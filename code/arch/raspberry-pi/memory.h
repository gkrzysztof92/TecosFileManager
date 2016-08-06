#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <cstdint>
#include <string.h>


namespace TECOS
{

    struct Memory
    {
        static inline void Barrier()
        {
            asm volatile("mcr p15, 0, ip, c7, c5,  0\n"
                         "mcr p15, 0, ip, c7, c5,  6\n"
                         "mcr p15, 0, ip, c7, c10, 4\n"
                         "mcr p15, 0, ip, c7, c5,  4");

        }
    };




}


#endif
