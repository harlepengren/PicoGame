#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/malloc.h>
#include <hardware/flash.h>
#include <string.h>

#include "mode2.h"
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

void Image::LoadImage(const char* filename){
    UINT bytes_read=0;
    uint16_t buffer[FLASH_SECTOR_SIZE/2];
    uint8_t temp_buffer[FLASH_SECTOR_SIZE/2];
    int read_len = FLASH_SECTOR_SIZE/2;
    uint offset;

    printf("Number of SD cards: %i\n", sd_get_num());
    // Get pointer to SD card image
    sd_card_t *pSD=sd_get_by_num(0);
    printf("Check config file: %i\n", pSD->ss_gpio);
    
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
    //height = (uint16_t)(fgetc(fp) << 8 | fgetc(fp));
    fr = f_read(&fil,&width,2,&bytes_read);
    //width = (uint16_t)(fgetc(fp) << 8 | fgetc(fp));

    printf("Reading the palette\n");
    // Read the color palette
    // Step 1: Get the number of colors in the palette
    fr = f_read(&fil,&num_colors,2,&bytes_read);
    //num_colors = (uint16_t)fgetc(fp);

    palette = (uint16_t*)malloc(sizeof(uint16_t)*num_colors);

    fr = f_read(&fil,palette,sizeof(uint16_t)*num_colors,&bytes_read);
    /*for(uint8_t index=0; index<num_colors; ++index){
        palette[index] = ((uint8_t)fgetc(fp) << 8) | (uint8_t)fgetc(fp);
    }*/

    image_position = (uint32_t)f_tell(&fil);
    offset = FLASH_TARGET_OFFSET;

    printf("reading the image data\n");
    bool done = false;
    bool first = true;
    while(!done){
        f_read(&fil, temp_buffer, read_len, &bytes_read);


        if(bytes_read < read_len){
            done = true;
        }

        for(int index=0; index<bytes_read; ++index){
            buffer[index] = palette[temp_buffer[index]];

        }

        if(first){
            for(int temp_index=0; temp_index< bytes_read; ++temp_index){
                printf("%08x ", buffer[temp_index]);
            }
            printf("/n");
            first = false;
        }

    /*for(int index=0; index<(height*width/2); index+=bytes_read){
        f_read(&fil, buffer, sizeof(buffer), &bytes_read);
        if(bytes_read == 0){
            printf("Problem\n");
            break;
        }*/

        flash_range_erase(offset,bytes_read*2);
        flash_range_program(offset,(const uint8_t*)buffer,bytes_read*2);

        offset += bytes_read*2;
    }

    printf("Done Reading: %n",offset-FLASH_TARGET_OFFSET);
    printf("====================================================");

    f_close(&fil);
    f_unmount(pSD->pcName);
}

void Image::ReadIntoBuffer(uint16_t x, uint16_t y, uint16_t buffer_width, uint16_t buffer_height){
    //uint16_t line_pixels = width;
    //uint8_t* line = (uint8_t*)malloc(width);

    // Set the flash offset
    uint offset = XIP_BASE + FLASH_TARGET_OFFSET;

    for(int index=0; index<height; ++index){
        mode2_draw_line(x,y+index,(uint8_t*)offset,width*2);

        // Mulitply by 2 since there are 16bpp.
        offset += width*2;
    }

    //free(line);
}