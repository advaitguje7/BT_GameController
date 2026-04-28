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
-> Edge case robustness (if != type, return)
-> Separate toggled and tapped functions (modular)
-> Pin struct
-> Debounce (delay(50) ) 
*/

// Buttons
#define aPin 27
#define bPin 13
#define yPin 12
#define xPin 14

// Button Commands
#define aCommand 32 // 0x20 | jump
#define bCommand 122 // drop item
#define xCommand 99 // inventory
#define yCommand 0 // undetermined

#define leftButtonCommand 0
#define rightButtonCommand 0

// D-pad
#define dpadUpPin 21
#define dpadDownPin 2
#define dpadRightPin 5
#define dpadLeftPin 15

// Triggers
#define leftTriggerPin 19
#define rightTriggerPin 18
#define leftButtonPin 22
#define rightButtonPin 23

// Hard Coded Values
#define NUM_BUTTONS 4
#define DELAY 10 // ms

enum buttonType {
    TAPPED,
    TOGGLED,
};
struct Pin {
    std::string name;
    int num;
    buttonType type;
    bool firstCall;
};

struct Application {

    // Controls
    Pin aButton;
    Pin bButton;
    Pin xButton;
    Pin yButton;

    Pin leftButton;
    Pin rightButton;
    // int abxyCommands[4];
    // int triggerButtons[2];
    // int backButtons[2];
    // int dpadButtons[4];
    // int joystickButtons[2];


};

Application Application_construct();
Application Application_loop();

// Returns if the button was tapped
bool isTapped(Pin* pin);

// reads the action buttons and executes its according command
void readWriteABXY(Application* app);

// reads the back buttons and executes its respective command
void readWriteBackButtons(Application* app);

// reads the D-Pad buttons and returns which one was pressed
int readDPad(Application* app);

// reads the joystick buttons and returns which one was pressed
int readJoystickButtons(Application* app);

// writes based on the action buttons
void writeABXY(Application* app);

// writes based on the triggers
void writeTrigger(Application* app);

// writes based on the back buttons
void writeBackButtons(Application* app);

// writes based on the D-Pad
void writeDPad(Application* app);

// writes based on the joystick buttons
void writeJoystickButtons(Application* app);