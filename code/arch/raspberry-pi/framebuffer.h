#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <cstdint>
#include <iostream>

#include "io.h"

namespace TECOS
{
    struct FRAMEBUFFER_INFO
    {
        uint32_t Width,
        Height,
        VidtualWidth,
        VirtualHeight,
        Pitch,
        Depth,
        XOffset,
        YOffset,
        Base,
        Size;
    };



    class FRAMEBUFFER
    {
    public:
        FRAMEBUFFER(uint32_t _Width, uint32_t _Height, uint32_t _Depth = 32);

        uint32_t GetWidth();
        uint32_t GetHeight();

        void SetPixel(uint32_t _PostitionX, uint32_t _PositionY, uint32_t _Color);


    private:
        FRAMEBUFFER_INFO* FrameBufferInfo;
        bool Valid;


    };

    inline uint32_t RGBToColor(uint8_t _RComp,uint8_t _GComp,uint8_t _BComp,uint8_t _AComp)
    {
        return ((_AComp << 24) + (_BComp << 16) + (_GComp << 8) + (_RComp));
    }

}
#endif
