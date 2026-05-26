/* TODO
-> Action Buttons (ABXY) [x]
-> Joysticks
-> Triggers [x]
-> Back Buttons [x]
-> Dpad
-> Power Supply
-> LED
*/

/* Questions 
-> For commands, is it better to define or initialize in construct? [#define is better because otherwise you have magic numbers]
-> Is it still spagetti code? [No - separated code for controls into buttons.h, implemented HAL_refresh and button constructs, and button types]
*/

/* Features
-> Edge case robustness (if != type, return) [x]
-> Separate toggled and tapped functions (modular) [x]
-> Button struct [x]
-> Debounce (delay(50)) [x]
*/
#include "Buttons.h"
#include "Joystick.h"

/*Action Buttons*/
#define PIN_A 32
#define PIN_B 33
#define PIN_X 25
#define PIN_Y 26


/*Triggers*/
#define PIN_LT 22
#define PIN_RT 34

/*Back Buttons*/
#define PIN_LB 23
#define PIN_RB 35

/*D-Pad*/
#define PIN_HAT_UP 21
#define PIN_HAT_DOWN 5
#define PIN_HAT_RIGHT 18
#define PIN_HAT_LEFT 19

/*Led*/
#define ledPin 13

/*Action Button Commands*/

#define COMMAND_A 32
#define COMMAND_B 122
#define COMMAND_X 99
#define COMMAND_Y 0

#define IOS_CMD_A 32 // ' ' [space] (jump)
#define IOS_CMD_B 122 // 'z' (drop item)
#define IOS_CMD_X 99 // 'c' (inventory)
#define IOS_CMD_Y 0 // undetermined

#define AND_CMD_A BUTTON_1
#define AND_CMD_B BUTTON_2
#define AND_CMD_X BUTTON_3
#define AND_CMD_Y BUTTON_4

/*Trigger Commands*/
#define COMMAND_LT 101
#define COMMAND_RT 113

#define IOS_CMD_LT 101 // 'e' (place/use)
#define IOS_CMD_RT 113 // 'q' (attack/destroy)

#define AND_CMD_LT BUTTON_5
#define AND_CMD_RT BUTTON_6

/*Back Button Commands*/
#define COMMAND_LB KEY_PAGE_UP
#define COMMAND_RB KEY_PAGE_DOWN

#define IOS_CMD_LB KEY_PAGE_UP // page up (cycle left)
#define IOS_CMD_RB KEY_PAGE_DOWN // page down (cycle right)

#define AND_CMD_LB BUTTON_7
#define AND_CMD_RB BUTTON_8

/*Dpad Commands*/
#define COMMAND_HAT_UP KEY_F5 // toggle perspective
#define COMMAND_HAT_DOWN KEY_LEFT_SHIFT // sneak
#define COMMAND_HAT_LEFT 98 // 'b' (emote)
#define COMMAND_HAT_RIGHT 116 // 't' (chat)

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

    Button hatUpButton;
    Button hatDownButton;
    Button hatLeftButton;
    Button hatRightButton;

} Application;

// enum gameMode {
//     KEYBOARD,
//     GAMEPAD 
// };

Application Application_construct();
Application Application_loop();         

// Initializes variables for the buttons
void setupButtons(Application* app);

// refreshes a button every cycle
void Button_refresh(Button* button);

// refreshes the entire HAL
void HAL_refresh(Application* app);

// taps the button
void tap_button(Button* pin);

// presses the button
void press_button(Button* pin);

// reads the action buttons and executes its according command
void readWriteABXY(Application* app);

// reads the triggers buttons and executes its according command
void readWriteTriggers(Application* app);

// reads the back buttons and executes its respective command
void readWriteBackButtons(Application* app);

// reads the D-Pad buttons and returns which one was pressed
void readWriteHats(Application* app);

// reads the joystick buttons and returns which one was pressed
void readJoystickButtons(Application* app);

// blinks LED
void blinkLED();
