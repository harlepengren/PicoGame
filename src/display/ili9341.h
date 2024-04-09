#ifndef ILI9341_H
#define ILI9341_H

#include <stdlib.h>
#include "pico/stdlib.h"

typedef struct _display_struct {
    spi_inst_t* spi;
    int8_t cs;
    int8_t dc;

} display_struct;

#endif