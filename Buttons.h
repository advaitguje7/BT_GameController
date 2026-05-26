#ifndef BUTTONS_H
#define BUTTONS_H

#define INACTIVE 1
#define ACTIVE 0

enum ButtonType {
    TAPPED,
    PRESSED,
};

enum _DebounceState {
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

  _DebounceState debounceState;

  unsigned long timerStart;
  unsigned long debounceDelay;

  // controls
  String name;
  ButtonType type;
  int command;
  bool firstCall;
  bool wasPressed;
};

// constructs the button
void Button_construct(Button* button, String name, int pin, int command, ButtonType type);

// determines if the button is tapped
bool Button_isTapped(Button* button);

// determines if the button is pressed 
bool Button_isPressed(Button* button);

#endif





