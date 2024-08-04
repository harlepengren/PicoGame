#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>
#include <stdlib.h>

#include <hardware/flash.h>

#include "ff.h"
#include "py/misc.h"

#define FLASH_TARGET_OFFSET (1024*1024)
#undef MICROPY_DEBUG_VERBOSE
#define MICROPY_DEBUG_VERBOSE (1)

// TO DO: Eventually, change this into assets (e.g., images and audio) instead of just images.
// However, not a high priority since the game system does not have audio output yet.

typedef struct {
    uint16_t* palette;
    uint16_t num_colors;
    uint16_t* image;
    FIL fil;
    uint16_t height;
    uint16_t width;
    uint image_offset;
    uint16_t alpha;
} Image;

uint GetOffset();
uint UpdateOffset(uint addOffset);
Image* LoadImage(const char* filename);
void CloseImage(Image* p_image);
uint16_t GetPaletteColor(Image* p_image, uint8_t index);
void ReadIntoBuffer(Image* p_image, uint16_t* screen_buffer, uint16_t x, uint16_t y, uint16_t buffer_width, uint16_t buffer_height);

#endif