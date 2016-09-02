#include "UIDrawer.h"

UIDrawer::UIDrawer()
{
    //ctor
}

UIDrawer::~UIDrawer()
{
    //dtor
}

void UIDrawer::setCharDrawer(TECOS::CharDrawer *charDrawer) {
    this->charDrawer = charDrawer;
}

void UIDrawer::drawMainWindow() {

    //top Line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,1,i);
    }

    charDrawer->drawLine(applicationName, 2, 200);

    //second top line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,3,i);
    }

    //third top line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,31,i);
    }

    //right Line
    charDrawer->drawChar(201,1,10);
    for(int i = 2; i < layoutLastLinePos; i++) {
        if (i == 3 || i == 31 ) {
            charDrawer->drawChar(204, i, 10);
        } else {
            charDrawer->drawChar(186, i, 10);
        }
    }
    charDrawer->drawChar(200, layoutLastLinePos, 10);

    //left line
    charDrawer->drawChar(187,1,780);
    for(int i = 2; i < layoutLastLinePos; i++) {
        if (i == 3 || i == 31 ) {
            charDrawer->drawChar(185, i, 780);
        } else {
            charDrawer->drawChar(186,i,780);
        }
    }
    charDrawer->drawChar(188, layoutLastLinePos, 780);

    //singleLines
    for(int i = separatorLineStart; i< separatorLineEnd; i++) {
        charDrawer->drawChar(179,i,nameSizeSeparatorPos);
    }
    for(int i = separatorLineStart; i< separatorLineEnd; i++) {
        charDrawer->drawChar(179,i,sizeDateSeparatorPos);
    }
    for(int i = separatorLineStart; i< separatorLineEnd; i++) {
        charDrawer->drawChar(179,i,dateModSeparatorPos);
    }
    for(int i = separatorLineStart; i< separatorLineEnd; i++) {
        charDrawer->drawChar(179,i,modMd5SeparatorPos);
    }


    //bottom line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,layoutLastLinePos,i);
    }

    //labels
    charDrawer->drawLine(nameLabel, labelsLinePos, 150);
    charDrawer->drawLine(sizeLabel, labelsLinePos, 300);
    charDrawer->drawLine(creationDateLabel, labelsLinePos, 400);
    charDrawer->drawLine(modificationDateLabel, labelsLinePos, 500);
    charDrawer->drawLine(md5Label, labelsLinePos, 600);

}

void UIDrawer::drawTextInput(std::string text) {
    for (int j = 10; j < 800; j+= 7) {
        charDrawer->drawChar(219, textInputLine, j, 0, 0, 0);
    }
    std::string inputLabel = "[root@root]$ " + text;
    charDrawer->drawLine(inputLabel, textInputLine, 10);
}

void UIDrawer::drawCommandBar() {
    std::string comandLabbels = newFileCommand + "    " + newDirCommand +
    "    " + editFileDirNameCommand + "    " + deleteCommand +
    "    " + editFileContentCommand + "    " + quitCommand;
    charDrawer->drawLine(comandLabbels, commandBarLine, 10);
}

void UIDrawer::drawUI() {

    drawMainWindow();
    drawTextInput(" ");
    drawCommandBar();
}

void UIDrawer::drawDirectoryContent(Directory * directory, int position) {

    clearDirectoryContent();
    std::map<std::string, FileSystemItem*> dc = directory->directoryContent;
    int line = startDirectoryDrawLine;
    if (position == 0) {
        charDrawer->drawLine("../" + directory->name, startDirectoryDrawLine - 1, 30, 102, 255, 102);
    } else {
        charDrawer->drawLine("../" + directory->name, startDirectoryDrawLine - 1, 30);
    }

    int iterPos = 1;
    for(std::map<std::string, FileSystemItem*>:: iterator it = dc.begin();
        it != dc.end(); it++) {

        if (position == iterPos) {
            if(it->second->fileSystemItemType == FS_FILEE) {
                drawFileInfo((File*)it->second, line, true);
            } else {
                drawDirectoryInfo((Directory*)it->second, line, true);
            }

        } else {
            if(it->second->fileSystemItemType == FS_FILEE) {
                drawFileInfo((File*)it->second, line, false);
            } else {
                drawDirectoryInfo((Directory*)it->second, line, false);
            }
        }
        iterPos++;
        line++;
    }

}

void UIDrawer::clearDirectoryContent() {

    for(int i = startDirectoryDrawLine - 1; i < 20; i++) {
        for (int j = 30; j < 200; j+= 7) {
                charDrawer->drawChar(219, i, j, 0, 0, 0);
        }
    }

}

void UIDrawer::drawFileInfo(File * file, int line, bool current) {

    if (current) {
        //std::string itemSize = to_string(file->itemSize);
        charDrawer->drawLine(file->name, line, 30, 102, 255, 102);
        charDrawer->drawLine("itemSize", line, 200, 102, 255, 102);
        charDrawer->drawLine(file->creationDate, line, 250, 102, 255, 102);
        charDrawer->drawLine(file->modificationDate, line, 300, 102, 255, 102);

    } else {
        //std::string itemSize = to_string(file->itemSize);
        charDrawer->drawLine(file->name, line, 30);
        charDrawer->drawLine("itemSize", line, 200);
        charDrawer->drawLine(file->creationDate, line, 250) ;
        charDrawer->drawLine(file->modificationDate, line, 300);
    }

}

void UIDrawer::drawDirectoryInfo(Directory * directory,int line, bool current) {

    if (current) {
        charDrawer->drawLine(directory->name, line, 30, 102, 255, 102);
        charDrawer->drawLine("<DIR>", line, 200, 102, 255, 102);
        charDrawer->drawLine(directory->creationDate, line, 250, 102, 255, 102);
        charDrawer->drawLine(directory->modificationDate, line, 300, 102, 255, 102);

    } else {
        charDrawer->drawLine(directory->name, line, 30);
        charDrawer->drawLine("<DIR>", line, 200);
        charDrawer->drawLine(directory->creationDate, line, 250) ;
        charDrawer->drawLine(directory->modificationDate, line, 300);
    }
}

void UIDrawer::showAlert(std::string message) {


    for (int j = 10; j < 800; j+= 7) {
        charDrawer->drawChar(219, alertLine, j, 0, 0, 0);
    }
    charDrawer->drawLine(message, alertLine, 10, 255, 255, 0);
}

