#include "py/runtime.h"

//#include "screen.h"

#ifdef __cplusplus
extern "C" {
#endif

static const mp_rom_map_elem_t PicoGame_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_PicoGame) },
	//{ MP_ROM_QSTR(MP_QSTR_PicoMath), MP_ROM_PTR(&type_PicoMath) },
	//{ MP_ROM_QSTR(MP_QSTR_test_add), MP_ROM_PTR(&test_add_obj)},
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
