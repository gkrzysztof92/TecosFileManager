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

void UIDrawer::drawTextInput() {
    std::string inputLabel = "[root@root]$ ";
    charDrawer->drawLine(inputLabel, textInputLine, 10);
}

void UIDrawer::drawCommandBar() {
    std::string comandLabbels = newFileCommand + "  " + newDirCommand + "  " + editFileDirNameCommand + "  " + deleteCommand;
    charDrawer->drawLine(comandLabbels, commandBarLine, 10);
}

void UIDrawer::drawUI() {

    drawMainWindow();
    drawTextInput();
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
                charDrawer->drawLine(it->second->name, line, 30, 102, 255, 102);
        } else {
            charDrawer->drawLine(it->second->name, line, 30);
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

void UIDrawer::drawFileInfo(File * file) {

}

void UIDrawer::drawDirectoryInfo(Directory * directory) {

}

