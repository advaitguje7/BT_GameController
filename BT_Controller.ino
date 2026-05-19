/*Standard Includes*/
#include <string>

/*HAL and Application Includes*/
#include "BT_Controller.h"
#include "Buttons.h"
#include <BleKeyboard.h>
#include <BleGamepad.h>

BleKeyboard bleKeyboard("BTGC", "AdvaitG", 100);
// BleGamepad bleGamepad("BTGC", "lemmingDev", 100);


Application app;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin(); 


  app = Application_construct();
}

void loop() {

  if (bleKeyboard.isConnected()) {

    if (app.firstCall) 
    {
      Serial.println("[Device Connected]");
      app.firstCall = false;
    }

    HAL_refresh(&app);

    readWriteABXY(&app);
    readWriteTriggers(&app);
    readWriteBackButtons(&app);

  } else 
  {
    if (!app.firstCall) 
    {
      Serial.println("[Device Disconnected]");
      app.firstCall = true;
    }
  }
}

void setupButtons(Application* app) 
{  
  Button_construct(&app->aButton, "A", aPin, COMMAND_A, PRESSED);
  Button_construct(&app->bButton, "B", bPin, COMMAND_B, TAPPED);
  Button_construct(&app->xButton, "X", xPin, COMMAND_X, TAPPED);
  Button_construct(&app->yButton, "Y", yPin, COMMAND_Y, TAPPED);

  Button_construct(&app->leftTrigger, "LT", leftTriggerPin, COMMAND_LT, PRESSED);
  Button_construct(&app->rightTrigger, "RT", rightTriggerPin, COMMAND_RT, PRESSED);

  Button_construct(&app->leftButton, "LB", leftButtonPin, COMMAND_LB, TAPPED);
  Button_construct(&app->rightButton, "RB", rightButtonPin, COMMAND_RB, TAPPED);
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

void tap_button(Button* button) {
  if (button->type != TAPPED) return;

  if (Button_isTapped(button)) {
    bleKeyboard.write(button->command);
    Serial.println(button->name);
  }
}


void press_button(Button* button) {
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

// void toggle_button(Button* button) 
// {
// if (button->type != TOGGLED) {
//     Serial.print("Wrong Type for Pin:"); 
//     Serial.println(button->name);
//     return;
//   }
//   if (button->firstCall == true) {
//     bleKeyboard.press(button->command);
//     Serial.println(button->name);
//     button->firstCall = false;
//   } else if (button->firstCall == false){
//     bleKeyboard.release(button->command);
//     button->firstCall = true;
//   }
// }