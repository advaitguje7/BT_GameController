/* TODO
-> Action Buttons (ABXY) [x]
-> Triggers [x]
-> Back Buttons [x]
-> Dpad [x]
-> LED [x]
-> Joysticks [x]
-> Power Supply
-> Keyboard VS Gamepad modes
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

/*Action Buttons [4]*/
#define PIN_A 14
#define PIN_B 27
#define PIN_X 26
#define PIN_Y 25

/*Triggers [2]*/
#define PIN_LT 23 K
#define PIN_RT 13

/*Back Buttons [2]*/
#define PIN_LB 15
#define PIN_RB 12

/*D-Pad [4]*/
#define PIN_HAT_UP 4
#define PIN_HAT_DOWN 19
#define PIN_HAT_LEFT 5
#define PIN_HAT_RIGHT 18

/*Joysticks [2]*/
#define PIN_LS_X 35
#define PIN_LS_Y 34
#define PIN_LS_JSB 21

#define PIN_RS_X 33
#define PIN_RS_Y 32
#define PIN_RS_JSB 22

/*Control [2]*/
#define PIN_START 0
#define PIN_MENU 0

/*Outputs [1]*/
// #define ledPin 34

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

/*Joystick Commands*/
#define COMMAND_LS_X_RIGHT 0
#define COMMAND_LS_X_LEFT 0
#define COMMAND_LS_Y_UP 0
#define COMMAND_LS_Y_DOWN 0
#define COMMAND_LS_JSB 0

#define COMMAND_RS_X_RIGHT 0
#define COMMAND_RS_X_LEFT 0
#define COMMAND_RS_Y_UP 0
#define COMMAND_RS_Y_DOWN 0
#define COMMAND_RS_JSB 0

// Hard Coded Macros
#define M_NUM_BUTTONS 16

typedef struct Application {

    // bools
    bool firstCall;
    // Button
    _Button aButton;
    _Button bButton;
    _Button xButton;
    _Button yButton;

    _Button leftTrigger;
    _Button rightTrigger;

    _Button leftButton;
    _Button rightButton;

    _Button hatUpButton;
    _Button hatDownButton;
    _Button hatLeftButton;
    _Button hatRightButton;

    _Joystick leftJoystick;
    _Joystick rightJoystick;

} Application;

// enum gameMode {
//     KEYBOARD,
//     GAMEPAD 
// };

Application Application_construct();

// Initializes variables for the buttons
void setupButtons(Application* app);

// Initializes variables for the buttons
void setupJoysticks(Application* app);

// refreshes a button every cycle
void Button_refresh(_Button* button);

// refreshes the entire HAL
void HAL_refresh(Application* app);

// taps the button
void tap_button(_Button* pin);

// presses the button
void press_button(_Button* pin);

// taps the joystick
void tap_joystick(_Joystick* joystick);

// reads the action buttons and executes corresponding commands
void readWriteABXY(Application* app);

// reads the triggers buttons and executes corresponding commands
void readWriteTriggers(Application* app);

// reads the back buttons and executes corresponding commands
void readWriteBackButtons(Application* app);

// reads the D-Pad buttons and executes corresponding commands
void readWriteHats(Application* app);

// samples the joysticks
void readJoysticks(Application* app);

// executes corresponding commands
void writeJoysticks(Application* app);
