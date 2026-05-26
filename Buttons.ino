/*
->Debounce
-> Refresh
*/
#include "Buttons.h"

void Button_construct(Button* button, String name, int pin, int command, ButtonType type) 
{
  button->name = name;
  button->pin = pin;
  button->command = command;
  button->type = type;
  button->firstCall = true;
  button->wasPressed = false;

  button->pushState = INACTIVE;
  button->isTapped = false;
  button->debounceState = StableR;
  button->timerStart = 0;
  button->debounceDelay = 50;

  pinMode(pin, INPUT_PULLUP);
}

void Button_refresh(Button* button) 
{
  int rawButtonStatus = digitalRead(button->pin);
  int newPushState = HIGH;

  switch (button->debounceState) {

    case StableR:
      if (rawButtonStatus == LOW) {
        button->timerStart = millis();
        button->debounceState = TransitionRP;
      }
      newPushState = HIGH;
      break;

    case StableP:
      if (rawButtonStatus == HIGH) {
        button->timerStart = millis();
        button->debounceState = TransitionPR;
      }
      newPushState = LOW;
      break;

    case TransitionRP:
      if (rawButtonStatus == HIGH) {
        button->debounceState = StableR;
      } 
      else if (millis() - button->timerStart >= button->debounceDelay) {
        button->debounceState = StableP;
      }
      newPushState = HIGH;
      break;

    case TransitionPR:
      if (rawButtonStatus == LOW) {
        button->debounceState = StableP;
      } 
      else if (millis() - button->timerStart >= button->debounceDelay) {
        button->debounceState = StableR;
      }
      newPushState = LOW;
      break;
  }

  button->isTapped = (newPushState == LOW && button->pushState == HIGH);
  button->pushState = newPushState;
}

bool Button_isPressed(Button* button) { return button->pushState == LOW; }

bool Button_isTapped(Button* button) { return button->isTapped; }
