#include "Joystick.h"

void Joystick_construct(_Joystick* joystick, 
                          String name, 
                          int pin_x, 
                          int pin_y, 
                          int pin_jsb, 
                          int command_x_left, 
                          int command_x_right, 
                          int command_y_down, 
                          int command_y_up,
                          int command_jsb) 
{
  joystick->name = name;

  joystick->pin_x = pin_x;
  joystick->pin_y = pin_y;
  joystick->pin_jsb = pin_jsb;

  joystick->command_x_left = command_x_left;
  joystick->command_x_right = command_x_right;
  joystick->command_y_up = command_y_up;
  joystick->command_y_down = command_y_down;

  joystick->jsb.firstCall = true;
  joystick->jsb.wasPressed = false;

  joystick->jsb.pushState = INACTIVE;
  joystick->jsb.isTapped = false;
  joystick->jsb.debounceState = StableR;
  joystick->jsb.timerStart = 0;
  joystick->jsb.debounceDelay = 50;

  pinMode(pin_x, INPUT_PULLUP);
  pinMode(pin_y, INPUT_PULLUP);
  
  Button_construct(&joystick->jsb, "JSB", pin_jsb, command_jsb, TAPPED);

}

