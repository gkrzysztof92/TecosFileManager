#ifndef FILE_H
#define FILE_H

#include <string>
#include "FileSystemItem.h"
#include "Directory.h"

class File : public FileSystemItem
{
    public:
        std::string content;

        File();
        File(FileSystemItemType fileSystemItemType, std::string name);
        File(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parentDirectory);
        virtual ~File();

    protected:

    private:

};

#endif // FILE_H
