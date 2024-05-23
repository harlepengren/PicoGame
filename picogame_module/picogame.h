#include "screen/screen.h"
#include "screen/image.h"
#include "input/input.h"

extern "C"{
    // This structure represents Screen instance objects.
    typedef struct _Screen_obj_t {
        // All objects start with the base.
        mp_obj_base_t base;

        // Attributes
        Screen *screenInstance;
    } Screen_obj_t;

    Screen newScreenObj();
    uint16_t GetWidth(Screen* obj);
    uint16_t GetHeight(Screen* obj);
    int GetPosition(Screen* obj, int x, int y);
    void ClearScreen(Screen* obj, uint16_t color=0);
    void DrawLine(Screen* obj, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color=0xffff);
    void DrawCircle(Screen* obj, int xc, int yc, int radius, uint16_t color=0xffff, bool fill=true);
    void DrawRectangle(Screen* obj, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color=0xffff, bool fill=true);
    void DrawImage(Screen* obj, uint16_t xs, uint16_t ys, Image* p_image);
    void Render(Screen* obj);
}
