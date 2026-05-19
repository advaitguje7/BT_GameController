/* TODO
-> Action Buttons (ABXY)
-> Joysticks
-> Triggers
-> Back Buttons
-> Dpad
-> Reset
*/

/* Questions 
-> For commands, is it better to define or initialize in construct? [#define is better because otherwise you have magic numbers]
-> Is it still spagetti code? [No - separated code for controls into buttons.h, implemented HAL_refresh and button constructs, and button types]
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
#define COMMAND_A 32 // ' ' [space] (jump)
#define COMMAND_B 122 // 'z' (drop item)
#define COMMAND_X 99 // 'c' (inventory)
#define COMMAND_Y 0 // undetermined

/*D-Pad*/
#define dpadUpPin 21
#define dpadDownPin 2
#define dpadRightPin 5
#define dpadLeftPin 15

/*Triggers*/
#define leftTriggerPin 19
#define rightTriggerPin 18

/*Trigger Commands*/
#define COMMAND_LT 101 // 'e' (place/use)
#define COMMAND_RT 113 // 'q' (attack/destroy)

/*Back Buttons*/
#define leftButtonPin 22
#define rightButtonPin 23

/*Back Button Commands*/
#define COMMAND_LB KEY_PAGE_UP // page up (cycle left)
#define COMMAND_RB KEY_PAGE_DOWN // page down (cycle right)

// Hard Coded Macros
#define M_NUM_BUTTONS 8
#define M_DELAY 50

typedef struct Application {

    // bools
    bool firstCall;
    // Button
    Button aButton;
    Button bButton;
    Button xButton;
    Button yButton;

    Button leftTrigger;
    Button rightTrigger;

    Button leftButton;
    Button rightButton;

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

// presses the button
void press_button(Button* pin);

// toggles the button
void toggle_button(Button* pin);
