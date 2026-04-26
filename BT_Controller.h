// Buttons
#define aPin 27
#define bPin 13
#define yPin 12
#define xPin 14

// Button Commands
#define aCommand 32 // 0x20 | jump
#define bCommand 122 // drop item
#define xCommand 99; // inventory
#define yCommand 0 // undetermined

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


struct Application {

    // Controls
    int abxyButtons[4];
    int abxyCommands[4];
    int triggerButtons[2];
    int backButtons[2];
    int dpadButtons[4];
    int joystickButtons[2];

    // Bools
    bool FirstCall_A;
    bool FirstCall_B;
    bool FirstCall_X;
    bool FirstCall_Y;

    bool FirstCall_LT;
    bool FirstCall_RT;

    bool FirstCall_LB;
    bool FirstCall_RB;

    bool FirstCall_DPadUp;
    bool FirstCall_DPadDown;
    bool FirstCall_DPadLeft;
    bool FirstCall_DPadRight;
};

Application Application_construct();
Application Application_loop();

// reads the action buttons and executes the according command
void readWriteABXY(Application* app);

// reads the back buttons and returns which one was pressed
int readBackButtons(Application* app);

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