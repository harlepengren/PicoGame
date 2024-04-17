#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/spi.h"

//#include "display/display.h"
#include "ili9341/ili9341.h"
#include "ili9341/mode2.h"
#include "image.h"

using namespace std;



int main()
{
    stdio_init_all();

    ili9341_config = {
	.port = spi1,
	.pin_miso = 6,
	.pin_cs = 9,
	.pin_sck = 14,
	.pin_mosi = 15,
	.pin_reset = 10,
	.pin_dc = 13
    };

    ili9341_init();
    mode2_init();

    int16_t x = 50;
    int16_t y = 75;
    int8_t x_direction = 1;
    int8_t y_direction = 1;

    Image ball;
    ball.LoadImage("test_circle.bin");

    while(1){
        /*mode2_clear();
        mode2_rect(x,40,40,80,0xFFFF);
        mode2_draw_pixel(pixel_x,pixel_y,pixel_color);
        mode2_render();

        x+=1;
        x = x%280;

        pixel_x = (pixel_x + 27) % 280;
        pixel_y = (pixel_y + 54) % 280;
        pixel_color = (pixel_color + 10) % 0xFFFF;*/

        ball.ReadIntoBuffer(x,y,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);

        mode2_render();

        x + = 10*direction;
        y += 15;

        if (x < 0 || x > (ILI9341_TFTWIDTH-32)){
            x_direction *= -1;
        }

        if (y < 0 || y > (ILI9341_TFTHEIGHT-32)){
            y_direction *= -1;
        }
    }


    return 0;
}