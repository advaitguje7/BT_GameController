#ifndef JOYSTICK_H
#define JOYSTICK_H

#define THRESHOLD_MIN 1
#define THRESHOLD_MAX 250

struct _Joystick { 
	int pin_x;
  int pin_y;
  int pin_jsb;
  String name;
  int command_x_left;
  int command_x_right;
  int command_y_up;
  int command_y_down;

  short x, y; 
	_Button jsb; 
}; 

// constructs the joystick
void Joystick_construct(_Joystick* joystick, 
                          String name, 
                          int pin_x, 
                          int pin_y, 
                          int pin_jsb, 
                          int command_x_left, 
                          int command_x_right, 
                          int command_y_up, 
                          int command_y_down,
                          int command_jsb);

#endif