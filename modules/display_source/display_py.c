#include "display_ili9341.h"

static mp_int_t factorial_helper(mp_int_t x) {
	if(x==0){
		return 1;
	}
	return x* factorial_helper(x-1);
}

// Init
// Close
// Fill circle

static mp_obj_t display(mp_obj_t x_obj) {
	mp_int_t x = mp_obj_get_int(x_obj);
	mp_int_t result = factorial_helper(x);
	return mp_obj_new_int(result);
}

static MP_DEFINE_CONST_FUN_OBJ_1(display_obj, display);

mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
	MP_DYNRUNTIME_INIT_ENTRY
	mp_store_global(MP_QSTR_display, MP_OBJ_FROM_PTR(&display_obj));
	MP_DYNRUNTIME_INIT_EXIT
}
