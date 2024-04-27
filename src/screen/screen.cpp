#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "screen.h"
#include "ili9341.h"

uint16_t ConvertColor565(uint8_t r, uint8_t g, uint8_t b){
	return (r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3;
}

Screen::Screen(){
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

void Screen::ClearScreen(uint16_t color){
    memset(screen_buffer, color, SIZE*sizeof(uint16_t));
}

void Screen::DrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint16_t color, bool fill){

}

void Screen::DrawRectangle(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color, bool fill){

}

void Screen::DrawImage(uint16_t x, uint16_t y/*image*/){

}

void Screen::Render(){
    ili9341_start_writing();
	ili9341_write_data_continuous(screen_buffer, SIZE);
	ili9341_stop_writing();
}

    