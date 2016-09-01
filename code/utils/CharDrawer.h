#ifndef CHARDRAWER_H
#define CHARDRAWER_H

#include <string>
#include "../arch/raspberry-pi/framebuffer.h"
#include "cp437-font.h"

namespace TECOS {

    class CharDrawer
    {
        public:
            const int CHAR_HEIGHT = 16;
            const int CHAR_WIDTH = 8;
            const int OFFSET_BETWEEN_CAHRS = 1;

            void drawChar(int charCode, int line, int column, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, float a = 1);
            void drawLine(std::string content, int line, int column, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, float a = 1);
            void setFrameBuffer(TECOS::FRAMEBUFFER *frame_buffer);
            CharDrawer();
            virtual ~CharDrawer();

        protected:

        private:
            TECOS::FRAMEBUFFER *frame_buffer;

    };

}



#endif // CHARDRAWER_H
