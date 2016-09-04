#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <string>
#include <vector>
#include <map>
#include "FileSystemItem.h"
#include "File.h"
#include "../utils/LocalDataTimeStub.h"

class Directory : public FileSystemItem
{
    public:
        const int sizeOfMetadata = 4096;
        std::map<std::string, FileSystemItem*> directoryContent;

        Directory();
        Directory(FileSystemItemType fileSystemItemType, std::string name);
        Directory(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem* parentDirectory);
        bool createFileSystemItem(FileSystemItemType type, std::string name);
        void deleteFileSystemItem(std::string name);
        void renameFileSystemItem(std::string currentName, std::string newName);
        std::vector<std::string> getListOfItemsInDirectory();
        virtual ~Directory();
    protected:

    private:

};

#endif // DIRECTORY_H
