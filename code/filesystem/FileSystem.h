#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Directory.h"
#include "File.h"
#include <string>
#include <map>
#include <vector>

class FileSystem
{
    public:
        Directory* directory;

        FileSystem();
        virtual ~FileSystem();

    protected:

    private:
};

#endif // FILESYSTEM_H
