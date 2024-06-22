#include "py/runtime.h"

#include "picogame_sdk/screen/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _PicoScreen_obj_t {
	mp_obj_base_t base;
	Screen screen;
} PicoScreen_obj_t;

const mp_obj_type_t picoclass_type;

static mp_obj_t clear_screen(mp_obj_t self_in, mp_obj_t color_in){
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(self_in);
	int color = mp_obj_get_int(color_in);

	ClearScreen(&(self->screen),color);

	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_2(pico_clearscreen_obj, clear_screen);

static mp_obj_t get_width(mp_obj_t self_in){
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(self_in);

	return 	mp_obj_new_int(GetWidth(&(self->screen)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(pico_getwidth_obj, get_width);

static mp_obj_t get_height(mp_obj_t self_in){
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(self_in);

	return 	mp_obj_new_int(GetHeight(&(self->screen)));
}
static MP_DEFINE_CONST_FUN_OBJ_1(pico_getheight_obj, get_height);

static mp_obj_t render(mp_obj_t self_in){
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(self_in);

	Render(&(self->screen));

	return 	mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(pico_render_obj, render);

static mp_obj_t PicoScreen_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	PicoScreen_obj_t *self = mp_obj_malloc(PicoScreen_obj_t,type);
	CreateScreen(&(self->screen));

	return MP_OBJ_FROM_PTR(self);
}

static const mp_rom_map_elem_t PicoScreen_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_clear_screen), MP_OBJ_FROM_PTR(&pico_clearscreen_obj) },
	{ MP_ROM_QSTR(MP_QSTR_get_width), MP_OBJ_FROM_PTR(&pico_getwidth_obj) },
	{ MP_ROM_QSTR(MP_QSTR_get_height), MP_OBJ_FROM_PTR(&pico_getheight_obj) },
	{ MP_ROM_QSTR(MP_QSTR_render), MP_OBJ_FROM_PTR(&pico_render_obj) },
};
static MP_DEFINE_CONST_DICT(PicoScreen_locals_dict, PicoScreen_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
	type_PicoScreen,
	MP_QSTR_PicoScreen,
	MP_TYPE_FLAG_NONE,
	make_new, PicoScreen_make_new,
	locals_dict, &PicoScreen_locals_dict);

static const mp_rom_map_elem_t PicoGame_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_PicoGame) },
	{ MP_ROM_QSTR(MP_QSTR_PicoScreen), MP_ROM_PTR(&type_PicoScreen) },
};
static MP_DEFINE_CONST_DICT(PicoGame_globals, PicoGame_globals_table);


// Define module object.
const mp_obj_module_t PicoGame = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t *)&PicoGame_globals,
};

// Register the module to make it available in Python.
MP_REGISTER_MODULE(MP_QSTR_PicoGame, PicoGame);

#ifdef __cplusplus
}
#endif
