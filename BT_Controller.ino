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
    // app.abxyButtons[0] = aPin;
    // app.abxyButtons[1] = bPin;
    // app.abxyButtons[2] = xPin;
    // app.abxyButtons[3] = yPin;

    // app.abxyCommands[0] = aCommand;
    // app.abxyCommands[1] = bCommand;
    // app.abxyCommands[2] = xCommand;
    // app.abxyCommands[3] = yCommand;

    // app.triggerButtons[0] = leftTriggerPin;
    // app.triggerButtons[1] = rightTriggerPin;

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

  // pinMode(aPin, INPUT_PULLUP);
  // pinMode(bPin, INPUT_PULLUP);
  // pinMode(xPin, INPUT_PULLUP);
  // pinMode(yPin, INPUT_PULLUP);
}


Application app = Application_construct();
void loop() {

  if (bleKeyboard.isConnected()) {
    // readWriteABXY(&app);
  }
  Serial.println("Disconnected");
}

void readWriteABXY(Application* app) {
  if (digitalRead(aPin) == LOW) {
    tap_button(aCommand);
  }

  if (digitalRead(bPin) == LOW) {
    tap_button(bCommand);
  }

  if (digitalRead(xPin) == LOW) {
    toggle_button(xCommand);
  }
}


void tap_button(Pin pin, int command) {
  if (pin.type != TAPPED) return;
  bleKeyboard.press(command);
  delay(100);
  bleKeyboard.release(command);
}


void toggle_button(Pin pin, int command) {
  if (pin.type != TOGGLED) return;

  if (pin.firstCall == false) {
    bleKeyboard.press(command);
    pin.firstCall = true;
  } else {
    bleKeyboard.release(command);
    pin.firstCall = false;
  }
  
}

