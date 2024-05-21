#include "py/runtime.h"

#include "picogame.h"

#include "screen/screen.h"
#include "screen/image.h"
#include "input/input.h"

extern "C" {

    // This represents Screen.__new__ and Screen.__init__, which is called when
    // the user instantiates a Screen object.
    static mp_obj_t Screen_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
        // Allocates the new object and sets the type.
        Screen_obj_t *self = mp_obj_malloc(Screen_obj_t, type);

        // Initializes the Screen instance.
        self->screenInstance = new Screen();

        // The make_new function always returns self.
        return MP_OBJ_FROM_PTR(self);
    }

    static mp_obj_t Screen_getWidth(mp_obj_t self_in) {
        Screen_obj_t *self = MP_OBJ_TO_PTR(self_in);

        mp_uint_t n_width = self->screenInstance->GetWidth();
        return mp_obj_new_int_from_uint(n_width);
    }
    static MP_DEFINE_CONST_FUN_OBJ_1(Screen_getWidth_obj, Screen_getWidth);

    static mp_obj_t Screen_getHeight(mp_obj_t self_in) {
        Screen_obj_t *self = MP_OBJ_TO_PTR(self_in);

        mp_uint_t n_height = self->screenInstance->GetHeight();
        return mp_obj_new_int_from_uint(n_height);
    }
    static MP_DEFINE_CONST_FUN_OBJ_1(Screen_getHeight_obj, Screen_getHeight);

    static mp_obj_t Screen_getPosition(mp_obj_t self_in, mp_obj_t x_obj, mp_obj_t y_obj) {
        Screen_obj_t *self = MP_OBJ_TO_PTR(self_in);
        int x = mp_obj_get_int(x_obj);
        int y = mp_obj_get_int(y_obj);

        mp_uint_t n_position = self->screenInstance->GetPosition(x,y);
    }
    static MP_DEFINE_CONST_FUN_OBJ_3(Screen_getPosition_obj, Screen_getPosition);

    static mp_obj_t Screen_clearScreen(mp_obj_t self_in, mp_obj_t color_in) {
        Screen_obj_t *self = MP_OBJ_TO_PTR(self_in);
        mp_uint_t color = mp_obj_get_uint(color_in);

        self->screenInstance->ClearScreen(color);

        // TO DO: What should void return?
    }
    static MP_DEFINE_CONST_FUN_OBJ_2(Screen_clearScreen_obj, Screen_clearScreen);

    void ClearScreen(Screen* obj, uint16_t color){
        obj->ClearScreen(color);
    }

    static const mp_rom_map_elem_t Screen_locals_dict_table[] = {
        { MP_ROM_QSTR(MP_QSTR_GetWidth), MP_ROM_PTR(&Screen_getWidth_obj) },
        { MP_ROM_QSTR(MP_QSTR_GetHeight), MP_ROM_PTR(&Screen_getHeight_obj) },
    };
    static MP_DEFINE_CONST_DICT(Screen_locals_dict, Screen_locals_dict_table);

    MP_DEFINE_CONST_OBJ_TYPE(
        type_Simer,
        MP_QSTR_Timer,
        MP_TYPE_FLAG_NONE,
        make_new, Screen_make_new,
        locals_dict, &Screen_locals_dict
        );

    static const mp_rom_map_elem_t picogame_module_globals_table[] = {
        { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_picogame) },
        { MP_ROM_QSTR(MP_QSTR_Screen),    MP_ROM_PTR(&type_Screen) },
    };
    static MP_DEFINE_CONST_DICT(picogame_module_globals, picogame_module_globals_table);

/*
    
    void DrawLine(Screen* obj, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color=0xffff);
    void DrawCircle(Screen* obj, int xc, int yc, int radius, uint16_t color=0xffff, bool fill=true);
    void DrawRectangle(Screen* obj, uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y, uint16_t color=0xffff, bool fill=true);
    void DrawImage(Screen* obj, uint16_t xs, uint16_t ys, Image* p_image);
    void Render(Screen* obj);
*/
}