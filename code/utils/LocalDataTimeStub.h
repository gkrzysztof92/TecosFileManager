#ifndef LOCALDATATIMESTUB_H
#define LOCALDATATIMESTUB_H

#include "../arch/raspberry-pi/time.h"
#include <ctime>

class LocalDataTimeStub
{
    public:
        static inline std::string getDataTime() {
            uint32_t seconds = TECOS::TIME::getSysSeconds();
            time_t time = seconds;
            char buff[80];
            struct tm * lt = localtime(&time);
            strftime(buff, 80, "%Y-%m-%d %H-%M-%S", lt);
            std::string formatedDate(buff);
            return formatedDate;
        }

    protected:

    private:
};

#endif // LOCALDATATIMESTUB_H
