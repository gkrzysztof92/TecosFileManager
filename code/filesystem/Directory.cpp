#include "Directory.h"

Directory::Directory()
    : FileSystemItem() {

}

Directory::Directory(FileSystemItemType fileSystemItemType, std::string name)
    : FileSystemItem(fileSystemItemType, name) {
        this->creationDate = LocalDataTimeStub::getDataTime();

}

Directory::Directory(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem* parentDirectory)
    :FileSystemItem(fileSystemItemType, name, parentDirectory) {
        this->creationDate = LocalDataTimeStub::getDataTime();

}


Directory::~Directory()
{
    //dtor
}

bool Directory::createFileSystemItem(FileSystemItemType type, std::string name){

    if(directoryContent[name] == nullptr) {
        if(type == FS_DIRECTORY) {
            directoryContent[name] = new Directory(type, name, this);
        } else {
            directoryContent[name] = (FileSystemItem*) new File(type, name, this);
        }
        return true;
    } else {
        return false;
    }

}

void Directory::deleteFileSystemItem(std::string name) {

}

void Directory::renameFileSystemItem(std::string currentName, std::string newName) {

}



