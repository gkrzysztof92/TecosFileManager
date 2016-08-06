#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "io.h"
#include "time.h"

namespace TECOS
{
    struct UART
    {
        UART();
        ~UART();

        void Init();
        void PutChar(uint8_t _Character);
        void PutString(const char* _String);
        uint8_t GetChar();
    };
}
#endif // __SERIAL_H__
