#include <stdlib.h>

#include "pico/stdlib.h"
#include "pico/malloc.h"

#include "image.h"

Image::~Image(){
    if(fp != NULL){
        fclose(fp);
    }

    if(palette != NULL){
        free(palette);
    }
}

void Image::PrepareImage(const char* filename){
    fp = fopen(filename, "r");

    // Read the height and width
    height = (uint16_t)(fgetc(fp) << 8 | fgetc(fp));
    width = (uint16_t)(fgetc(fp) << 8 | fgetc(fp));

    // Read the color palette
    // Step 1: Get the number of colors in the palette
    num_colors = (uint16_t)fgetc(fp);

    palette = (uint16_t*)malloc(sizeof(uint16_t)*num_colors);

    for(uint8_t index=0; index<num_colors; ++index){
        palette[index] = ((uint8_t)fgetc(fp) << 8) | (uint8_t)fgetc(fp);
    }

    image_position = (uint32_t)ftell(fp);
    offset = 0;
}

void Image::ImageBegin(){
    fseek(fp,image_position,SEEK_SET);
    offset = 0;
}

bool Image::EndOfFile()
{
    if(offset > height*width/2){
        return true;
    }

    return false;
}

// TO DO: Add Error Checking to make sure we are not EOF
uint8_t Image::ReadByte(){
    char next_byte = fgetc(fp);
    offset += 1;

    return (uint8_t)next_byte;
}