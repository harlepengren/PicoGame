#include "input.h"

Input::Input(){
    button_status = 0x0;
    button_change = 0x0;
}

void Input::SetCallBack(button target_button, void* callbackFunction){
    if(target_button == a_button){
        a_button_func = callbackFunction;
    } else if(target_button == b_button){
        b_button_func = callbackFunction;
    } else if(target_button == home_button){
        home_button_func = callbackFunction;
    }
}