#ifndef FILESYSTEMITEM_H
#define FILESYSTEMITEM_H

#include <string>


enum FileSystemItemType
	{
		FS_DIRECTORY,
		FS_FILEE
	};

class FileSystemItem
{
    public:
        FileSystemItemType fileSystemItemType;
        FileSystemItem * parentFileSystemItem;
        std::string name;
        std::string creationDate;
        std::string modificationDate;
	std::string md5;
        int itemSize = 0;

        FileSystemItem();
        FileSystemItem(FileSystemItemType fileSystemItemType, std::string name);
        FileSystemItem(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parentFileSystemItem);
        virtual ~FileSystemItem();

    protected:

    private:

};

#endif // FILESYSTEMITEM_H
