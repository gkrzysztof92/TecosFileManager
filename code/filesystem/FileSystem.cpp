#include "FileSystem.h"

FileSystem::FileSystem()
{

    directory = new Directory(FS_DIRECTORY, "/");
    directory->createFileSystemItem(FS_DIRECTORY, "tmp");
    directory->createFileSystemItem(FS_DIRECTORY, "home");
    directory->createFileSystemItem(FS_DIRECTORY, "sys");
    directory->createFileSystemItem(FS_FILEE, "text.txt");

}

FileSystem::~FileSystem()
{
    //dtor
}
