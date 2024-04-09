#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>

typedef struct _display_struct {
    spi_inst_t* spi;
    int8_t sck;
    int8_t cs;
    int8_t dc;
    int8_t mosi;
    int8_t rst;
    int16_t width;
    int16_t height;
} display_struct;

int16_t Color565(int8_t r, int8_t g, int8_t b);

// Initialize and De-initialize
display_struct* Init(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t rst, int16_t width, int16_t height);
void Deinit(display_struct* current_display);

// Functions
void Clear(display_struct* current_display, int16_t color);

#endif