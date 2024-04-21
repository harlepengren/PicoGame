#include <stdio.h>
#include <stdlib.h>

#include "hardware/flash.h"
#include "ff.h"

#ifndef IMAGE_H
#define IMAGE_H

#define FLASH_TARGET_OFFSET (1024*1024)

class Image{
    private:
        uint16_t* palette;
        uint16_t num_colors;
        uint8_t* image;
        FIL fil;
        //FILE* fp;
        uint32_t image_position;
        uint16_t height;
        uint16_t width;

    public:
        ~Image();
        void LoadImage(const char* filename);
        void ReadIntoBuffer(uint16_t x, uint16_t y, uint16_t buffer_width, uint16_t buffer_height);
};

#endif