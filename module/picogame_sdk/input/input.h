#ifndef INPUT_H
#define INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#define GPIO_A_BUTTON 5
#define GPIO_B_BUTTON 6
#define GPIO_SELECT_BUTTON 7

#define BUTTON_UP       0x0001
#define BUTTON_DOWN     0x0002
#define BUTTON_LEFT     0x0004
#define BUTTON_RIGHT    0x0008
#define BUTTON_A        0x0010
#define BUTTON_B        0x0020
#define BUTTON_SELECT   0x0040

typedef struct _Input{
    uint8_t button_state;
    uint8_t button_change;
} Input;

void InitInput(Input* self);
//void InitButton(Input* self, uint8_t button);

void ProcessInputs(Input* self);
bool GetButtonDown(Input* self, uint8_t testButton);  // Button was pressed during the frame
bool GetButtonUp(Input* self, uint8_t testButton);    // Button was released during the frame
bool GetKey(Input* self, uint8_t testButton);         // Button is currently down

#ifdef __cplusplus
}
#endif
#endif