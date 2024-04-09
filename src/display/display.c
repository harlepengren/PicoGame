#include <stdlib.h>

#include "display.h"
#include "hardware/spi.h"

int16_t Color565(int8_t r, int8_t g, int8_t b){
    return (int16_t)((r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3);
}

// Initialize and De-initialize
display_struct* Init(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t rst, int16_t width, int16_t height){
    display_struct* current_display = (display_struct*)malloc(sizeof(display_struct));

    current_display->spi = spi;
    current_display->cs = cs;
    current_display->dc = dc;
    current_display->rst = rst;
    current_display->width = width;
    current_display->height = height;

    spi_init(spi,40000000);

    return current_display;
}

void Deinit(display_struct* current_display){
    spi_deinit(current_display->spi);
    free(current_display);
}

// Functions
void Clear(display_struct* current_display, int16_t color);