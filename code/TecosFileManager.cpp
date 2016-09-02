#include "TecosFileManager.h"

TecosFileManager::TecosFileManager(FileSystem* fileSystem, UIDrawer * uiDrawer, TECOS::UART* uart)
{
    this->uiDrawer = uiDrawer;
    this->fileSystem = fileSystem;
    this->uart = uart;
}

TecosFileManager::~TecosFileManager()
{
    //dtor
}

void TecosFileManager::run() {

    cursorPosition = 1;
    uiDrawer->drawUI();
    uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);

    std::map<std::string, FileSystemItem*>::size_type maxPosition =
            fileSystem->directory->directoryContent.size();
    this->maxCursorPosition = static_cast<int>(maxPosition);
    std::cout<< "MAX POS: " << maxPosition << std::endl;
    int dataIn = 0;
    int counter = 0;
    while(true) {

        uint8_t charIn = uart->GetChar();
        dataIn += (int)charIn;
        counter++;

        //UP ARRW
        if (dataIn == 183 && counter == 3 && cursorPosition > 0) {
            cursorPosition--;
            uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
            std::cout << cursorPosition << std::endl;
            dataIn = 0;
        }

        // DOWN ARROW
        if (dataIn == 184 && counter == 3 && cursorPosition < maxCursorPosition) {
            cursorPosition++;
            std::cout << cursorPosition << std::endl;
            std::cout << TECOS::TIME::getSysSeconds() << std::endl;
            uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
            dataIn = 0;
            counter = 0;
        }

        // ENTER TO DIR
        if (dataIn == 13) {
            enterToDirectory(cursorPosition);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == NEW_FILE_COMMAND) {
            std::cout << "press 1" << std::endl;
            createNewFile(fileSystem->directory);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == NEW_DIR_COMMAND) {
            std::cout << "press 2" << std::endl;
            createNewDirectory(fileSystem->directory);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == EDIT_NAME_COMMAND) {
            std::cout << "press 3" << std::endl;
            renameFileSystemItem(cursorPosition);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == DELETE_COMMAND) {
            std::cout << "press 4" << std::endl;
            deleteFileSystemItem(cursorPosition);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == EDIT_FILE_CONTENT_COMMAND) {
            std::cout << "press 5" << std::endl;
            editFileContent(cursorPosition);
            dataIn = 0;
            counter = 0;
        }

        if (dataIn == QUIT_COMMAND) {
            std::cout << "press 6" << std::endl;
            quitProgram();
            dataIn = 0;
            counter = 0;
        }

        if(counter == 3 || (counter == 1 && dataIn != 27)) {
            dataIn = 0;
            counter = 0;
        }
    }

}


void TecosFileManager::enterToDirectory(int position) {

    if(position == 0) {
        if(fileSystem->directory->parentFileSystemItem != nullptr) {
            fileSystem->directory =
            (Directory*) fileSystem->directory->parentFileSystemItem;
            }
    } else {
        std::string key = getKeyFileSystemItem(position);
        if (fileSystem->directory->directoryContent.at(key)->fileSystemItemType == FS_DIRECTORY) {
            fileSystem->directory = (Directory*)fileSystem->directory->directoryContent.at(key);
        }
    }

    std::map<std::string, FileSystemItem*>::size_type maxPosition =
            fileSystem->directory->directoryContent.size();
    cursorPosition = 0;
    this->maxCursorPosition = static_cast<int>(maxPosition);
    //std::cout<< "new max pos: " << maxCursorPosition << std::endl;
    uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
}

void TecosFileManager::createNewDirectory(Directory * dir) {

    uiDrawer->showAlert("Enter the directory name");
    std::cout << "new file add" << std::endl;
    std::string fileName = getTextInput(20);

    if(fileName.size() > 0) {
        dir->createFileSystemItem(FS_DIRECTORY, fileName);
    }
    uiDrawer->showAlert("Directory created");
    uiDrawer->drawTextInput(" ");
    setMaxCursorPosition();
    this->cursorPosition = 1;
    uiDrawer->drawDirectoryContent(dir, 1);

}

void TecosFileManager::createNewFile(Directory * dir) {

    uiDrawer->showAlert("Enter the file name");
    std::cout << "new folder add" << std::endl;
    std::string fileName = getTextInput(20);

    if(fileName.size() > 0) {
        dir->createFileSystemItem(FS_FILEE, fileName);
    }
    uiDrawer->showAlert("File created");
    uiDrawer->drawTextInput(" ");
    setMaxCursorPosition();
    this->cursorPosition = 1;
    uiDrawer->drawDirectoryContent(dir, 1);
}

void TecosFileManager::deleteFileSystemItem(int position) {

    std::string key = getKeyFileSystemItem(position);
    uiDrawer->showAlert("Are you sure you want to delete selected item? Y-Yes, N-No");
    std::string answer = getTextInput(1);
    if (answer.compare("Y") == 0 || answer.compare("y") == 0) {
        std::cout<<"delete"<<std::endl;
        fileSystem->directory->directoryContent.erase(key);
        uiDrawer->showAlert("File system item deleted!");
        setMaxCursorPosition();
        cursorPosition--;
        uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
    } else if (answer.compare("N") == 0 || answer.compare("n") == 0) {

    } else {
        uiDrawer->showAlert("Wrong command!, Deleting aborted");
    }
}


void TecosFileManager::renameFileSystemItem(int position) {

    std::string key = getKeyFileSystemItem(position);
    uiDrawer->showAlert("Enter new name");
    std::string newName = getTextInput(20);
    if(newName.size() > 1) {
        FileSystemItem* item = fileSystem->directory->directoryContent.at(key);
        item->name = newName;
        item->modificationDate = LocalDataTimeStub::getDataTime();
        fileSystem->directory->directoryContent.erase(key);
        fileSystem->directory->directoryContent.insert
            (std::pair<std::string, FileSystemItem*>(newName, item));
        uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
    }

}

void TecosFileManager::editFileContent(int position) {

    std::string key = getKeyFileSystemItem(position);
    FileSystemItem * item = fileSystem->directory->directoryContent.at(key);
    if(item->fileSystemItemType == FS_FILEE) {
        uiDrawer->showAlert("Enter content of file:");
        File * file = (File*) item;
        std::string fileContent = getTextInput(50, file->content);
        file->setFileContent(fileContent);
    }

}

std::string TecosFileManager::getKeyFileSystemItem(int position) {

    std::map<std::string, FileSystemItem*> dirContent =
        fileSystem->directory->directoryContent;
    int counter = 1;
    std::string key;
    for (std::map<std::string, FileSystemItem*>::iterator it = dirContent.begin();
        it != dirContent.end(); it++) {
            if (position == counter) {
                key = it->first;
            }
            counter++;
        }
    return key;
}

void TecosFileManager::quitProgram() {

    //exit(0);
}

std::string TecosFileManager::getTextInput(int limit, std::string text) {

    uint8_t charr;
    std::string textIn = text;
    uiDrawer->drawTextInput(textIn);
    do {
        charr = uart->GetChar();


        if((charr != 13 && charr != 127)
           && textIn.size() <= limit - 1) {
            textIn += (char)charr;
           // textIn.append((char)charr);
        }

        if(charr == 127) {
            textIn.pop_back();
            //textIn = textIn.substr(0, textIn.length() - 1);
            std::cout<<std::dec<<(int)charr<<std::endl;
        }

        uiDrawer->drawTextInput(textIn);

    } while (charr != 13);

    return textIn;
}

void TecosFileManager::setMaxCursorPosition() {

    std::map<std::string, FileSystemItem*>::size_type maxPosition =
            fileSystem->directory->directoryContent.size();
    this->maxCursorPosition = static_cast<int>(maxPosition);
}
