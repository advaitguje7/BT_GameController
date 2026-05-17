/*Standard Includes*/
#include <string>

/*HAL and Application Includes*/
#include "BT_Controller.h"
#include "Buttons.h"
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("BTGC", "Manufacturer", 100);

Application app;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin(); 

  app = Application_construct();

  // pinMode(leftTriggerPin, INPUT_PULLUP);
  // pinMode(rightTriggerPin, INPUT_PULLUP);

  // pinMode(leftButtonPin, INPUT_PULLUP);
  // pinMode(rightButtonPin, INPUT_PULLUP);
}

void loop() {

  if (bleKeyboard.isConnected()) {
    if (app.firstCall) {
      Serial.println("[Device Connected]");
      app.firstCall = false;
    }
    HAL_refresh(&app);

    readWriteABXY(&app);
    // readWriteTriggers(&app);
  } else {
    if (!app.firstCall) {
      Serial.println("[Device Disconnected]");
      app.firstCall = true;
    }
  }
}

void setupButtons(Application* app) 
{  
  Button_construct(&app->aButton, "A", aPin, aCommand, PRESSED);
  Button_construct(&app->bButton, "B", bPin, bCommand, TAPPED);
  Button_construct(&app->xButton, "X", xPin, xCommand, TAPPED);
  // Button_construct(&app->yButton, "Y", yPin, yCommand, TAPPED);
}

Application Application_construct() {
    setupButtons(&app);

    app.firstCall = true;

    

    // app.leftTrigger.name = "LT";
    // app.leftTrigger.pin = leftTriggerPin;
    // app.leftTrigger.type = TAPPED;
    // app.leftTrigger.firstCall = false;

    // app.rightTrigger.name = "RT";
    // app.rightTrigger.pin = rightTriggerPin;
    // app.rightTrigger.type = TAPPED;
    // app.rightTrigger.firstCall = false;

    // app.dpadButtons[0] = dpadUpPin;
    // app.dpadButtons[1] = dpadRightPin;
    // app.dpadButtons[2] = dpadDownPin;
    // app.dpadButtons[3] = dpadLeftPin;
    return app;
}

void HAL_refresh(Application* app){
  Button_refresh(&app->aButton);
  Button_refresh(&app->bButton);
  Button_refresh(&app->xButton);
  // Button_refresh(&app->yButton);

  // Button_refresh(&app->leftTrigger);
  // Button_refresh(&app->rightTrigger);

  // Button_refresh(&app->leftButton);
  // Button_refresh(&app->rightButton);
}

void readWriteABXY(Application* app)
{
  press_button(&app->aButton);
  tap_button(&app->bButton);
  tap_button(&app->xButton); 
  tap_button(&app->yButton);
}

// void readWriteTriggers(Application* app)
// {
//   if (Button_isPressed(&app->leftTrigger)) press_button(&app->leftTrigger);
//   if (Button_isPressed(&app->rightTrigger)) press_button(&app->rightTrigger);
// }

// void readWriteBackButtons(Application* app)
// {
//   if (Button_isTapped(&app->leftButton)) tap_button(&app->leftButton);
//   if (Button_isTapped(&app->rightButton)) tap_button(&app->rightButton);
// }

void tap_button(Button* button) {
if (button->type != TAPPED) {
    Serial.print("Wrong Type for Pin:"); 
    Serial.println(button->name);
    return;
  }
  if (Button_isTapped(button)) {
    bleKeyboard.write(button->command);
    Serial.println(button->name);
  }
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

void press_button(Button* button) {
  if (button->type != PRESSED) {
    Serial.print("Wrong Type for Pin:"); 
    Serial.println(button->name);
    return;
  }

  bool isPressed = Button_isPressed(button);

  if (!button->wasPressed && isPressed) {
    bleKeyboard.press(button->command);
    // delay(M_DELAY);
    Serial.println(button->name);
  } else if (button->wasPressed && !isPressed) {
    bleKeyboard.release(button->command);
  }

  button->wasPressed = isPressed;
}