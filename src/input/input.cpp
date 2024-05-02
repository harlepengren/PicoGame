#include <vector>
#include <stdio.h>

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "input.h"


Input::Input(){
    button_state = 0x0;
    button_change = 0x0;

    gpio_set_function(GPIO_A_BUTTON, GPIO_FUNC_SIO);
    //gpio_set_function(GPIO_B_BUTTON, GPIO_FUNC_SIO);
    //gpio_set_function(GPIO_SELECT_BUTTON,GPIO_FUNC_SIO);

    gpio_set_dir(GPIO_A_BUTTON, false);
    //gpio_set_dir(GPIO_B_BUTTON,false);
    //gpio_set_dir(GPIO_SELECT_BUTTON,false);

    gpio_pull_up(GPIO_A_BUTTON);
    //gpio_pull_up(GPIO_B_BUTTON);
    //gpio_pull_up(GPIO_SELECT_BUTTON);

}

Input::~Input(){
    gpio_deinit(GPIO_A_BUTTON);
    //gpio_deinit(GPIO_B_BUTTON);
    //gpio_deinit(GPIO_SELECT_BUTTON);
}

void Input::ProcessInputs()
{
    if(!gpio_get(GPIO_A_BUTTON)){
        printf("button down\n");
    }
    /*uint8_t current_buttons = 0;
    if(!gpio_get(GPIO_A_BUTTON)){
        current_buttons = BUTTON_A;
    } else{
        printf("Not down");
    }

    button_change = current_buttons ^ button_state;
    button_state = current_buttons;   */ 
}

bool Input::GetButtonDown(uint8_t testButton) {
    if(!gpio_get(GPIO_A_BUTTON)){
        printf("Button is currently pushed\n");
    }

    return (testButton & button_state & button_change) == testButton;
}


bool Input::GetButtonUp(uint8_t testButton){
    return (testButton & button_state & !button_change) == 0;
}

bool Input::GetKey(uint8_t testButton){
    return button_state & testButton == testButton;
}