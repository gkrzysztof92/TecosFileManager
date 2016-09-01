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
        fileSystem->directory = (Directory*)fileSystem->directory->directoryContent.at(key);
    }


    std::map<std::string, FileSystemItem*>::size_type maxPosition =
            fileSystem->directory->directoryContent.size();
    cursorPosition = 0;
    this->maxCursorPosition = static_cast<int>(maxPosition);
    std::cout<< "new max pos: " << maxCursorPosition << std::endl;
    uiDrawer->drawDirectoryContent(fileSystem->directory, cursorPosition);
}

void TecosFileManager::createNewDirectory(Directory * dir) {

}

void TecosFileManager::createNewFile(Directory * dir) {

}

void TecosFileManager::deleteFileSystemItem(int position) {

}

void TecosFileManager::renameFileSystemItem(int position) {

}

void TecosFileManager::editFileContent(int position) {

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
