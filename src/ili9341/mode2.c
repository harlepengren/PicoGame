#include <string.h>

#include "pico/mem_ops.h"
#include "mode2.h"

#define SIZE (ILI9341_TFTHEIGHT*ILI9341_TFTWIDTH)

uint16_t mode2_buffer[SIZE] = { 0 };
uint16_t color_palette[16] = {0};

void mode2_init() {
}

void mode2_set_color_palette(uint8_t palette_entry, uint16_t color){
	// 0x00 is reserved for transparent
	if(palette_entry > 0 && palette_entry < 16){
		color_palette[palette_entry] = color;
	}
}

void mode2_clear() {
    memset(mode2_buffer, 0, SIZE*sizeof(uint16_t));
}

void mode2_draw_pixel(uint16_t x, uint16_t y, uint16_t color){
	if(x < 0 || x >= ILI9341_TFTWIDTH || y < 0 || y >= ILI9341_TFTHEIGHT || color == 0){
		return;
	}

	mode2_buffer[x*ILI9341_TFTWIDTH+y] = color;
}

// The image must be  an even width
void mode2_draw_image(uint16_t x, uint16_t y, uint16_t width, uint8_t* data, int data_len){
	uint16_t current_x = x;
	uint16_t current_y = y;
	uint16_t pixel_color[2];

	for(int index=0; index<data_len; index++){
		pixel_color[0] = color_palette[data[index] >> 4];
		pixel_color[1] = color_palette[data[index] & 0xFF];

		mode2_draw_pixel(current_x,current_y,pixel_color[0]);
		current_x++;
		mode2_draw_pixel(current_x,current_y,pixel_color[1]);
		current_x++;

		if((index*2) % width == 0){
			current_y += 1;
		}
	}
}

void mode2_draw_line(uint16_t x, uint16_t y, uint8_t* data, int data_len){
	// Line is outside the screen, don't draw
	if(y < 0 || y > ILI9341_TFTHEIGHT){
		return;
	}

	// where should we start and end
	uint16_t offset = 0;
	uint16_t start_x = x;
	uint16_t width = data_len;
	if(x < 0){
		start_x = 0;
		offset = start_x - x;

		// if the offset is odd, then skip 1 pixel (the second half of 1 byte)
		if(offset % 2 == 1){
			offset +=1;
		}
	} else if(x > ILI9341_TFTWIDTH){
		width -= (uint16_t)((x - ILI9341_TFTWIDTH)/2);
	}

	for(int index=offset; index<width; index++){
		mode2_draw_pixel(start_x+(index*2), y, color_palette[data[index] >> 4]);
		mode2_draw_pixel(start_x+(index*2)+1, y, color_palette[data[index] & 0xFF]);
	}

	// Base case, line is fully in the screen space
	// Alternative cases: x < 0, x >ILI9341_TFTWIDTH

}

void mode2_rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t color) {
	uint16_t *base_loc = &mode2_buffer[x*ILI9341_TFTWIDTH+y];

	for (int h=0; h<width; h++) {
	    uint16_t *loc = base_loc + h*ILI9341_TFTWIDTH;
    	for (int v=0; v<height; v++) {
			*loc++ = color;
    	}
	}
}

void mode2_render() {
    ili9341_start_writing();
	ili9341_write_data_continuous(mode2_buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
}

