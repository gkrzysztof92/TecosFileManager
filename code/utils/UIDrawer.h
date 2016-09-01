#ifndef UIDRAWER_H
#define UIDRAWER_H

#include <string>
#include <map>
#include <vector>
#include "CharDrawer.h"
#include "../filesystem/Directory.h"
#include "../filesystem/FileSystemItem.h"
#include "../filesystem/File.h"


class UIDrawer
{
    public:
        const std::string applicationName = "TECOS FILE MANAGER";
        const std::string newFileCommand = "1 NEW FILE";
        const std::string newDirCommand = "2 NEW DIR";
        const std::string editFileDirNameCommand = "3 EDIT NAME";
        const std::string deleteCommand = "4 DELETE";
        const std::string nameLabel = "Name";
        const std::string sizeLabel = "Size";
        const std::string creationDateLabel = "Date";
        const std::string modificationDateLabel = "Mod Date";
        const std::string md5Label = "MD5";

        const int layoutFirstLinePos = 1;
        const int layoutSecondLinePos = 3;
        const int layoutLastLinePos = 31;

        const int labelsLinePos = 5;
        const int separatorLineStart = 4;
        const int separatorLineEnd = 34;
        const int nameSizeSeparatorPos = 270;
        const int sizeDateSeparatorPos = 360;
        const int dateModSeparatorPos = 470;
        const int modMd5SeparatorPos = 570;

        const int RightLeftMargin = 10;

        const int textInputLine = 35;
        const int commandBarLine = 36;

        const int startDirectoryDrawLine = 8;

        UIDrawer();
        virtual ~UIDrawer();
        void setCharDrawer(TECOS::CharDrawer *charDrawer);
        void drawUI();
        void drawDirectoryContent(Directory * directory, int position);
        void drawFileInfo(File * file);
        void drawDirectoryInfo(Directory * directory);
        void clearDirectoryContent();
    protected:

    private:
        TECOS::CharDrawer *charDrawer;
        void drawMainWindow();
        void drawTextInput();
        void drawCommandBar();
};

#endif // UIDRAWER_H
