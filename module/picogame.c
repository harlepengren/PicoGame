#include "py/runtime.h"

#include "picoscreen.h"

#ifdef __cplusplus
extern "C" {
#endif

static mp_obj_t test_add(mp_obj_t x_obj, mp_obj_t y_obj) {
	int x = mp_obj_get_int(x_obj);
	int y= mp_obj_get_int(y_obj);

	return mp_obj_new_int(x+y);
}
static MP_DEFINE_CONST_FUN_OBJ_2(test_add_obj, test_add);

static mp_obj_t CreateScreen() {
	return MP_OBJ_FROM_PTR(CreatePicoScreen());
}
static MP_DEFINE_CONST_FUN_OBJ_0(create_screen_obj, CreateScreen);

static const mp_rom_map_elem_t PicoGame_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_PicoGame) },
	//{ MP_ROM_QSTR(MP_QSTR_PicoMath), MP_ROM_PTR(&type_PicoMath) },
	{ MP_ROM_QSTR(MP_QSTR_test_add), MP_ROM_PTR(&test_add_obj)},
	{ MP_ROM_QSTR(MP_QSTR_CreateScreen), MP_ROM_PTR(&create_screen_obj)},
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
