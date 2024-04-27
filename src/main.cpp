#ifndef PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS
#define PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS (5000)
#endif

#include <stdio.h>

#include <pico/stdio.h>
#include <pico/stdlib.h>
#include <pico/time.h>
#include <hardware/spi.h>
#include <pico/multicore.h>

#include "screen/screen.h"
#include "ili9341/image.h"

using namespace std;

#define PICO_GAME_DEBUG

int main()
{
    stdio_init_all();

    #ifdef PICO_GAME_DEBUG
    multicore_reset_core1();
    #endif

    sleep_ms(2000);

    printf("now to init the sd card\n");

    int16_t x = 50;
    int16_t y = 75;
    int8_t x_direction = 1;
    int8_t y_direction = 1;

    Image ball;
    Screen current_screen;
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

        //ball.ReadIntoBuffer(x,y,ILI9341_TFTWIDTH,ILI9341_TFTHEIGHT);

        current_screen.ClearScreen(0xFA00);
        current_screen.Render();

        /*x += 10*x_direction;
        y += 15*y_direction;

        if (x < 0 || x > (ILI9341_TFTWIDTH-32)){
            x_direction *= -1;
        }

        if (y < 0 || y > (ILI9341_TFTHEIGHT-32)){
            y_direction *= -1;
        }*/
    }


    return 0;
}