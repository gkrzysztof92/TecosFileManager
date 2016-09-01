#include "CharDrawer.h"

namespace TECOS {

    CharDrawer::CharDrawer()
    {
        //ctor
    }

    CharDrawer::~CharDrawer()
    {
        //dtor
    }

    void CharDrawer::setFrameBuffer(TECOS::FRAMEBUFFER *frame_buffer) {
        this->frame_buffer = frame_buffer;
    }

    void CharDrawer::drawChar(int charCode, int line, int column,
                              uint8_t r, uint8_t g , uint8_t b, float a) {

        int xStartDrawingPoint = column;
        int yStartDrawingPoint = line * CHAR_HEIGHT;

        for (int i = 0; i < CHAR_HEIGHT; i++) {
            int character = cp437_font[charCode][i];
            int x = xStartDrawingPoint;
            int y = yStartDrawingPoint + i;
            for (int j = 0; j < CHAR_WIDTH; j++) {
                x++;
                if((character & (1 << (8 - j)))) {
                    frame_buffer->SetPixel(x, y, TECOS::RGBToColor(r, g, b, a));
                }
            }
        }
    }

    void CharDrawer::drawLine(std::string content, int line, int column,
                              uint8_t r, uint8_t g, uint8_t b, float a) {

        int contentLength = content.length();
        int yNextposition = column;

        for (int i = 0; i < contentLength; i++) {
            drawChar((int)content[i], line, yNextposition, r, b, g, a);
            yNextposition += CHAR_WIDTH + OFFSET_BETWEEN_CAHRS;
        }
    }

}
