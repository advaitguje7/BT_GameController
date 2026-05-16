/*Standard Includes*/
#include <string>

/*HAL and Application Includes*/
#include "BT_Controller.h"
#include "Buttons.h"
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("BTGC", "Manufacturer", 100);

Application Application_construct() {
    Application app;
    setupButtons(&app);

    app.firstCall = true;

    // // Controls
    // app.aButton.name = "A";
    // app.aButton.pin = aPin;
    // app.aButton.type = TAPPED;
    // app.aButton.firstCall = false;

    // app.bButton.name = "B";
    // app.bButton.pin = bPin;
    // app.bButton.type = TAPPED;
    // app.bButton.firstCall = false;

    // app.xButton.name = "X";
    // app.xButton.pin = xPin;
    // app.xButton.type = TOGGLED;
    // app.xButton.firstCall = false;

    // app.leftButton.name = "LB";
    // app.leftButton.pin = leftButtonPin;
    // app.leftButton.type = TAPPED;
    // app.leftButton.firstCall = false;

    // app.rightButton.name = "RB";
    // app.rightButton.pin = rightButtonPin;
    // app.rightButton.type = PRESSED;
    // app.rightButton.firstCall = false;

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

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin(); 

  // pinMode(leftTriggerPin, INPUT_PULLUP);
  // pinMode(rightTriggerPin, INPUT_PULLUP);

  // pinMode(leftButtonPin, INPUT_PULLUP);
  // pinMode(rightButtonPin, INPUT_PULLUP);
}


Application app = Application_construct();
void loop() {

  if (bleKeyboard.isConnected()) {
    if (app.firstCall) {
      Serial.println("Device Connected!");
      app.firstCall = false;
    }
    HAL_refresh(&app);

    readWriteABXY(&app);
    readWriteTriggers(&app);
  }
}

void setupButtons(Application* app) 
{  
  Button_construct(&app->aButton, "A", aPin, aCommand, PRESSED);
  Button_construct(&app->bButton, "B", bPin, bCommand, TAPPED);
  Button_construct(&app->xButton, "X", xPin, xCommand, TAPPED);
  Button_construct(&app->yButton, "Y", yPin, yCommand, TOGGLED);
}

void HAL_refresh(Application* app){
  Button_refresh(&app->aButton);
  Button_refresh(&app->bButton);
  Button_refresh(&app->xButton);
  Button_refresh(&app->yButton);

  // Button_refresh(&app->leftTrigger);
  // Button_refresh(&app->rightTrigger);

  // Button_refresh(&app->leftButton);
  // Button_refresh(&app->rightButton);
}

void readWriteABXY(Application* app)
{
  
  press_button(&app->aButton);
  // if (Button_isPressed(&app->aButton)) press_button(&app->aButton);

  if (Button_isTapped(&app->bButton)) tap_button(&app->bButton);
  if (Button_isTapped(&app->xButton)) tap_button(&app->xButton); 
}

void readWriteTriggers(Application* app)
{
  if (Button_isPressed(&app->leftTrigger)) press_button(&app->leftTrigger);
  if (Button_isPressed(&app->rightTrigger)) press_button(&app->rightTrigger);
}

void readWriteBackButtons(Application* app)
{
  if (Button_isTapped(&app->leftButton)) tap_button(&app->leftButton);
  if (Button_isTapped(&app->rightButton)) tap_button(&app->rightButton);
}

void tap_button(Button* button) {
  if (button->type != TAPPED) return;

  bleKeyboard.press(button->command);
  Serial.println(button->name);
  if (button->name == "A") delay(100);
  bleKeyboard.release(button->command);
}

void toggle_button(Button* button) {
  if (button->type != TOGGLED) return;

  if (button->firstCall == true) {
    bleKeyboard.press(button->command);
    Serial.println(button->name);
    button->firstCall = false;
  } else if (button->firstCall == false){
    bleKeyboard.release(button->command);
    button->firstCall = true;
  }
}

void press_button(Button* button) {
  if (button->type != PRESSED) return;

  bool isPressed = Button_isPressed(button);

  if (!button->wasPressed && isPressed) {
    bleKeyboard.press(button->command);
  } else if (button->wasPressed && !isPressed) {
    bleKeyboard.release(button->command);
  }

  button->wasPressed = isPressed;
}


