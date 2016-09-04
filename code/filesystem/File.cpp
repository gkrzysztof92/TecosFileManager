#include "File.h"

File::File()
    : FileSystemItem() {

}

File::File(FileSystemItemType fileSystemItemType, std::string name)
    : FileSystemItem(fileSystemItemType, name) {
    this->creationDate = LocalDataTimeStub::getDataTime();
    this->itemSize = 0;
}

File::File(FileSystemItemType fileSystemItemType, std::string name, FileSystemItem * parentDirectory)
    : FileSystemItem(fileSystemItemType, name, parentDirectory) {
    this->creationDate = LocalDataTimeStub::getDataTime();
}

void File::setFileContent(std::string content) {
    this->content = content;
    this->itemSize = static_cast<int>(content.size()) * 8;
    this->modificationDate = LocalDataTimeStub::getDataTime();
}


File::~File()
{
    //dtor
}
