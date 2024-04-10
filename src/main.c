#include "pico/stdlib.h"
#include "hardware/spi.h"

#include "display/display.h"

int main()
{
    display_struct* current_display;
    spi_inst_t *spi = spi1;
    uint8_t rst_pin = 10;
    uint8_t sck_pin = 14;
    uint8_t cs_pin = 9;
    uint8_t dc_pin = 13;
    uint8_t mosi_pin = 15;

    current_display = display_init(spi0, cs_pin, dc_pin, sck_pin, mosi_pin, rst_pin, 240, 320);
    display_clear_screen(current_display, Color565(255,0,0),current_display->height);
    display_deinit(current_display);

    return 0;
}