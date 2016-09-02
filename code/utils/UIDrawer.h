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
        const std::string editFileContentCommand = "5 EDIT FILE CONTENT";
        const std::string quitCommand = "6 QUIT";

        const std::string nameLabel = "Name";
        const std::string sizeLabel = "Size";
        const std::string creationDateLabel = "Date";
        const std::string modificationDateLabel = "Mod Date";
        const std::string md5Label = "MD5";

        const int layoutFirstLinePos = 1;
        const int layoutSecondLinePos = 3;
        const int layoutLastLinePos = 33;

        const int labelsLinePos = 5;
        const int separatorLineStart = 4;
        const int separatorLineEnd = 31;
        const int nameSizeSeparatorPos = 220;
        const int sizeDateSeparatorPos = 320;
        const int dateModSeparatorPos = 450;
        const int modMd5SeparatorPos = 580;

        const int RightLeftMargin = 10;

        const int pathLine = 32;
        const int alertLine = 34;
        const int textInputLine = 35;
        const int commandBarLine = 36;

        const int startDirectoryDrawLine = 8;

        UIDrawer();
        virtual ~UIDrawer();
        void setCharDrawer(TECOS::CharDrawer *charDrawer);
        void drawUI();
        void drawDirectoryContent(Directory * directory, int position);
        void drawFileInfo(File * file, int line, bool current);
        void drawDirectoryInfo(Directory * directory, int line, bool current);
        void clearDirectoryContent();
        void showAlert(std::string message);
        void drawTextInput(std::string text);
        void drawPath(std::string path);
    protected:

    private:
        TECOS::CharDrawer *charDrawer;
        void drawMainWindow();
        void drawCommandBar();
};

#endif // UIDRAWER_H
