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

Image::~Image(){
    if(&fil != NULL){
        f_close(&fil);
    }

    if(palette != NULL){
        free(palette);
    }
}

uint16_t Image::GetHeight(){
    return height;
}

uint16_t Image::GetWidth(){
    return width;
}

uint8_t* Image::GetImageOffset(){
    return image;
}

void Image::LoadImage(const char* filename){
    bool done = false;
    UINT bytes_read=0;
    uint8_t buffer[FLASH_SECTOR_SIZE];
    int read_len = FLASH_SECTOR_SIZE;

    printf("Number of SD cards: %i\n", sd_get_num());
    // Get pointer to SD card image
    sd_card_t *pSD=sd_get_by_num(0);
    
    FRESULT fr=f_mount(&pSD->fatfs,pSD->pcName,1);
    if (FR_OK!=fr) {
		printf("E f_mount error: %s (%d)\n",FRESULT_str(fr),fr);
		return;
	}

	fr=f_open(&fil,filename,FA_READ);

    if(fr != FR_OK){
        printf("Open failed\n");
        return;
    }

    printf("Reading Height and Width\n");
    // Read the height and width
    fr = f_read(&fil,&height,2,&bytes_read);
    fr = f_read(&fil,&width,2,&bytes_read);

    printf("Reading the palette\n");
    // Read the color palette
    // Step 1: Get the number of colors in the palette
    fr = f_read(&fil,&num_colors,2,&bytes_read);

    palette = (uint16_t*)malloc(sizeof(uint16_t)*num_colors);
    fr = f_read(&fil,palette,sizeof(uint16_t)*num_colors,&bytes_read);
    alpha = palette[0];

    // Palette in file is little endian, but screen is big endian, so we need to flip the bytes
    for(int palette_index=0; palette_index<num_colors; ++palette_index){
        uint16_t current_color = palette[palette_index];
        palette[palette_index] = ((current_color & 0xff) << 8) | (current_color >> 8);
    }

    image = (uint8_t*)(XIP_BASE + offset);

    printf("Storing this image at: %08x\n",image);
    printf("====================================\n");

    while(!done){
        f_read(&fil, buffer, read_len, &bytes_read);

        if(bytes_read < read_len){
            done = true;
        }

        // Not sure if necessary, but recommended to save interrupts
        uint32_t interrupts = save_and_disable_interrupts();
        flash_range_erase(offset,FLASH_SECTOR_SIZE);
        flash_range_program(offset,(const uint8_t*)buffer,bytes_read);
        restore_interrupts(interrupts);

        offset += FLASH_SECTOR_SIZE;
    }

    printf("Done Reading: %08x\n",offset);
    printf("====================================\n");

    f_close(&fil);
    f_unmount(pSD->pcName);
}

uint16_t Image::GetPaletteColor(uint8_t index){
    if(index < num_colors){
        return palette[index];
    }
    
    return 0;
}