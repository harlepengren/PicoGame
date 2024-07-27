#include <string.h>

#include "py/runtime.h"
#include "py/objstr.h"

#include "picogame_sdk/screen/screen.h"
#include "picogame_sdk/input/input.h"
#include "picogame_sdk/image/image.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************
 * Screen: Functions to Control the Screen
 *****************************************************************/
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

static mp_obj_t draw_line(size_t n_args, const mp_obj_t *args) {
	// Arguments
	// mp_obj_t self_in, mp_obj_t startx_in, mp_obj_t starty_in,
	// mp_obj_t endx_in, mp_obj_t endy_in, mp_obj_t color_in
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(args[0]);
	int start_x = mp_obj_get_int(args[1]);
	int start_y = mp_obj_get_int(args[2]);
	int end_x = mp_obj_get_int(args[3]);
	int end_y = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);

	DrawLine(&(self->screen),start_x,start_y,end_x,end_y,color);

	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR(pico_drawline_obj, 6, draw_line);

static mp_obj_t draw_circle(size_t n_args, const mp_obj_t *args) {
	// Arguments
	// mp_obj_t self_in, mp_obj_t xc_in, mp_obj_t yc_in,
	// mp_obj_t radius_in, mp_obj_t color_in, mp_obj_t fill_in
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(args[0]);
	int xc = mp_obj_get_int(args[1]);
	int yc = mp_obj_get_int(args[2]);
	int radius = mp_obj_get_int(args[3]);
	int color = mp_obj_get_int(args[4]);
	int fill = mp_obj_get_int(args[5]);

	DrawCircle(&(self->screen),xc,yc,radius,color,fill);

	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR(pico_drawcircle_obj, 6, draw_circle);

static mp_obj_t draw_rectangle(size_t n_args, const mp_obj_t *args) {
	// Arguments
	// mp_obj_t self_in, mp_obj_t start_x_in, mp_obj_t start_y_in,
	// mp_obj_t end_x_in, mp_obj_t end_y_in, mp_obj_t color_in,
	// mp_obj_t fill_in)
	PicoScreen_obj_t* self = MP_OBJ_TO_PTR(args[0]);
	int start_x = mp_obj_get_int(args[1]);
	int start_y = mp_obj_get_int(args[2]);
	int end_x = mp_obj_get_int(args[3]);
	int end_y = mp_obj_get_int(args[4]);
	int color = mp_obj_get_int(args[5]);
	int fill = mp_obj_get_int(args[6]);

	DrawRectangle(&(self->screen),start_x,start_y,end_x,end_y,color,fill);

	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_VAR(pico_drawrectangle_obj, 7, draw_rectangle);

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
	{ MP_ROM_QSTR(MP_QSTR_draw_line), MP_OBJ_FROM_PTR(&pico_drawline_obj) },
	{ MP_ROM_QSTR(MP_QSTR_draw_circle), MP_OBJ_FROM_PTR(&pico_drawcircle_obj) },
	{ MP_ROM_QSTR(MP_QSTR_draw_rectangle), MP_OBJ_FROM_PTR(&pico_drawrectangle_obj) },
	{ MP_ROM_QSTR(MP_QSTR_render), MP_OBJ_FROM_PTR(&pico_render_obj) },
};
static MP_DEFINE_CONST_DICT(PicoScreen_locals_dict, PicoScreen_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
	type_PicoScreen,
	MP_QSTR_PicoScreen,
	MP_TYPE_FLAG_NONE,
	make_new, PicoScreen_make_new,
	locals_dict, &PicoScreen_locals_dict);

/*****************************************************************
 * Input: Functions to Control the Input
 *****************************************************************/
typedef struct _PicoInput_obj_t {
	mp_obj_base_t base;
	Input input;
} PicoInput_obj_t;

static mp_obj_t process_inputs(mp_obj_t self_in){
	PicoInput_obj_t* self = MP_OBJ_TO_PTR(self_in);

	uint8_t result = ProcessInputs(&(self->input));

	return 	mp_obj_new_int(result);
}

static MP_DEFINE_CONST_FUN_OBJ_1(pico_processinputs_obj,process_inputs);

static mp_obj_t get_key(mp_obj_t self_in, mp_obj_t key_name_in){
	PicoInput_obj_t* self = MP_OBJ_TO_PTR(self_in);
	GET_STR_DATA_LEN(key_name_in, str, str_len);
	char key_str[str_len];
	strcpy(key_str, (char *)str);

 /*BUTTON_UP       0x0001
#define BUTTON_DOWN     0x0002
#define BUTTON_LEFT     0x0004
#define BUTTON_RIGHT    0x0008
#define BUTTON_A        0x0010
#define BUTTON_B        0x0020
#define BUTTON_SELECT */

	uint8_t key = 0;
	if(strcmp(key_str,"A")==0){
		key = BUTTON_A;
	} else if(strcmp(key_str,"B")==0){
		key = BUTTON_B;
	} else if(strcmp(key_str,"UP")==0){
		key = BUTTON_UP;
	} else if(strcmp(key_str,"DOWN")==0){
		key = BUTTON_DOWN;
	} else if(strcmp(key_str,"LEFT")==0){
		key = BUTTON_LEFT;
	} else if(strcmp(key_str,"RIGHT")==0){
		key = BUTTON_RIGHT;
	} else if(strcmp(key_str,"SELECT")==0){
		key = BUTTON_SELECT;
	}

	return mp_obj_new_bool(GetKey(&(self->input),key));
}
static MP_DEFINE_CONST_FUN_OBJ_2(pico_getkey_obj,get_key);

static mp_obj_t PicoInput_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	PicoInput_obj_t *self = mp_obj_malloc(PicoInput_obj_t,type);
	InitInput(&(self->input));

	return MP_OBJ_FROM_PTR(self);
}

static const mp_rom_map_elem_t PicoInput_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_process_inputs), MP_OBJ_FROM_PTR(&pico_processinputs_obj) },
	{ MP_ROM_QSTR(MP_QSTR_get_key), MP_OBJ_FROM_PTR(&pico_getkey_obj) },
};
static MP_DEFINE_CONST_DICT(PicoInput_locals_dict, PicoInput_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
	type_PicoInput,
	MP_QSTR_PicoInput,
	MP_TYPE_FLAG_NONE,
	make_new, PicoInput_make_new,
	locals_dict, &PicoInput_locals_dict);

/*****************************************************************
 * Image: Functions to Load and Display an Image
 *****************************************************************/
typedef struct _PicoImage_obj_t {
	mp_obj_base_t base;
	Image* image;
} PicoImage_obj_t;

static mp_obj_t load_image(mp_obj_t self_in, mp_obj_t path_obj){
	PicoImage_obj_t* self = MP_OBJ_TO_PTR(self_in);
	const char *path = qstr_str(mp_obj_str_get_qstr(path_obj));

	Image* new_image = LoadImage(path);
	self->image = new_image;

	return 	mp_obj_new_bool(self->image != NULL);
}

static MP_DEFINE_CONST_FUN_OBJ_2(pico_loadimage_obj,load_image);

static mp_obj_t PicoImage_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
	PicoImage_obj_t *self = mp_obj_malloc(PicoImage_obj_t,type);

	return MP_OBJ_FROM_PTR(self);
}

static const mp_rom_map_elem_t PicoImage_locals_dict_table[] = {
	{ MP_ROM_QSTR(MP_QSTR_load_image), MP_OBJ_FROM_PTR(&pico_loadimage_obj) },
};
static MP_DEFINE_CONST_DICT(PicoImage_locals_dict, PicoImage_locals_dict_table);

MP_DEFINE_CONST_OBJ_TYPE(
	type_PicoImage,
	MP_QSTR_PicoImage,
	MP_TYPE_FLAG_NONE,
	make_new, PicoImage_make_new,
	locals_dict, &PicoImage_locals_dict);


/*****************************************************************
 * Module: Overall Module Functions
 *****************************************************************/

static const mp_rom_map_elem_t PicoGame_globals_table[] = {
	{ MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_PicoGame) },
	{ MP_ROM_QSTR(MP_QSTR_PicoScreen), MP_ROM_PTR(&type_PicoScreen) },
	{ MP_ROM_QSTR(MP_QSTR_PicoInput), MP_ROM_PTR(&type_PicoInput) },
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
