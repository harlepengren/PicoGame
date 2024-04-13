#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/spi.h"

//#include "display/display.h"
#include "ili9341/ili9341.h"
#include "ili9341/mode2.h"

using namespace std;

int main()
{
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

    uint16_t x = 0;
    while(1){
        mode2_clear();
        mode2_rect(x,40,40,80,0xFFFF);
        mode2_render();

        x+=1;
        x = x%280;
    }


    return 0;
}