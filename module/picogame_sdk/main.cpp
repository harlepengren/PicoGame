#ifndef PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS
#define PICO_STDIO_USB_CONNECT_WAIT_TIMEOUT_MS (5000)
#endif

#include <stdio.h>

#include <pico/stdio.h>
#include <pico/time.h>
#include <hardware/spi.h>
#include <pico/multicore.h>
#include <hardware/timer.h>

#include "screen/screen.h"
#include "screen/image.h"
#include "input/input.h"

using namespace std;

#define PICO_GAME_DEBUG

void ButtonCallback(){
    printf("Button pressed\n");
}

int main()
{
    stdio_init_all();

    #ifdef PICO_GAME_DEBUG
    multicore_reset_core1();
    #endif

    sleep_ms(2000);

    printf("Now to init the sd card\n");

    int16_t x = 50;
    int16_t y = 75;
    int8_t x_direction = 1;
    int8_t y_direction = 1;

    Image ball;
    Screen current_screen;
    ball.LoadImage("test_circle.bin");

    Image magenta;
    magenta.LoadImage("magenta.bin");

    uint16_t background_color = ConvertColor565(255,0,0);

    Input controller;

    uint64_t current_time = time_us_64();
    uint16_t fixed_time_update = 33333;     // 1e6/30 - fixes the framerate at 30 fps

    while(1){
        if(time_us_64() > current_time + fixed_time_update){
            current_time = time_us_64();
            // Process Inputs
            controller.ProcessInputs();

            current_screen.ClearScreen(background_color);
            current_screen.DrawRectangle(x,75,x+50,150);
            current_screen.DrawLine(0,0,current_screen.GetWidth(),current_screen.GetHeight(),ConvertColor565(0,0,255));
            current_screen.DrawLine(0,100,100,100,0xffff);
            current_screen.DrawCircle(120,160,100,0xffff,false);
            current_screen.DrawCircle(120,160,50,0xff07,true);
            current_screen.DrawImage(110,y,&ball);
            current_screen.DrawImage(10,10,&magenta);
            current_screen.Render();

            x += 10 * x_direction;
            if(x+50 > current_screen.GetWidth()){
                x = current_screen.GetWidth() - 50;
                x_direction *= -1;
            } else if(x < 0){
                x = 0;
                x_direction *= -1;
            }

            y += 10 *y_direction;
            if(y+50 > current_screen.GetHeight()){
                y = current_screen.GetHeight() - 50;
                y_direction *= -1;
            } else if (y< 0){
                y=0;
                y_direction *= -1;
            }

        }
    }

    return 0;
}
