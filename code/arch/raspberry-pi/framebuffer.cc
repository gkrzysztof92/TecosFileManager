
#include "framebuffer.h"


namespace TECOS
{

    FRAMEBUFFER::FRAMEBUFFER(uint32_t _Width, uint32_t _Height, uint32_t _Depth ) :Valid(false)
    {
        //pobieranie adresu bufora ramki wideo

        FrameBufferInfo = reinterpret_cast<FRAMEBUFFER_INFO*>(IO_REGISTER::FB_LOCATION);

        //ustawienia nbufora ramki


        FrameBufferInfo->Width = _Width;
        FrameBufferInfo->Height = _Height;
        FrameBufferInfo->VidtualWidth = _Width;
        FrameBufferInfo->VirtualHeight = _Height;
        FrameBufferInfo->Pitch = 0;
        FrameBufferInfo->Depth = _Depth;
        FrameBufferInfo->XOffset = 0;
        FrameBufferInfo->YOffset = 0;
        FrameBufferInfo->Base = 0;
        FrameBufferInfo->Size = 0;





        //zainicjowanie bufora ramki
        //wysylanie żądania
        IO::MailboxWrite(1,IO::PhysicalToBus(reinterpret_cast<uint32_t>(FrameBufferInfo)));

        uint32_t result = 0xFF;

        do
        {
            result = IO::MailboxRead(1);
        }
        while(result != 0);

        //sprawdznie poprawnosci odopwiedzi
        if(FrameBufferInfo->Base ==0) return;
        if(FrameBufferInfo->Pitch ==0) return;


        //skorygowanie adresu

        FrameBufferInfo->Base = IO::BusToPhysical(FrameBufferInfo->Base);

        //ustawnie flagi poprawnosci flagi

        Valid = true;


    }

    uint32_t FRAMEBUFFER::GetWidth()
    {
        return FrameBufferInfo->Width;
    }

    uint32_t FRAMEBUFFER::GetHeight()
    {
        return FrameBufferInfo->Height;
    }

    void FRAMEBUFFER::SetPixel(uint32_t _PostitionX, uint32_t _PositionY, uint32_t _Color)
    {
        //ustawienie polozenia bufora
        uint32_t buffer_offset,
        x = _PostitionX,
        y = _PositionY;

        x = (x<0) ? 0 : x;
        x = (x > FrameBufferInfo->Width) ? FrameBufferInfo->Width : x;

        y = (y<0) ? 0 : y;
        y = (y > FrameBufferInfo->Height) ? FrameBufferInfo->Height : y;

        buffer_offset = (y * FrameBufferInfo->Pitch) + (x * FrameBufferInfo->Depth >> 3);

        //ustawienie koloru pixela

        *reinterpret_cast<uint32_t*>(FrameBufferInfo->Base + buffer_offset) = _Color;
    }

}

