#ifndef INPUT_H
#define INPUT_H

enum button{a_button, b_button, home_button};

class Input{
    private:
        // Callback functions
        void* a_button_func;
        void* b_button_func;
        void* home_button_func;

        uint8_t button_status;
        uint8_t button_change;

    public:
        void SetCallBack(button target_button, void* callbackFunction);

};

#endif