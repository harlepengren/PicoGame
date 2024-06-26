#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define BIT_DEPTH 2     // 565 color with 2 bytes per pixel

typedef struct _display_struct {
    spi_inst_t* spi;
    int8_t sck;
    int8_t cs;
    int8_t dc;
    int8_t mosi;
    int8_t rst;
    int16_t width;
    int16_t height;
    uint8_t* frame_buffer;
    int buffer_size;
} display_struct;

// Commands
#define NOP 0x00
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
#define GMCTRP1 0xE0
#define GMCTRN1 0xE1
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
#define ENABLE3G 0xF2   // Enable/disable gamma
#define VSCRSADD 0x37   // Vertical scrolling start address
#define GAMMASET 0x26   // Gamma set

int16_t Color565(int8_t r, int8_t g, int8_t b);

// Display Class
class Display {
    private: 
        display_struct current_display;

    public:
        Display(spi_inst_t* spi, int8_t cs, int8_t dc, int8_t sck, int8_t mosi, int8_t rst, int16_t width, int16_t height);
        ~Display();

        void Reset();
        void WriteBlock(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1, uint8_t* data, int data_len);
        void ClearScreen(uint16_t color);
        void WriteCmd(uint8_t command);
        void WriteCmd(uint8_t command, uint8_t arg_count, ...);
        void WriteData(uint8_t* data, int data_len);
        void WriteData16(uint16_t* data, int data_len);
};
#endif