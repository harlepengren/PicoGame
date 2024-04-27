#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pico/mem_ops.h>

#include "screen.h"
#include "ili9341.h"

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

void Screen::PlotCirclePoints(uint16_t xc, uint16_t yc, uint16_t x, uint16_t y, uint16_t color){
	screen_buffer[(yc+y)*width + (xc+x)] = color;
	screen_buffer[(yc+y)*width + (xc-x)] = color;
	screen_buffer[(yc-y)*width + (xc+x)] = color;
	screen_buffer[(yc-y)*width + (xc-x)] = color;
	screen_buffer[(yc+x)*width + (xc+y)] = color;
	screen_buffer[(yc+x)*width + (xc-y)] = color;
	screen_buffer[(yc-x)*width + (xc+y)] = color;
	screen_buffer[(yc-x)*width + (xc-y)] = color;
}

void Screen::DrawCircle(uint16_t xc, uint16_t yc, uint16_t radius, uint16_t color, bool fill){
	uint16_t x = 0, y = radius;
    uint16_t d = 3 - 2 * radius;
    PlotCirclePoints(xc, yc, x, y,color);
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
        
        x++;

        // check for decision parameter
        // and correspondingly 
        // update d, x, y
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        PlotCirclePoints(xc, yc, x, y,color);
    }
}

void Screen::DrawRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color, bool fill){
	/*uint16_t x1 = start_x < 0 ? 0 : start_x;
	uint16_t x2 = end_x >= width ? width-1 : end_x;
	uint16_t y1 = start_y < 0 ? 0 : start_y;
	uint16_t y2 = end_y >= height ? height-1 : end_y;*/

	for(int y=start_y; y<end_y; ++y){
		for(int x=start_x; x<end_x; ++x){
			int pixel = y*width + x;
			screen_buffer[pixel] = color;
		}
	}
}

void Screen::DrawImage(uint16_t x, uint16_t y/*image*/){

}

void Screen::Render(){
    ili9341_start_writing();
	ili9341_write_data_continuous(screen_buffer, SIZE*sizeof(uint16_t));
	ili9341_stop_writing();
}
    