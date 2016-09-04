#include "arch.h"
#include "output.h"
#include <string>
#include "utils/CharDrawer.h"
#include "utils/UIDrawer.h"
#include "filesystem/FileSystem.h"
#include "TecosFileManager.h"
#include "arch/raspberry-pi/time.h"
#include <ctime>


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
	TECOS::CharDrawer* charDrawer = new TECOS::CharDrawer();
	charDrawer->setFrameBuffer(&frame_buffer);
	UIDrawer* uiDrawer = new UIDrawer();
	uiDrawer->setCharDrawer(charDrawer);
    FileSystem * fs = new FileSystem();
    TECOS::UART * uart = new TECOS::UART;

    TecosFileManager* fileManager = new TecosFileManager(fs, uiDrawer, uart);
    fileManager->run();

    /*while(true)
    {
        //TECOS::TIME::DelayS(1);

       //std::cout<< "I'm alive!" << TECOS::endl;
    }*/
}
