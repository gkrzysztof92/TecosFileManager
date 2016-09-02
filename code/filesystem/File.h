#ifndef FILE_H
#define FILE_H

#include <string>
#include "FileSystemItem.h"
#include "Directory.h"
#include "../utils/LocalDataTimeStub.h"

class File : public FileSystemItem
{
    public:
        std::string content;
        std::string md5;

        File();
        File(FileSystemItemType fileSystemItemType, std::string name);
        File(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parentDirectory);
        void setFileContent(std::string content);
        virtual ~File();

    protected:

    private:

};

#endif // FILE_H
