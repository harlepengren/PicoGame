#include <vector>
#include <stdio.h>

#include <hardware/gpio.h>
#include <pico/stdlib.h>

#include "input.h"

Input::Input(){
    button_state = 0x0;
    button_change = 0x0;

    InitButton(GPIO_A_BUTTON);
    InitButton(GPIO_B_BUTTON);
    InitButton(GPIO_SELECT_BUTTON);    
}

Input::~Input(){
    gpio_deinit(GPIO_A_BUTTON);
    gpio_deinit(GPIO_B_BUTTON);
    gpio_deinit(GPIO_SELECT_BUTTON);
}

void Input::InitButton(uint8_t button)
{
    gpio_init(button);
    gpio_set_dir(button, GPIO_IN);
    gpio_pull_up(button);
}

void Input::ProcessInputs()
{
    if(!gpio_get(GPIO_A_BUTTON)){
        printf("A Button Down\n");
    }

    uint8_t current_buttons = gpio_get(GPIO_A_BUTTON) | gpio_get(GPIO_B_BUTTON) | gpio_get(GPIO_SELECT_BUTTON);
    button_change = current_buttons ^ button_state;
    button_state = current_buttons;    
}

bool Input::GetButtonDown(uint8_t testButton) {
    return (testButton & button_state & button_change) == testButton;
}


bool Input::GetButtonUp(uint8_t testButton){
    return (testButton & button_state & !button_change) == 0;
}

bool Input::GetKey(uint8_t testButton){
    return button_state & testButton == testButton;
}