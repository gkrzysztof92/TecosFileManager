#ifndef __IO_H__
#define __IO_H__

#include <cstdint>
#include "memory.h"

namespace TECOS
{
    enum class IO_REGISTER : uint32_t
    {
        //Bazowy adres 64-bitowego licznika systemowego
        TIMER_BASE = 0x20003000,

        //Bazowy adres rejestru GPIO
        GPIO_BASE = 0x20200000,

        //Pozwala na włączenie/wyłączenie podciągnięcia dla wszystkich pinów GPIO
        GPPUD = (GPIO_BASE + 0x94),

        //Pozwala na ustawienie podciągnięcia dla wybranego pinu GPIO
        GPPUDCLK0 = (GPIO_BASE + 0x98),

        //Bazowy adres UART
        UART0_BASE = 0x20201000,

        //Adresy pozostałych rejestrów związanych z UART
        UART0_DR = (UART0_BASE + 0x00),
        UART0_FR = (UART0_BASE + 0x18),
        UART0_IBRD = (UART0_BASE + 0x24),
        UART0_FBRD = (UART0_BASE + 0x28),
        UART0_LCRH = (UART0_BASE + 0x2C),
        UART0_CR = (UART0_BASE + 0x30),
        UART0_IMSC = (UART0_BASE + 0x38),
        UART0_ICR = (UART0_BASE + 0x44),

        // bazowy adres mailbox
        MAILBOX_BASE = 0x2000B880,

        //adresy pozostałeych rejestrow
        MAILBOX_READ = (MAILBOX_BASE + 0x00),
        MAILBOX_STATUS = (MAILBOX_BASE + 0x18),
        MAILBOX_WRITE = (MAILBOX_BASE + 0x20),

        //framebuffor, bufor ramki wideo
        FB_LOCATION = 0x00002000,

        //adres magistrali
        BUS_LOCATION = 0x40000000


    };

    constexpr bool operator> (const uint32_t& _OperandA, const IO_REGISTER& _OperandB)
    {
        return (_OperandA > static_cast<uint32_t>(_OperandB));
    }

    constexpr uint32_t operator+ (const uint32_t& _OperandA, const IO_REGISTER& _OperandB)
    {
        return (_OperandA + static_cast<uint32_t>(_OperandB));
    }

    constexpr uint32_t operator- (const uint32_t& _OperandA, const IO_REGISTER& _OperandB)
    {
        return (_OperandA - static_cast<uint32_t>(_OperandB));
    }

    struct IO
    {
        static inline uint32_t Read32(IO_REGISTER _Register)
        {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(_Register);
            uint32_t data{};

            asm volatile ("ldr %[Data], [%[Register]]"
                          : [Data]"=r"(data)
                          : [Register]"r"(ptr));
            return data;
        }

        static inline void Write32(IO_REGISTER _Register, uint32_t _Data)
        {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(_Register);

            asm volatile ("str %[Data], [%[Register]]"
                          :
                          : [Register]"r"(ptr), [Data]"r"(_Data));
        }

        static inline uint32_t PhysicalToBus(uint32_t _Address)
        {
            return (_Address + IO_REGISTER::BUS_LOCATION);
        }

        static inline uint32_t BusToPhysical(uint32_t _Address)
        {
            if(_Address > IO_REGISTER::BUS_LOCATION)
                return (_Address - IO_REGISTER::BUS_LOCATION);

            return _Address;
        }

        static uint32_t MailboxRead(uint8_t _Channel);
        static void MailboxWrite(uint8_t _Channel, uint32_t _Data);

    };


}

#endif // __IO_H__
