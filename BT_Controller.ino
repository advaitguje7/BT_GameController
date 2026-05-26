/*Standard Includes*/
#include <string>

/*HAL and Application Includes*/
#include "BT_Controller.h"
#include "Buttons.h"
#include "Joystick.h"
#include <BleKeyboard.h>
#include <BleGamepad.h>

int ledState = LOW;          
unsigned long previousMillis = 0;     
unsigned long interval = 1000UL;  

BleKeyboard bleKeyboard("BTGC", "advaitguje7", 100);
// BleGamepad bleGamepad("BTGC", "advaitguje7", 100);


Application app;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin(); 
  app = Application_construct();
  pinMode(ledPin, OUTPUT);      

}

void loop() {

  if (bleKeyboard.isConnected()) {
    digitalWrite(ledPin, HIGH);
    if (app.firstCall) {
      Serial.println("[Device Connected]");
      app.firstCall = false;
    }

    HAL_refresh(&app);

    readWriteABXY(&app);
    readWriteTriggers(&app);
    readWriteBackButtons(&app);
    readWriteHats(&app);

  } else {
    if (!app.firstCall) {
      Serial.println("[Device Disconnected]");
      app.firstCall = true;
    }
    blinkLED();
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

Application Application_construct() {
    setupButtons(&app);
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
}

void tap_button(Button* button) 
{
  if (button->type != TAPPED) return;

  if (Button_isTapped(button)) {
    bleKeyboard.write(button->command);
    Serial.println(button->name);
  }
}

void press_button(Button* button) 
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
  tap_button(&app->hatDownButton);
  tap_button(&app->hatLeftButton); 
  tap_button(&app->hatRightButton);
}


void blinkLED()
/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  Original Concept: Tom Igoe
  Original Code: David A. Mellis, Arduino Core Team
  Adapted by: Advait Guje 
  
  This example code is in the public domain.
  Original source: https://www.arduino.cc/en/Tutorial/Blink
*/
{
    if (millis() - previousMillis > interval) 
  {
    // save the last time you blinked the LED
    previousMillis += interval;  

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
}