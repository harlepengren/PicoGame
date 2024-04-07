#include <stdio.h>

#include "py/runtime.h"
#include "py/obj.h"

typedef struct _displayclass_obj_t {
    mp_obj_base_t base;
    spi_inst_t* spi;
    int8_t spi_pin;
    int8_t cs;
    int8_t dc;
    int8_t rst;
    int16_t height;
    int16_t width;
} displayclass_obj_t;

const mp_obj_type_t displayclass_type;

STATIC void displayclass_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    (void)kind;
    displayclass_obj_t *self = MP_OBJ_TO_PTR(self_in);
    mp_print_str(print, "Display Object");
    mp_obj_print_helper(print, mp_obj_new_int(self->height), PRINT_REPR);
    mp_print_str(print, " x ");
    mp_obj_print_helper(print, mp_obj_new_int(self->width), PRINT_REPR);
    mp_print_str(print, ")");
}

STATIC mp_obj_t displayclass_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    mp_arg_check_num(n_args, n_kw, 2, 2, true);
    displayclass_obj_t *self = m_new_obj(displayclass_obj_t);
    self->base.type = &displayclass_type;
    self->spi_pin = mp_obj_get_int(args[0]);
    self->cs = mp_obj_get_int(args[1]);
    self->dc = mp_obj_get_int(args[2]);
    self->rst = mp_obj_get_int(args[3]);
    self->width = mp_obj_get_int(args[4]);
    self->height = mp_obj_get_int(args[5]);

    return MP_OBJ_FROM_PTR(self);
}

// Instance Methods
STATIC mp_obj_t displayclass_clear(mp_obj_t self_in, mp_obj_t color_obj) {
    displayclass_obj_t *class_instance = MP_OBJ_TO_PTR(self_in);
    mp_int_t n_color = mp_obj_get_int(color_obj);

    return self_in;
}

MP_DEFINE_CONST_FUN_OBJ_2(displayclass_clear_obj, displayclass_clear);