#include "BT_Controller.h"
#include <BleKeyboard.h>
#include <string>


BleKeyboard bleKeyboard("BT_GameController", "Manufacturer", 100);

Application Application_construct() {
    Application app;
    int i;

    // Controls
    app.aButton.name = "aButton";
    app.aButton.pin = aPin;
    app.aButton.type = TAPPED;
    app.aButton.firstCall = false;

    app.bButton.name = "bButton";
    app.bButton.pin = bPin;
    app.bButton.type = TAPPED;
    app.bButton.firstCall = false;

    app.xButton.name = "xButton";
    app.xButton.pin = xPin;
    app.xButton.type = TOGGLED;
    app.xButton.firstCall = false;

    app.leftButton.name = "leftButton";
    app.leftButton.pin = leftButtonPin;
    app.leftButton.type = TAPPED;
    app.leftButton.firstCall = false;

    app.rightButton.name = "rightButton";
    app.rightButton.pin = rightButtonPin;
    app.rightButton.type = TAPPED;
    app.rightButton.firstCall = false;


    // app.backButtons[0] = leftButtonPin;
    // app.backButtons[1] = rightButtonPin;

    // app.dpadButtons[0] = dpadUpPin;
    // app.dpadButtons[1] = dpadRightPin;
    // app.dpadButtons[2] = dpadDownPin;
    // app.dpadButtons[3] = dpadLeftPin;

   

    return app;
}

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();

  pinMode(aPin, INPUT_PULLUP);
  pinMode(bPin, INPUT_PULLUP);
  pinMode(xPin, INPUT_PULLUP);
  pinMode(yPin, INPUT_PULLUP);

  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

}


Application app = Application_construct();
void loop() {

  if (bleKeyboard.isConnected()) {
    readWriteABXY(&app);
  }
}

void readWriteABXY(Application* app) {
  if (isTapped(app->aButton.num)) {
    tap_button(&app->aButton, aCommand);
    Serial.println("A");
  }

  if (isTapped(app->bButton.num)) {
    tap_button(&app->bButton, bCommand);
    Serial.println("B");

  }

  if (isTapped(app->xButton.num)) {
    toggle_button(&app->xButton, xCommand);
    Serial.println("X");
  }
}

bool isTapped(Pin* pin) { return (!digitalRead(pin->num)); }

void tap_button(Pin* pin, int command) {
  if (pin->type != TAPPED) return;

  bleKeyboard.press(command);
  delay(50);
  bleKeyboard.release(command);
}


void toggle_button(Pin* pin, int command) {
  if (pin->type != TOGGLED) return;

  if (pin->firstCall == false) {
    bleKeyboard.press(command);
    delay(50);
    pin->firstCall = true;
  } else {
    bleKeyboard.release(command);
    pin->firstCall = false;
  }
  
}

void readWriteBackButtons(Application* app) {
  if (isTapped(app->leftButton) {
    tapButton(&app->leftButton, leftButtonCommand);
  }
}

