/*Standard Includes*/
#include <string>

/*HAL and Application Includes*/
#include "Wireless-Gamepad.h"
#include "Buttons.h"
#include "Joystick.h"
#include <BleKeyboard.h>
#include <BleGamepad.h>

BleKeyboard bleKeyboard("BTGC", "advaitguje7", 100);
// BleGamepad bleGamepad("BTGC", "advaitguje7", 100);


Application app;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin(); 
  app = Application_construct();    

}

void loop() {

  if (bleKeyboard.isConnected()) {
    // digitalWrite(ledPin, HIGH);
    if (app.firstCall) {
      Serial.println("[Device Connected]");
      app.firstCall = false;
    }

    HAL_refresh(&app);

    readWriteABXY(&app);
    readWriteTriggers(&app);
    readWriteBackButtons(&app);
    readWriteHats(&app);
    readJoysticks(&app);
    writeJoysticks(&app);

    delay(10);

  } else {
    if (!app.firstCall) {
      Serial.println("[Device Disconnected]");
      app.firstCall = true;
      delay(500);
    }
  }
}

void setupButtons(Application* app) 
{  
  Button_construct(&app->aButton, "A", PIN_A, COMMAND_A, PRESSED);
  Button_construct(&app->bButton, "B", PIN_B, COMMAND_B, TAPPED);
  Button_construct(&app->xButton, "X", PIN_X, COMMAND_X, TAPPED);
  Button_construct(&app->yButton, "Y", PIN_Y, COMMAND_Y, TAPPED);

  Button_construct(&app->leftTrigger, "LT", PIN_LT, COMMAND_LT, PRESSED);
  Button_construct(&app->rightTrigger, "RT", PIN_RT, COMMAND_RT, PRESSED);

  Button_construct(&app->leftButton, "LB", PIN_LB, COMMAND_LB, TAPPED);
  Button_construct(&app->rightButton, "RB", PIN_RB, COMMAND_RB, TAPPED);

  Button_construct(&app->hatUpButton, "HAT_UP", PIN_HAT_UP, COMMAND_HAT_UP, TAPPED);
  Button_construct(&app->hatDownButton, "HAT_DOWN", PIN_HAT_DOWN, COMMAND_HAT_DOWN, PRESSED);
  Button_construct(&app->hatLeftButton, "HAT_LEFT", PIN_HAT_LEFT, COMMAND_HAT_LEFT, TAPPED);
  Button_construct(&app->hatRightButton, "HAT_RIGHT", PIN_HAT_RIGHT, COMMAND_HAT_RIGHT, TAPPED);
}

void setupJoysticks(Application* app)
{
  Joystick_construct(&app->leftJoystick, "LS", PIN_LS_X, PIN_LS_Y, PIN_LS_JSB, COMMAND_LS_X_LEFT, COMMAND_LS_X_RIGHT, COMMAND_LS_Y_UP, COMMAND_LS_Y_DOWN, COMMAND_LS_JSB); 
  Joystick_construct(&app->rightJoystick, "RS", PIN_RS_X, PIN_RS_Y, PIN_RS_JSB, COMMAND_RS_X_LEFT, COMMAND_RS_X_RIGHT, COMMAND_RS_Y_UP, COMMAND_RS_Y_DOWN, COMMAND_RS_JSB);                                                                               // !!!
}

Application Application_construct() {
    setupButtons(&app);
    setupJoysticks(&app);
    app.firstCall = true;

    return app;
}

void HAL_refresh(Application* app){
  Button_refresh(&app->aButton);
  Button_refresh(&app->bButton);
  Button_refresh(&app->xButton);
  Button_refresh(&app->yButton);

  Button_refresh(&app->leftTrigger);
  Button_refresh(&app->rightTrigger);

  Button_refresh(&app->leftButton);
  Button_refresh(&app->rightButton);

  Button_refresh(&app->hatUpButton);
  Button_refresh(&app->hatDownButton);
  Button_refresh(&app->hatLeftButton);
  Button_refresh(&app->hatRightButton);

  Button_refresh(&app->leftJoystick.jsb);
  Button_refresh(&app->rightJoystick.jsb);

}

void tap_button(_Button* button) 
{
  if (button->type != TAPPED) return;

  if (Button_isTapped(button)) {
    bleKeyboard.write(button->command);
    Serial.println(button->name);
  }
}




void press_button(_Button* button) 
{
  if (button->type != PRESSED) return;

  bool isPressed = Button_isPressed(button);

  if (!button->wasPressed && isPressed) {
    bleKeyboard.press(button->command);
    Serial.println(button->name);
  } else if (button->wasPressed && !isPressed) {
    bleKeyboard.release(button->command);
  }

  button->wasPressed = isPressed;
}

void readWriteABXY(Application* app)
{
  press_button(&app->aButton);
  tap_button(&app->bButton);
  tap_button(&app->xButton); 
  tap_button(&app->yButton);
}

void readWriteTriggers(Application* app)
{
  press_button(&app->leftTrigger);
  press_button(&app->rightTrigger);
}

void readWriteBackButtons(Application* app)
{
  tap_button(&app->leftButton);
  tap_button(&app->rightButton);
}

void readWriteHats(Application* app)
{
  tap_button(&app->hatUpButton);
  press_button(&app->hatDownButton);
  tap_button(&app->hatLeftButton); 
  tap_button(&app->hatRightButton);
}

void readJoysticks(Application* app)
{
  app->leftJoystick.x = readAnalogAxisLevel(PIN_LS_X); 
  app->leftJoystick.y = readAnalogAxisLevel(PIN_LS_Y);
  app->leftJoystick.jsb.isTapped = Button_isTapped(&app->leftJoystick.jsb);
 
  app->rightJoystick.x = readAnalogAxisLevel(PIN_RS_X); 
  app->rightJoystick.y = readAnalogAxisLevel(PIN_RS_Y);   
  app->rightJoystick.jsb.isTapped = Button_isTapped(&app->rightJoystick.jsb); 
}

void writeJoysticks(Application* app)
{
  tap_joystick(&app->leftJoystick);
  tap_joystick(&app->rightJoystick);
}

void tap_joystick(_Joystick* joystick) 
{
  if (joystick->x < THRESHOLD_MIN) {
    bleKeyboard.press(joystick->command_x_left);

    Serial.print(joystick->name);
    Serial.print(":\t");
    Serial.println("LEFT");
  } else {
    bleKeyboard.release(joystick->command_x_left);
  }

  if (joystick->x > THRESHOLD_MAX) {
    bleKeyboard.press(joystick->command_x_right);

    Serial.print(joystick->name);
    Serial.print(":\t");
    Serial.println("RIGHT");
  } else {
    bleKeyboard.release(joystick->command_x_right);
  }

  if (joystick->y < THRESHOLD_MIN) {
    bleKeyboard.press(joystick->command_y_down);

    Serial.print(joystick->name);
    Serial.print(":\t");
    Serial.println("DOWN");
  } else {
    bleKeyboard.release(joystick->command_y_down);
  }

  if (joystick->y > THRESHOLD_MAX) {
    bleKeyboard.press(joystick->command_y_up);

    Serial.print(joystick->name);
    Serial.print(":\t");
    Serial.println("UP");
  } else {
    bleKeyboard.release(joystick->command_y_up);
  }
}

byte readAnalogAxisLevel(int pin) 
{ 
	 return map(analogRead(pin), 0, 4095, 0, 255); 
} 