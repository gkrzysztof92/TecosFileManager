#ifndef TECOSFILEMANAGER_H
#define TECOSFILEMANAGER_H

#include<string>
#include<vector>
#include<map>
#include<stdio.h>


#include "filesystem/FileSystem.h"
#include "utils/UIDrawer.h"
#include "arch/raspberry-pi/serial.h"


class TecosFileManager
{
    public:
        const uint8_t UP = 13;
        const uint8_t DOWN = 40;
        const uint8_t ENTER = 13;
        const uint8_t NEW_FILE_COMMAND = 49;
        const uint8_t NEW_DIR_COMMAND = 32;
        const uint8_t EDIT_NAME_COMMAND = 33;
        const uint8_t DELETE_COMMAND = 34;
        const uint8_t EDIT_FILE_CONTENT_COMMAND = 35;

        uint8_t cursorPosition;
        int maxCursorPosition;

        TecosFileManager(FileSystem* fileSystem, UIDrawer * uiDrawer, TECOS::UART* uart);
        void enterToDirectory(int position);
        void createNewFile(Directory * dir);
        void createNewDirectory(Directory * dir);
        void renameFileSystemItem(int position);
        void deleteFileSystemItem(int position);
        void editFileContent(int position);
        std::string getKeyFileSystemItem(int position);
        std::string getTextInput(int limit);
        virtual ~TecosFileManager();

        void run();

    protected:

    private:
        FileSystem* fileSystem;
        UIDrawer* uiDrawer;
        TECOS::UART* uart;
};

#endif // TECOSFILEMANAGER_H
