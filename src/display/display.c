#include <stdlib.h>
#include <string.h>

#include "display.h"
#include "pico/time.h"
#include "hardware/spi.h"

int16_t Color565(int8_t r, int8_t g, int8_t b){
    return (int16_t)((r & 0xf8) << 8 | (g & 0xfc) << 3 | b >> 3);
}

// Initialize and De-initialize
display_struct* display_init(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t sck, int8_t mosi, int8_t rst, int16_t width, int16_t height){
    display_struct* current_display = (display_struct*)malloc(sizeof(display_struct));

    current_display->spi = spi;
    current_display->cs = cs;
    current_display->dc = dc;
    current_display->sck = sck;
    current_display->mosi = mosi;
    current_display->rst = rst;
    current_display->width = width;
    current_display->height = height;

    stdio_init_all();

    // Initialize CS pin
    gpio_init(cs);
    gpio_set_dir(cs, GPIO_OUT);
    gpio_put(cs, 1);

    // Initialize DC pin
    gpio_init(dc);
    gpio_set_dir(dc, GPIO_OUT);
    gpio_put(dc, 0);

    // Initialize RST pin
    gpio_init(rst);
    gpio_set_dir(rst, GPIO_OUT);
    gpio_put(rst, 1);

    // Initialize SPI
    spi_init(spi,40000000);
    spi_set_format(spi,  // SPI instance spi0 or spi1
                   8,    // Number of bits per transfer
                   1,    // Polarity (CPOL)
                   1,    // Phase (CPHA)
                   SPI_MSB_FIRST);

    // Initialize SPI pins
    gpio_set_function(sck, GPIO_FUNC_SPI);
    gpio_set_function(mosi, GPIO_FUNC_SPI);

    // Reset
    display_reset(current_display);

    // Initialization Commands
    display_write_cmd(current_display, SWRESET,NULL,0);
    sleep_ms(10);
    /********************************************
    self.write_cmd(self.SWRESET)  # Software reset
    sleep(.1)
    self.write_cmd(self.PWCTRB, 0x00, 0xC1, 0x30)  # Pwr ctrl B
    self.write_cmd(self.POSC, 0x64, 0x03, 0x12, 0x81)  # Pwr on seq. ctrl
    self.write_cmd(self.DTCA, 0x85, 0x00, 0x78)  # Driver timing ctrl A
    self.write_cmd(self.PWCTRA, 0x39, 0x2C, 0x00, 0x34, 0x02)  # Pwr ctrl A
    self.write_cmd(self.PUMPRC, 0x20)  # Pump ratio control
    self.write_cmd(self.DTCB, 0x00, 0x00)  # Driver timing ctrl B
    self.write_cmd(self.PWCTR1, 0x23)  # Pwr ctrl 1
    self.write_cmd(self.PWCTR2, 0x10)  # Pwr ctrl 2
    self.write_cmd(self.VMCTR1, 0x3E, 0x28)  # VCOM ctrl 1
    self.write_cmd(self.VMCTR2, 0x86)  # VCOM ctrl 2
    self.write_cmd(self.MADCTL, self.rotation)  # Memory access ctrl
    self.write_cmd(self.VSCRSADD, 0x00)  # Vertical scrolling start address
    self.write_cmd(self.PIXFMT, 0x55)  # COLMOD: Pixel format
    self.write_cmd(self.FRMCTR1, 0x00, 0x18)  # Frame rate ctrl
    self.write_cmd(self.DFUNCTR, 0x08, 0x82, 0x27)
    self.write_cmd(self.ENABLE3G, 0x00)  # Enable 3 gamma ctrl
    self.write_cmd(self.GAMMASET, 0x01)  # Gamma curve selected
    if gamma:  # Use custom gamma correction values
        self.write_cmd(self.GMCTRP1, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08,
                        0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09,
                        0x00)
        self.write_cmd(self.GMCTRN1, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07,
                        0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36,
                        0x0F)
    self.write_cmd(self.SLPOUT)  # Exit sleep
    sleep(.1)
    self.write_cmd(self.DISPLAY_ON)  # Display on
    sleep(.1)
    self.clear()
    *************************************************/

    return current_display;
}

void display_deinit(display_struct* current_display){
    spi_deinit(current_display->spi);
    free(current_display);
}

void display_reset(display_struct* current_display){
    gpio_put(current_display->rst,0);
    sleep_ms(50);
    gpio_put(current_display->rst,1);
}

// Functions
void display_clear_screen(display_struct* current_display, uint16_t color, uint16_t lines){
    // lines = number of lines to fill at once. Best case scenario (and max is the height)
    if(lines > current_display->height || current_display->height % lines != 0){
        // Error
        return;
    }

    // Create a buffer - size is divided by 2 since we are writing 16 bits at a time.
    int buffer_size = (current_display->width * lines);
    uint16_t* buffer = (uint16_t*)malloc(buffer_size*sizeof(uint16_t));
    memset(buffer, color, buffer_size);

    for(int index=0; index<lines; ++index){

    }
    free(buffer);
}

void display_write_cmd(display_struct* current_display, uint8_t command, uint8_t* args, uint8_t arg_count){
    gpio_put(current_display->dc, 0);
    gpio_put(current_display->cs, 0);
    spi_write_blocking(current_display->spi,&command,1);
    gpio_put(current_display->cs, 1);

    for(int index=0; index<arg_count; ++index){
        display_write_data(current_display,&args[index], sizeof(args[index]));
    }
}

void display_write_data(display_struct* current_display, uint8_t* data, int data_len){
    gpio_put(current_display->dc, 1);
    gpio_put(current_display->cs, 0);
    spi_write_blocking(current_display->spi,data,data_len);
    gpio_put(current_display->cs, 1);
}

// Note this is data in 16 bits - e.g., data_len of 2 bytes is 1
void display_write16_data(display_struct* current_display, uint16_t* data, int data_len){
    gpio_put(current_display->dc, 1);
    gpio_put(current_display->cs, 0);
    spi_write16_blocking(current_display->spi,data,data_len);
    gpio_put(current_display->cs, 1);
}