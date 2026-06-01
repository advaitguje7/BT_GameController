#ifndef BUTTONS_H
#define BUTTONS_H

#define INACTIVE 1
#define ACTIVE 0

enum _ButtonType {
    TAPPED,
    PRESSED,
};

enum _DebounceState {
  StableR,
  StableP,
  TransitionRP,
  TransitionPR
};

struct _Button {

  // buttons
  int pin;

  int pushState;
  bool isTapped;

  _DebounceState debounceState;

  unsigned long timerStart;
  unsigned long debounceDelay;

  // controls
  String name;
  _ButtonType type;
  int command;
  bool firstCall;
  bool wasPressed;
};

// constructs the button
void Button_construct(_Button* button, String name, int pin, int command, _ButtonType type);

// determines if the button is tapped
bool Button_isTapped(_Button* button);

// determines if the button is pressed 
bool Button_isPressed(_Button* button);

#endif





