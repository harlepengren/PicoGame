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

    //Image ball;
    Screen current_screen;
    //ball.LoadImage("test_circle.bin");

    uint16_t background_color = ConvertColor565(255,0,0);

    while(1){
        current_screen.ClearScreen(background_color);
        current_screen.DrawRectangle(x,y,x+50,y+50);
        current_screen.DrawLine(0,0,current_screen.GetWidth(),current_screen.GetHeight(),ConvertColor565(0,0,255));
        current_screen.DrawLine(0,100,100,100,0xffff);
        current_screen.DrawCircle(120,160,50,0xffff);
        current_screen.Render();

        x += 10 * x_direction;
        if(x+50 > current_screen.GetWidth()){
            x = current_screen.GetWidth() - 50;
            x_direction *= -1;
        } else if(x < 0){
            x = 0;
            x_direction *= -1;
        }
    }

    return 0;
}