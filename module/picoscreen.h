#ifdef __cplusplus
extern "C" {
#endif

#include "pico/stdlib.h"

void* CreatePicoScreen();
uint16_t GetWidth(void* screen);
uint16_t GetHeight(void* screen);
void ClearScreen(void* screen, int n_args, ...);

#ifdef __cplusplus
}
#endif