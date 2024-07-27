#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/malloc.h>
#include <hardware/flash.h>
#include <string.h>

#include "image.h"
#include "ff.h"
#include "f_util.h"
#include "sd_card.h"
#include "hw_config.h"

Image* LoadImage(const char* filename){
    bool done = false;
    UINT bytes_read=0;

    // We will be storing 16 bits per color, so we need to read half of the sector size.
    uint8_t read_buffer[FLASH_SECTOR_SIZE/2];
    uint16_t write_buffer[FLASH_SECTOR_SIZE/2];
    int read_len = FLASH_SECTOR_SIZE / 2;   

    // Create an image
    Image* p_image;
    p_image = (Image*)malloc(sizeof(Image));

    printf("Number of SD cards: %i\n", sd_get_num());
    // Get pointer to SD card image
    sd_card_t *pSD=sd_get_by_num(0);
    
    FRESULT fr=f_mount(&pSD->fatfs,pSD->pcName,1);
    if (FR_OK!=fr) {
		printf("E f_mount error: %s (%d)\n",FRESULT_str(fr),fr);
        free(p_image);
		return null;
	}

	fr=f_open(&fil,filename,FA_READ);

    if(fr != FR_OK){
        printf("Open failed\n");
        free(p_image);
        p_image = null;
        return null;
    }

    printf("Reading Height and Width\n");
    // Read the height and width
    fr = f_read(&fil,&p_image->height,2,&bytes_read);
    fr = f_read(&fil,&p_image->width,2,&bytes_read);

    printf("Reading the palette\n");
    // Read the color palette
    // Step 1: Get the number of colors in the palette
    fr = f_read(&fil,&p_image->num_colors,2,&bytes_read);

    uint pallette_size = sizeof(uint16_t)*p_image->num_colors;
    p_image->palette = (uint16_t*)malloc(pallette_size);
    fr = f_read(&fil,p_image->palette,pallette_size,&bytes_read);
    alpha = p_image->palette[0];

    // Palette in file is little endian, but screen is big endian, so we need to flip the bytes
    for(int palette_index=0; palette_index<num_colors; ++palette_index){
        uint16_t current_color = p_image->palette[palette_index];
        p_image->palette[palette_index] = ((current_color & 0xff) << 8) | (current_color >> 8);
    }

    p_image->image = (uint8_t*)(XIP_BASE + offset);

    printf("Storing this image at: %08x\n",image);
    printf("====================================\n");

    while(!done){
        f_read(&fil, read_buffer, read_len, &bytes_read);

        if(bytes_read < read_len){
            done = true;
        }

        // For each byte, lookup the value in the color palette and record the result in the write_buffer
        for(int read_index=0; read_index<bytes_read; read_index++){
            uint16_t pixel = p_image->palette[read_buffer[read_index] >> 4];
            write_buffer[read_index*2] = pixel;
            pixel = p_image->palette[read_buffer[read_index] & 0xf];
            write_buffer[read_index*2 + 1] = pixel;
        }

        // Not sure if necessary, but recommended to save interrupts
        uint32_t interrupts = save_and_disable_interrupts();
        flash_range_erase(offset,FLASH_SECTOR_SIZE);
        flash_range_program(offset,(const uint8_t*)write_buffer,bytes_read);
        restore_interrupts(interrupts);

        offset += FLASH_SECTOR_SIZE;
    }

    printf("Done Reading: %08x\n",offset);
    printf("====================================\n");

    f_close(&fil);
    f_unmount(pSD->pcName);

    return p_image;
}

void CloseImage(Image* p_image){
    free(p_image);
    p_image = null;
}

uint16_t GetPaletteColor(Image* p_image, uint8_t index){
    if(index < num_colors){
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
        uint16_t* image_position = ((current_row - y) * p_image->width) + row_start;
        memcpy(current_position, p_image,row_end);
    }

}