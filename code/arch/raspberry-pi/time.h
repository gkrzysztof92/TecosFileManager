#ifndef __TIME_H__
#define __TIME_H__

#include <cstdint>
#include "io.h"

extern "C" void DelayCycles(uint32_t _NumberOfCycles);

namespace TECOS
{
    struct TIMER
    {
        volatile uint32_t ControlStatus,
         CounterLO,
         CounterHI,
         Compare0,
         Compare1,
         Compare2,
         Compare3;
    };

    class TIME
    {
    public:

        /*static inline void Delay(uint32_t _NumberOfCycles)
        {
            asm volatile("delay_loop:\n"
                         "    subs %[NumberOfCycles], %[NumberOfCycles], #1\n"
                         "    bne delay_loop"
                         :
                         : [NumberOfCycles]"r"(_NumberOfCycles)
                         : "cc");
        }*/

        static inline uint32_t getSysSeconds() {
            return SYSTEM_TIMER->CounterLO/1000000;
        }

        //get fake data


        static inline void Delay(uint32_t _NumberOfCycles)
        {
            DelayCycles(_NumberOfCycles);
        }

        static inline void DelayUS(uint32_t _Microseconds)
        {
            volatile uint32_t start_time = SYSTEM_TIMER->CounterLO;

            while((SYSTEM_TIMER->CounterLO - start_time) < _Microseconds)
            { }
        }

        static inline void DelayMS(uint32_t _Miliseconds)
        {
            DelayUS(1000 * _Miliseconds);
        }

        static inline void DelayS(uint32_t _Seconds)
        {
            DelayMS(1000 * _Seconds);
        }

    private:
        static TIMER* SYSTEM_TIMER;
    };
}

#endif // __TIME_H__
