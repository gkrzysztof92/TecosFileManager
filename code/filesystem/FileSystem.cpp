#include "FileSystem.h"

FileSystem::FileSystem()
{

    directory = new Directory(FS_DIRECTORY, "/");
    directory->createFileSystemItem(FS_DIRECTORY, "tmp");
    directory->createFileSystemItem(FS_DIRECTORY, "home");
    directory->createFileSystemItem(FS_DIRECTORY, "axxa");

}

FileSystem::~FileSystem()
{
    //dtor
}
