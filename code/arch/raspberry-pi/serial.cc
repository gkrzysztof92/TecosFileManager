#include "serial.h"

namespace TECOS
{
    UART::UART()
    {
        Init();
    }

    UART::~UART()
    {

    }

    void UART::Init()
    {
        //Deaktywuje UART.
        IO::Write32(IO_REGISTER::UART0_CR, 0);

        //Ustawienie wartości sygnału sterującego dla wybranych pinów GPIO (wyłączenie podciągnięcia)
        IO::Write32(IO_REGISTER::GPPUD, 0);
        TIME::Delay(150);

        //Wybranie pinów, do których zostanie wysłany sygnał sterujący
        IO::Write32(IO_REGISTER::GPPUDCLK0, (1 << 14) | (1 << 15));
        TIME::Delay(150);

        IO::Write32(IO_REGISTER::GPPUD, 0);

        //Przełączenie oczekujących przerwań w stan nieaktywny.
        IO::Write32(IO_REGISTER::UART0_ICR, 0x7FF);

        //Wyznaczenie całkowitej i ułamkowej części dzielnika szybkości transmisji
        //Parametry transmisji
        //
        //Szybkość transmisji - BAUD_RATE = 115200
        //Częstotliwość zegara UART - UART_CLOCK = 3MHz = 3000000Hz (Domyślna
        //
        //
        //Całkowita część dzielnika transmisji wynosi:
        //DIP = UART_CLOCK / (16 * BAUD_RATE)
        //DIP = 3000000 / (16 * 115200) = 1.627 ~ 1
        //
        //Ułamkowa część dzielnika szybkości transmisji
        //DFP = floor(DIP) * 64 + 0.5
        //DFP = 0.627 * 64 + 0.5 = 40.6 ~ 40

        IO::Write32(IO_REGISTER::UART0_IBRD, 1);
        IO::Write32(IO_REGISTER::UART0_FBRD, 40);

        //Parametry transmisji:
        // - 1 bit stopu
        // - FIFO
        // - 8 bitowe słowo

        IO::Write32(IO_REGISTER::UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

        //Wyłączenie przerwań UART
        IO::Write32(IO_REGISTER::UART0_IMSC, (1 << 1) | (1 << 2) | (1 << 3)
                                           | (1 << 4) | (1 << 5) | (1 << 6)
                                           | (1 << 7) | (1 << 8) | (1 << 9)
                                           | (1 << 10));

        //Aktywowanie UART:
        // - Włączenie linii nadawczej
        // - Włączenie linii odbiorczej
        IO::Write32(IO_REGISTER::UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
    }

    void UART::PutChar(uint8_t _Character)
    {
        //Oczeniwanie na gotowość do wysłania

        while(IO::Read32(IO_REGISTER::UART0_FR) & (1 << 5))
        { }

        IO::Write32(IO_REGISTER::UART0_DR, _Character);
    }

    void UART::PutString(const char* _String)
    {
        while(*_String)
        {
            PutChar(*_String++);
        }

    }


    uint8_t UART::GetChar()
    {
        //oczekiwanie na odebranie znaku
        while(IO::Read32(IO_REGISTER::UART0_FR) & (1 << 4))
        {

        }
        return IO::Read32(IO_REGISTER::UART0_DR);
    }

}
