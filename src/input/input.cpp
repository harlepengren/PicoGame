#include <vector>
#include <hardware/gpio.h>

#include "input.h"

Input::Input(){

}

Input::~Input(){
    InputEvent* p_event;

    while(eventList.size() > 0){
        p_event = eventList.back();
        delete p_event;
        eventList.pop_back();
    }
}

void Input::AddCallback(button inputButton, event_type event, void* callbackFunction){
    InputEvent* p_inputEvent = new InputEvent;
    p_inputEvent->inputButton = inputButton;
    p_inputEvent->event = event;
    p_inputEvent->callbackFunction = callbackFunction;

    eventList.push_back(p_inputEvent);
}

void Input::RemoveCallBack(button inputButton, event_type event){
    InputEvent* p_event;

    // Find the event
    std::vector<InputEvent*>::iterator it;
    for(it=eventList.begin(); it != eventList.end(); ++it){
        p_event = *it;
        if(p_event->inputButton == inputButton && p_event->event == event){
            eventList.erase(it);
            break;
        }
    }
}