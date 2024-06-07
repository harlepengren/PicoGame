#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "display.h"
#include "pico/time.h"
#include "hardware/spi.h"

int16_t Color565(int8_t r, int8_t g, int8_t b){
    return (int16_t)((r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3);
}

// Initialize and De-initialize
Display::Display(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t sck, int8_t mosi, int8_t rst, int16_t width, int16_t height){
    
    current_display.spi = spi;
    current_display.cs = cs;
    current_display.dc = dc;
    current_display.sck = sck;
    current_display.mosi = mosi;
    current_display.rst = rst;
    current_display.width = width;
    current_display.height = height;

    // Create the frame buffer: width * height * BIT_DEPTH
    current_display.buffer_size = width * height *BIT_DEPTH;
    current_display.frame_buffer = (uint8_t*)malloc(current_display.buffer_size);
    printf("Display buffer: %i\n", current_display.buffer_size);

    // Initialize CS pin
    printf("CS pin\n");
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);

    // Initialize DC pin
    printf("DC pin\n");
    gpio_init(dc);
    gpio_set_dir(dc, GPIO_OUT);
    gpio_put(dc, 0);

    // Initialize RST pin
    gpio_init(rst);
    gpio_set_dir(rst, GPIO_OUT);
    gpio_put(rst, 1);

    // Initialize SPI
    printf("SPI\n");
    uint baudrate = spi_init(spi,40000000);
    printf("SPI Baudrate: %i",baudrate);
    spi_set_format(spi,  // SPI instance spi0 or spi1
                   8,    // Number of bits per transfer
                   SPI_CPOL_1,    // Polarity (CPOL)
                   SPI_CPHA_1,    // Phase (CPHA)
                   SPI_MSB_FIRST);

    // Initialize SPI pins
    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);

    // Reset
    printf("Prepare to reset\n");
    Reset();

    // Initialization Commands
    printf("Start initialization commands\n");
    WriteCmd(SWRESET);
    sleep_ms(150);
    
    WriteCmd(0xEF, 3, 0x03, 0x80, 0x02);                // Unknown command. Not in datasheet but in adafruit implementation
    WriteCmd(PWCTRB, 3, 0x00, 0xC1, 0x30);              // Power control B
    WriteCmd(POSC, 4, 0x54, 0x03, 0x12, 0x81);          // Power on sequence control
    WriteCmd(DTCA, 3, 0x85, 0x00, 0x78);                // Driver timing control
    WriteCmd(PWCTRA, 5, 0x39, 0x2c, 0x00, 0x34, 0x02);  // Power control A
    WriteCmd(PUMPRC, 1, 0x20);                          // Pump ratio control
    WriteCmd(DTCB, 2, 0x00, 0x00);                      // Driver timing control B
    WriteCmd(PWCTR1, 1, 0x23);                          // Power control 1
    WriteCmd(PWCTR2, 1, 0x10);                          // Power control 2
    WriteCmd(VMCTR1, 2, 0x3E, 0x28);                    // VCOM ctrl 1
    WriteCmd(VMCTR2, 1, 0x86);                          // VCOM ctrl 2
    WriteCmd(MADCTL,1, 0x88);                           // Memory access control
    WriteCmd(VSCRSADD, 1, 0x00);                        // Vertical scrolling start address
    WriteCmd(PIXFMT, 1, 0x55);                          // Set pixel format (16 bpp)
    WriteCmd(FRMCTR1, 2, 0x00, 0x18);                   // Frame rate control
    WriteCmd(DFUNCTR, 3, 0x08, 0x82, 0x27);             // Display function control
    WriteCmd(ENABLE3G, 1, 0x00);                        // Disable 3 gamma ctrl
    WriteCmd(GAMMASET, 1, 0x01);                        // Gamma curve selected
    WriteCmd(GMCTRP1, 15, 0x0F, 0x31, 0x2B, 0x0C,       // Set Gamma
                    0x0E, 0x08, 0x4E, 0xF1, 0x37,
                    0x07, 0x10, 0x03, 0x0E, 0x09,
                    0x00);
    WriteCmd(GMCTRN1, 15, 0x00, 0x0E, 0x14, 0x03,
            0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F,
            0x0C, 0x31, 0x36, 0x0F);
    WriteCmd(SLEEP_OUT);   // Exit Sleep
    sleep_ms(5);
    WriteCmd(DISPLAY_ON);
    sleep_ms(5);
    WriteCmd(NOP);

    printf("Finished initialization\n");
}

Display::~Display(){
    spi_deinit(current_display.spi);
    free(current_display.frame_buffer);
}

void Display::Reset(){
    gpio_put(current_display.rst,0);
    sleep_ms(150);
    gpio_put(current_display.rst,1);
}

// Functions
void Display::WriteBlock(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1, uint8_t* data, int data_len){
    /*Write a block of data to display.

    Args:
        x0 (int):  Starting X position.
        y0 (int):  Starting Y position.
        x1 (int):  Ending X position.
        y1 (int):  Ending Y position.
        data (bytes): Data buffer to write.*/

    
    WriteCmd(SET_COLUMN, 4, x0 >> 8, x0 & 0xff, x1 >> 8, x1 & 0xff);
    WriteCmd(SET_PAGE, 4, y0 >> 8, y0 & 0xff, y1 >> 8, y1 & 0xff);
    WriteCmd(WRITE_RAM);
    WriteData(data, data_len);
}

void Display::ClearScreen(uint16_t color){
    for(int y=0; y<current_display.height; y++){
        for(int x=0; x<current_display.width; x++){
            WriteData16(&color,1);
        }
    }
}

// Write a command without arguments
void Display::WriteCmd(uint8_t command){
    gpio_put(current_display.dc, 0);
    gpio_put(current_display.cs, 0);
    spi_write_blocking(current_display.spi,&command,1);
    gpio_put(current_display.cs, 1);
}

// Write a command with arguments
void Display::WriteCmd(uint8_t command, uint8_t arg_count, ...){
    gpio_put(current_display.dc, 0);
    gpio_put(current_display.cs, 0);
    spi_write_blocking(current_display.spi,&command,1);
    gpio_put(current_display.cs, 1);

    if(arg_count > 0){
        va_list valist;

        va_start(valist, arg_count);
        for(int index=0; index<arg_count; ++index){
            uint8_t cmd_arg = (uint8_t)va_arg(valist, int);
            WriteData(&cmd_arg, sizeof(cmd_arg));
        }

        va_end(valist);
    }
}

void Display::WriteData(uint8_t* data, int data_len){
    gpio_put(current_display.dc, 1);
    gpio_put(current_display.cs, 0);
    int num_bytes = spi_write_blocking(current_display.spi,data,data_len);
    printf("%i bytes written\n");
    gpio_put(current_display.cs, 1);
}

// Note this is data in 16 bits - e.g., data_len of 2 bytes is 1
void Display::WriteData16(uint16_t* data, int data_len){
    gpio_put(current_display.dc, 1);
    gpio_put(current_display.cs, 0);
    spi_write16_blocking(current_display.spi,data,data_len);
    gpio_put(current_display.cs, 1);
}