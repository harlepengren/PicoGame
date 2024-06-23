#include <stdio.h>

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "input.h"


void InitInput(Input* self){
    self->button_state = 0;
    self->button_change = 0;

    gpio_set_function(GPIO_A_BUTTON, GPIO_FUNC_SIO);
    gpio_set_function(GPIO_B_BUTTON, GPIO_FUNC_SIO);
    gpio_set_function(GPIO_SELECT_BUTTON,GPIO_FUNC_SIO);

    gpio_set_dir(GPIO_A_BUTTON, false);
    gpio_set_dir(GPIO_B_BUTTON,false);
    gpio_set_dir(GPIO_SELECT_BUTTON,false);

    gpio_pull_up(GPIO_A_BUTTON);
    gpio_pull_up(GPIO_B_BUTTON);
    gpio_pull_up(GPIO_SELECT_BUTTON);

}

/*Input::~Input(){
    gpio_deinit(GPIO_A_BUTTON);
    gpio_deinit(GPIO_B_BUTTON);
    gpio_deinit(GPIO_SELECT_BUTTON);
}*/

void ProcessInputs(Input* self)
{
    uint8_t current_buttons;
    current_buttons = (!gpio_get(GPIO_A_BUTTON) << 4) | 
                      (!gpio_get(GPIO_B_BUTTON) << 5) | 
                      (!gpio_get(GPIO_SELECT_BUTTON)) << 6;

    self->button_change = current_buttons ^ self->button_state;
    self->button_state = current_buttons; 
}

bool GetButtonDown(Input* self, uint8_t testButton) {
    return (testButton & self->button_state & self->button_change) == testButton;
}


bool GetButtonUp(Input* self, uint8_t testButton){
    return (testButton & ~self->button_state & self->button_change) == testButton;
}

bool GetKey(Input* self, uint8_t testButton){
    return (self->button_state & testButton) == testButton;
}