#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pico/mem_ops.h>

#include "screen.h"
#include "ili9341.h"
#include "image.h"

uint16_t ConvertColor565(uint8_t r, uint8_t g, uint8_t b){
	// Reminder pico is little endian
	uint16_t color = (r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3;
	return (color << 8) | (color >> 8);
}

Screen::Screen(){
	width = ILI9341_TFTWIDTH;
	height = ILI9341_TFTHEIGHT;
	ili9341_config = {
		.port = spi1,
		.pin_miso = 6,
		.pin_cs = 9,
		.pin_sck = 14,
		.pin_mosi = 15,
		.pin_reset = 10,
		.pin_dc = 13
		};

    printf("Screen Init\n");
    ili9341_init();

}


Screen::~Screen(){

}

uint16_t Screen::GetWidth(){
	return width;
}

uint16_t Screen::GetHeight(){
	return height;
}

int Screen::GetPosition(int x, int y){
	return y*width + x;
}

void Screen::ClearScreen(uint16_t color){
	if(color == 0){
		memset(screen_buffer, color, SIZE*sizeof(uint16_t));
	} else {
		for(int index=0; index<SIZE; index++){
			screen_buffer[index] = color;
		}
	}
}

void Screen::DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	// Bresenham Line Algorithm
	// We need x1 <x2 and y1 < y2
	if(x1 > x2){
		uint16_t temp=x1;
		x1 = x2;
		x2 = temp;
	}

	if(y1 > y2){
		uint16_t temp = y1;
		y1 = y2;
		y2 = temp;
	}

	// check whether vertical or horizontal
	if(x1 == x2){
		// vertical line
		for(int index=y1; index<y2; ++index){
			screen_buffer[index*width + x1] = color;
		}
		return;

	} else if(y1 == y2){
		// horizontal line
		for(int index=x1; index<x2; ++index){
			screen_buffer[y1*width + index] = color;
		}

		return;
	}

	int m_new = 2 * (y2 - y1); 
    int slope_error_new = m_new - (x2 - x1); 
    for (int x = x1, y = y1; x <= x2; x++) {
		screen_buffer[y*width + x] = color; 
  
        // Add slope to increment angle formed 
        slope_error_new += m_new; 
  
        // Slope error reached limit, time to 
        // increment y and update slope error. 
        if (slope_error_new >= 0) { 
            y++; 
            slope_error_new -= 2 * (x2 - x1); 
        } 
    } 
}

// https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C
void Screen::DrawCircle(int xc, int yc, int radius, uint16_t color, bool fill){
	int f = 1 - radius;
	int ddF_x = 0;
	int ddF_y = -2 * radius;
	int x = 0;
	int y = radius;

	// Plot initial pixels (0,90,180,270)
	if(fill){
		DrawLine(xc-radius, yc,xc+radius,yc,color);
	} else {
		screen_buffer[GetPosition(xc, yc+radius)] = color;
		screen_buffer[GetPosition(xc, yc-radius)] = color;
		screen_buffer[GetPosition(xc+radius, yc)] = color;
		screen_buffer[GetPosition(xc-radius, yc)] = color;
	}

	while(x < y){
		if(f >= 0){
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x + 1;
		if(fill){
			DrawLine(xc-x,yc+y,xc+x,yc+y,color);
			DrawLine(xc-x,yc-y,xc+x,yc-y,color);
			DrawLine(xc-y,yc+x,xc+y,yc+x,color);
			DrawLine(xc-y,yc-x,xc+y,yc-x,color);
		} else {
			screen_buffer[GetPosition(xc+x, yc+y)] = color;
			screen_buffer[GetPosition(xc-x,yc+y)] = color;
			screen_buffer[GetPosition(xc+x,yc-y)] = color;
			screen_buffer[GetPosition(xc-x,yc-y)] = color;
			screen_buffer[GetPosition(xc+y,yc+x)] = color;
			screen_buffer[GetPosition(xc-y, yc+x)] = color;
			screen_buffer[GetPosition(xc+y,yc-x)] = color;
			screen_buffer[GetPosition(xc-y,yc-x)] = color;
		}
	}
}

void Screen::DrawRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color, bool fill){
	/*uint16_t x1 = start_x < 0 ? 0 : start_x;
	uint16_t x2 = end_x >= width ? width-1 : end_x;
	uint16_t y1 = start_y < 0 ? 0 : start_y;
	uint16_t y2 = end_y >= height ? height-1 : end_y;*/

	// Filled Rectangle
	if(fill){
		for(int y=start_y; y<end_y; ++y){
			for(int x=start_x; x<end_x; ++x){
				screen_buffer[GetPosition(x,y)] = color;
			}
		}
	} else{
		// Not filled
		DrawLine(start_x, start_y, end_x, start_y, color);
		DrawLine(end_x, start_y, end_x, end_y, color);
		DrawLine(start_x, end_y, end_x, end_y, color);
		DrawLine(start_x, start_y,start_x, end_y, color);
	}
}

void Screen::DrawImage(uint16_t xs, uint16_t ys, Image* p_image){
	uint8_t* current_offset = p_image->GetImageOffset();
	uint8_t current_pixel;

	for(int y=0; y<p_image->GetHeight(); ++y){
		for(int x=0; x<p_image->GetWidth(); x+=2){
			if((uint8_t)(*current_offset) != 0)
			{
				current_pixel = (uint8_t)(*current_offset);
				screen_buffer[GetPosition(xs+x,ys+y)] = p_image->GetPaletteColor(current_pixel >> 4);
				screen_buffer[GetPosition(xs+x+1,ys+y)] = p_image->GetPaletteColor(current_pixel & 0xf);
			}
			current_offset++;
		}
	}
}

void Screen::Render(){
    ili9341_start_writing();
	ili9341_write_data_continuous(screen_buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
}
    