#ifndef BUTTONS_H
#define BUTTONS_H

#define INACTIVE 1
#define ACTIVE 0

enum buttonType {
    TAPPED,
    TOGGLED,
    PRESSED,
    TAP_AND_PRESS,
};

enum DebounceState {
  StableR,
  StableP,
  TransitionRP,
  TransitionPR
};

struct Button {

  // buttons
  int pin;

  int pushState;
  bool isTapped;

  DebounceState debounceState;

  unsigned long timerStart;
  unsigned long debounceDelay;

  // controls
  String name;
  buttonType type;
  int command;
  bool firstCall;
  bool wasPressed;
};

// constructs the button
void Button_construct(Button* button, String name, int pin, int command, buttonType type);

// determines if the button is tapped
bool Button_isTapped(Button* button);

// determines if the button is pressed 
bool Button_isPressed(Button* button);

#endif





