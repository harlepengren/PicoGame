#include <stdio.h>
#include <malloc.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "py/dynruntime.h"
#include "display_ili9341.h"
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SET_COLUMN 0x2A  // Column address set
#define SET_PAGE 0x2B    // Page address set
#define WRITE_RAM 0x2C   // Memory write

struct display_struct
{
    spi_inst_t *spi;
    uint cs;
    uint sck;
    uint mosi;
    uint miso;
};

void write_cmd(display_struct* p_display, uint8_t command, uint8_t* args):
    /*Write command to display.

    Args:
        command (byte): ILI9341 command code.
        *args (optional bytes): Data to transmit.*/

    gpio_put(p_display->dc,0);
    gpio_put(p_display->cs,0);
    spi_write_blocking(p_display->spi, &command, 1);
    gpio_put(p_display->cs,1);

    // Handle any arguments - TO DO
}

int write_data(display_struct* p_display, uint16_t* data, size_t len)
{
    /* Write the data to the display

    Args:
        data(bytes): Data to transmit
    */

    gpio_put(p_display->dc,1);
    gpio_put(p_display->cs,0);
    int num_bytes = spi_write16_blocking(p_display->spi, data, len);
    gpio_put(p_display->cs,1);

    return num_bytes;
}


display_struct* init(uint spi_num, uint cs, uint dc, uint rst, uint mosi){
    display_struct* p_display = (display_struct*)malloc(sizeof(display_struct));

    if(spi_num ==0){
        p_display->spi = spi0;
    } else if{
        p_display->spi = spi1;
    }
    stdio_init_all();

    p_display->cs = cs;
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs,1)

    // Initialize SPI port
    spi_init(p_display->spi, 40000000);
    spi_set_format(p_display->spi, 16, 1, 1,SPI_MSB_FIRST);


    p_display->sck = sck;
    gpio_set_function(sck);

    p_display->mosi = mosi;
    gpio_set_function(mosi);


    return p_display;
}

void cleanup(p_display)
{
    spi_deinit(p_display->spi);

    if(p_display != null){
        free(p_display);
    }

}

void block(int x0, int y0, int x1, int y1, uint16_t* data){
    /*Write a block of data to display.

    Args:
        x0 (int):  Starting X position.
        y0 (int):  Starting Y position.
        x1 (int):  Ending X position.
        y1 (int):  Ending Y position.
        data (bytes): Data buffer to write.*/

    write_cmd(SET_COLUMN,
                x0 >> 8, x0 & 0xff, x1 >> 8, x1 & 0xff)
    write_cmd(SET_PAGE,
                y0 >> 8, y0 & 0xff, y1 >> 8, y1 & 0xff)
    write_cmd(WRITE_RAM)
    write_data(data)
    free(data)
}

void draw_vline(int x, int y, int h, int color)
{
    /*Draw a vertical line.

    Args:
        x (int): Starting X position.
        y (int): Starting Y position.
        h (int): Height of line.
        color (int): RGB565 color value.
    */
    // Confirm coordinates in boundary
    if(is_off_grid(x, y, x, y + h - 1)){
        return;
    }

    uint16_t* line;

    line = (uint16_t *)malloc(h*sizeof(uint16_t));
    memset(line,(uint16_t)color,h);
    
    block(x, y, x, y + h - 1, line)
}

void fill_circle(int x0, int y0, int r, int color) {
    /*Draw a filled circle.
    Args:
        x0 (int): X coordinate of center point.
        y0 (int): Y coordinate of center point.
        r (int): Radius.
        color (int): RGB565 color value.
    */
    int f = 1 - r
    int dx = 1
    int dy = -r - r
    int x = 0
    int y = r
    
    draw_vline(x0, y0 - r, 2 * r + 1, color)
    
    while(x < y)
    {
        if(f >= 0)
        {       
            y -= 1
            dy += 2
            f += dy
        }

        x += 1
        dx += 2
        f += dx

        draw_vline(x0 + x, y0 - y, 2 * y + 1, color)
        draw_vline(x0 - x, y0 - y, 2 * y + 1, color)
        draw_vline(x0 - y, y0 - x, 2 * x + 1, color)
        draw_vline(x0 + y, y0 - x, 2 * x + 1, color)
    }
}