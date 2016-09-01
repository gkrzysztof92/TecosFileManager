#include "FileSystemItem.h"

FileSystemItem::FileSystemItem() {

}

FileSystemItem::FileSystemItem(FileSystemItemType fileSystemItemType, std::string name) {
    this->fileSystemItemType = fileSystemItemType;
    this->name = name;
}

FileSystemItem::FileSystemItem(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parent) {
    this->fileSystemItemType = fileSystemItemType;
    this->parentFileSystemItem = parent;
    this->name = name;
}

FileSystemItem::~FileSystemItem()
{
    //dtor
}
