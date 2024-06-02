#include <stdarg.h>

#include "picoscreen.h"
#include "screen.h"

void* CreatePicoScreen(){
    Screen* current_screen = new Screen();

    return current_screen;
}

uint16_t GetWidth(void* screen){
    return screen->GetWidth();
}

uint16_t GetHeight(void* screen){
    return screen->GetHeight();
}

void ClearScreen(void* screen, int n_args, ...){
    va_list valist;
    uint16_t color = 0;

    // Check whether a color was provided
    if(n_args > 0){
        va_start(valist,n_args);
        color = va_arg(valist,uint16_t);
        va_end(valist);
    }

    screen->ClearScreen(color);

}