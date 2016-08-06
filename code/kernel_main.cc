#include "arch.h"
#include "output.h"

extern uint8_t end;
extern uint8_t stack;

extern "C"
void kernel_main()
{
    TECOS::SetOutput(TECOS::OUTPUT_TYPE::UART);
    std::cout << "TECOS" << TECOS::endl << TECOS::endl;
    std::cout << "Rozmiar sterty: " << (&stack - &end) / 1024 << "KB" << TECOS::endl;
    std::cout << "Adres konca stosu: 0x" << std::hex << reinterpret_cast<uintptr_t>(&stack) << TECOS::endl;

    TECOS::FRAMEBUFFER frame_buffer(800,600);

    for (uint32_t x=0; x <800; x++)
    {
        for (uint32_t y=0; y <600; y++)
        {
            frame_buffer.SetPixel(x, y, TECOS::RGBToColor(0, x^y % 0xFF, 0,0xFF));
        }
    }

    //fram_buffer.SetPixel(100, 100, TECOS::RGBToColor(0xFF,0,0,0xFF));


    while(true)
    {
        //TECOS::TIME::DelayS(1);

       //std::cout<< "I'm alive!" << TECOS::endl;
    }
}
