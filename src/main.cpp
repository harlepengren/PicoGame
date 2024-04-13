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
    /*
    spi_inst_t *spi = spi1;
    uint8_t rst_pin = 10;
    uint8_t sck_pin = 14;
    uint8_t cs_pin = 9;
    uint8_t dc_pin = 13;
    uint8_t mosi_pin = 15;
    uint16_t width = 240;
    uint16_t height = 320;

    // Test blinking code
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    stdio_init_all();

    sleep_ms(2000);

    Display current_display(spi0, cs_pin, dc_pin, sck_pin, mosi_pin, rst_pin, width, height);
    printf("Display Created . . .\n");

    current_display.ClearScreen(Color565(255,0,0));
    printf("Screen cleared");

    while(1){
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }*/

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