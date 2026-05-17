/* TODO
-> Joysticks
-> Back Buttons
-> Dpad
-> Triggers
*/

/* Questions 
-> For commands, is it better to define or initialize in construct?
-> Is it still spagetti code?
*/

/* Features
-> Edge case robustness (if != type, return) [x]
-> Separate toggled and tapped functions (modular) [x]
-> Button struct [x]
-> Debounce (delay(50) ) [x]
*/
#include "Buttons.h"
/*Action Buttons*/
#define aPin 27
#define bPin 13
#define yPin 12
#define xPin 14

/*Action Button Commands*/
#define aCommand 32 // 0x20 | jump
#define bCommand 122 // drop item
#define xCommand 99 // inventory
#define yCommand 0 // undetermined

/*D-Pad*/
#define dpadUpPin 21
#define dpadDownPin 2
#define dpadRightPin 5
#define dpadLeftPin 15

/*Triggers*/
#define leftTriggerPin 19
#define rightTriggerPin 18

/*Trigger Commands*/
#define leftTriggerCommand 101 // place/use
#define rightTriggerCommand 113 // attack/destroy

/*Back Buttons*/
#define leftButtonPin 22
#define rightButtonPin 23

/*Back Button Commands*/

// Hard Coded Macros
#define NUM_BUTTONS 4
#define M_DELAY 50

typedef struct Application {

    // bools
    bool firstCall;
    // Button
    Button aButton;
    Button bButton;
    Button xButton;
    Button yButton;

    // Button leftTrigger;
    // Button rightTrigger;

    // Button leftButton;
    // Button rightButton;
} Application;

Application Application_construct();
Application Application_loop();

// Initializes variables for the buttons
void setupButtons(Application* app);

// refreshes a button every cycle
void Button_refresh(Button* button);

// refreshes the entire HAL
void HAL_refresh(Application* app);

// reads the action buttons and executes its according command
void readWriteABXY(Application* app);

// reads the triggers buttons and executes its according command
void readWriteTriggers(Application* app);

// reads the back buttons and executes its respective command
void readWriteBackButtons(Application* app);

// reads the D-Pad buttons and returns which one was pressed
void readWriteDPad(Application* app);

// reads the joystick buttons and returns which one was pressed
void readJoystickButtons(Application* app);

// taps the button
void tap_button(Button* pin);

// toggles the button
void toggle_button(Button* pin);

// presses the button
void press_button(Button* pin);
