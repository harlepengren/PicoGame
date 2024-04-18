#include <stdio.h>
#include <stdlib.h>

#include <hardware/spi.h>
#include <pico/stdio.h>
#include <pico/stdlib.h>

#include "setup.h"
#include "sd_card.h"

void init_pins(){
    if(!sd_init_driver()){
        printf("Error init SD card driver.\n");

        // Infinite loop
        while(true);
    }
}

