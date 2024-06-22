#include <stdarg.h>
#include <stdlib.h>

#include "picoscreen.h"
#include "picogame_sdk/screen/screen.h"


void* CreatePicoScreen(){
    Screen* current_screen = new Screen();
    return current_screen;
}

uint16_t GetWidth(void* screen){
    return ((Screen*)screen)->GetWidth();
}

uint16_t GetHeight(void* screen){
    return ((Screen*)screen)->GetHeight();
}

void ClearScreen(void* screen, int n_args, ...){
    va_list valist;
    uint16_t color = 0;

    // Check whether a color was provided
    if(n_args > 0){
        va_start(valist,n_args);
        color = (uint16_t)va_arg(valist,int);
        va_end(valist);
    }

    ((Screen*)screen)->ClearScreen(color);

}