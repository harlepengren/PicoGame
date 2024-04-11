#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

typedef struct _display_struct {
    spi_inst_t* spi;
    int8_t sck;
    int8_t cs;
    int8_t dc;
    int8_t mosi;
    int8_t rst;
    int16_t width;
    int16_t height;
} display_struct;

// Commands
#define SWRESET 0x01
#define READ_ID 0x04
#define READ_STATUS 0x09
#define READ_PWR_MODE 0x0A
#define READ_MADCTL 0x0B
#define READ_PIXEL_FMT 0x0C
#define READ_IMG_FMT 0x0D
#define READ_SIGNAL_MODE 0x0E
#define READ_DIAG 0x0F
#define SLEEP 0x10
#define SLEEP_OUT 0x11
#define PARTIAL_MODE_ON 0x12
#define NORMAL_DISPLAY_MODE_ON 0x13
#define DISPLAY_INVERSION_OFF 0x20
#define DISPLAY_INVERSION_ON 0x21
#define DISPLAY_OFF 0x28        // Display off
#define DISPLAY_ON 0x29         // Display on
#define SET_COLUMN 0x2A
#define SET_PAGE 0x2B
#define WRITE_RAM 0x2C
#define PIXFMT 0x3A     // COLMOD: Pixel format set
#define MADCTL 0x36     // Memory access control
#define FRMCTR1 0xB1    // Frame rate control (In normal mode/full colors)
#define FRMCTR2 0xB2    // Frame rate control (In idle mode/8 colors)
#define FRMCTR3 0xB3    // Frame rate control (In partial mode/full colors)
#define DFUNCTR 0xB6    // Display function control
#define PWCTR1 0xC0
#define PWCTR2 0xC1
#define PWCTRA 0xCB
#define PWCTRB 0xCF
#define VMCTR1 0xC5     // VCOM control 1
#define VMCTR2 0xC7     // VCOM control 2
#define DTCA 0xE8       // Driver timing control A
#define DTCB 0xEA       // Driver timing control B
#define DTCA 0xE8       // Driver timing control A
#define DTCB 0xEA       // Driver timing control B
#define POSC 0xED       // Power on sequence
#define PUMPRC 0xF7     // Pump ratio control


int16_t Color565(int8_t r, int8_t g, int8_t b);

// Initialize and De-initialize
display_struct* display_init(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t sck, int8_t mosi, int8_t rst, int16_t width, int16_t height);
void display_deinit(display_struct* current_display);
void display_reset(display_struct* current_display);

// Functions
void display_clear_screen(display_struct* current_display, uint16_t color, uint16_t lines);
void display_write_cmd(display_struct* current_display, uint8_t command);
void display_write_cmd_args(display_struct* current_display, uint8_t command, uint8_t arg_count, uint8_t* args);
void display_write_data(display_struct* current_display, uint8_t* data, int data_len);
void display_write16_data(display_struct* current_display, uint16_t* data, int data_len);


#endif