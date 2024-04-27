#ifndef SCREEN_H
#define SCREEN_H

#include "ili9341.h"

#define SIZE (ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH)

class Screen{
    private:
        uint16_t height;
        uint16_t width;
        uint16_t screen_buffer[SIZE];

    public:
        Screen();
        ~Screen();
        void ClearScreen(uint16_t color);
        void DrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, bool fill);
        void DrawRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color, bool fill);
        void DrawImage(uint16_t x, uint16_t y/*image*/);
        void Render();
};

uint16_t ConvertColor565(uint8_t r, uint8_t g, uint8_t b);

#endif