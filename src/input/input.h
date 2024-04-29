#ifndef INPUT_H
#define INPUT_H

#include <vector>

#define A_BUTTON 5
#define B_BUTTON 6
#define SELECT_BUTTON 7

enum button{a_button, b_button, select_button};
enum event_type{button_down, button_up};

struct InputEvent{
    button inputButton;         // Button that this event applies to
    event_type event;           // Event to look for (button up/button down)
    void* callbackFunction;     // Function to call when event occurs
};

class Input{
    private:
        std::vector<InputEvent*> eventList;

    public:
        Input();
        void AddCallback(button inputButton, event_type event, void* callbackFunction);
        void RemoveCallBack(button inputButton, event_type event);
};

#endif