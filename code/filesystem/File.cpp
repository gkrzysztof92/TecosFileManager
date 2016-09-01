#include "File.h"

File::File()
    : FileSystemItem() {

}

File::File(FileSystemItemType fileSystemItemType, std::string name)
    : FileSystemItem(fileSystemItemType, name) {

}

File::File(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parentDirectory)
    : FileSystemItem(fileSystemItemType, name, parentDirectory) {

}


File::~File()
{
    //dtor
}
