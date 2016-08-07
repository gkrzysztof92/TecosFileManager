#include "UIDrawer.h"
#include <string>

using std::string;

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

    charDrawer->drawLine(applicationName, 2, 300);

    //second top line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,3,i);
    }

    //third top line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,31,i);
    }

    //another one top line
    for(int i = 17; i < 780; i+=7) {
        charDrawer->drawChar(205,6,i);
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
    charDrawer->drawLine(nameLabel, labelsLinePos, 100);
    charDrawer->drawLine(sizeLabel, labelsLinePos, 250);
    charDrawer->drawLine(creationDateLabel, labelsLinePos, 370);
    charDrawer->drawLine(modificationDateLabel, labelsLinePos, 480);
    charDrawer->drawLine(md5Label, labelsLinePos, 670);

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
        if (directory->parentFileSystemItem == nullptr) {
            charDrawer->drawLine(directory->name, startDirectoryDrawLine - 1, 30, 102, 255, 102);
        } else {
            charDrawer->drawLine("../" + directory->name, startDirectoryDrawLine - 1, 30, 102, 255, 102);
        }
    } else {
        if (directory->parentFileSystemItem == nullptr) {
            charDrawer->drawLine(directory->name, startDirectoryDrawLine - 1, 30);
        } else {
            charDrawer->drawLine("../" + directory->name, startDirectoryDrawLine - 1, 30);
        }
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

    for(int i = startDirectoryDrawLine - 1; i < 31; i++) {
        for (int j = 30; j < nameSizeSeparatorPos - 8; j+= 7) {
                charDrawer->drawChar(219, i, j, 0, 0, 0);
        }
        for (int j = nameSizeSeparatorPos + 10; j < sizeDateSeparatorPos - 10; j+= 7) {
                charDrawer->drawChar(219, i, j, 0, 0, 0);
        }
        for (int j = sizeDateSeparatorPos + 10; j < dateModSeparatorPos - 10; j+= 7) {
                charDrawer->drawChar(219, i, j, 0, 0, 0);
        }
        for (int j = modMd5SeparatorPos + 10; j < 780 - 10; j+= 7) {
                charDrawer->drawChar(219, i, j, 0, 0, 0);
        }
    }



}

void UIDrawer::drawFileInfo(File * file, int line, bool current) {

    if (current) {
        //std::string itemSize = st(file->itemSize);
        std::string itemSize = "10";
        charDrawer->drawLine(file->name, line, 30, 102, 255, 102);
        charDrawer->drawLine(itemSize, line, nameSizeSeparatorPos + 10, 102, 255, 102);
        charDrawer->drawLine(file->creationDate, line, sizeDateSeparatorPos + 10, 102, 255, 102);
        charDrawer->drawLine(file->modificationDate, line, dateModSeparatorPos +10, 102, 255, 102);

    } else {
        //std::string itemSize = to_string(file->itemSize);
        std::string itemSize = "" + file->itemSize;
        charDrawer->drawLine(file->name, line, 30);
        charDrawer->drawLine(itemSize, line, nameSizeSeparatorPos + 10);
        charDrawer->drawLine(file->creationDate, line, sizeDateSeparatorPos + 10) ;
        charDrawer->drawLine(file->modificationDate, line, dateModSeparatorPos +10);
    }

}

void UIDrawer::drawDirectoryInfo(Directory * directory,int line, bool current) {

    if (current) {
        charDrawer->drawLine("/" + directory->name, line, 30, 102, 255, 102);
        charDrawer->drawLine("<DIR>", line, nameSizeSeparatorPos + 10, 102, 255, 102);
        charDrawer->drawLine(directory->creationDate, line, sizeDateSeparatorPos + 10, 102, 255, 102);
        charDrawer->drawLine(directory->modificationDate, line, dateModSeparatorPos +10, 102, 255, 102);
	charDrawer->drawLine(md5(directory->name).substr(1, 17)+"...", line, modMd5SeparatorPos +10, 102, 255, 102);

    } else {
        charDrawer->drawLine("/" + directory->name, line, 30);
        charDrawer->drawLine("<DIR>", line, nameSizeSeparatorPos + 10);
        charDrawer->drawLine(directory->creationDate, line, sizeDateSeparatorPos + 10) ;
        charDrawer->drawLine(directory->modificationDate, line, dateModSeparatorPos +10);
	charDrawer->drawLine(md5(directory->name).substr(1, 17)+"...", line, modMd5SeparatorPos +10, 102, 255, 102);
    }
}

void UIDrawer::showAlert(std::string message) {

    for (int j = 10; j < 800; j+= 7) {
        charDrawer->drawChar(219, alertLine, j, 0, 0, 0);
    }
    charDrawer->drawLine(message, alertLine, 10, 255, 255, 0);
}

void UIDrawer::drawPath(std::string path)
{
    charDrawer->drawLine(path, pathLine, 30);
}

