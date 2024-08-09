#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <hardware/flash.h>
#include <string.h>

// TODO: Remove
// I wanted to keep the sdk seperate from micropython
// however, I need for now to debug.
#include "py/runtime.h"
#include "py/obj.h"
#include "py/mpprint.h"

#include "image.h"
#include "ff.h"
#include "f_util.h"
#include "hw_config.h"

uint GetOffset(){
    return UpdateOffset(0);
}

uint UpdateOffset(uint addOffset){
    static uint offset = FLASH_TARGET_OFFSET;

    offset += addOffset;

    return offset;
}

int LoadImage(Image* p_image, const char* filename){
    sd_card_t *pSD = sd_get_by_num(0);
    FRESULT fr = f_mount(&pSD->fatfs, pSD->pcName, 1);
    if (FR_OK != fr) {
        mp_printf(MP_PYTHON_PRINTER, "f_mount error: %s (%d)\n",FRESULT_str(fr),fr);
    }

    return IMG_OK;
}

void CloseImage(Image* p_image){
    free(p_image);
    p_image = NULL;
}

uint16_t GetPaletteColor(Image* p_image, uint8_t index){
    if(index < p_image->num_colors){
        return p_image->palette[index];
    }
    
    return 0;
}

// Copies the image from the flash memory location into the screen buffer
void ReadIntoBuffer(Image* p_image, uint16_t* screen_buffer, uint16_t x, uint16_t y, uint16_t buffer_width, uint16_t buffer_height){
    // First, are we starting offscreen
    if(x > buffer_width || y > buffer_height){
        return;
    }

    uint16_t row_start = 0;
    if(x < 0){
        row_start = abs(x);
    }
    
    // Next, we need to know whether our width goes beyond the buffer_width
    uint16_t row_end = p_image->width;
    if(x + p_image->width > buffer_width){
        row_end = x + p_image->width - buffer_width;
    }
    
    // For each row, copy the row into the buffer
    for(int current_row = y; (current_row < buffer_height) && (current_row < y + p_image->height); current_row++){
        uint16_t* current_position = &screen_buffer[current_row * buffer_width + x];
        uint16_t* image_position = &p_image->image[((current_row - y) * p_image->width) + row_start];
        memcpy(current_position, image_position,row_end);
    }

}