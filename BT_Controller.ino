#include <BleCombo.h>

//BleComboKeyboard Keyboard("BT-Controller");
//BleComboMouse Mouse;

#define Wpin 27
#define Apin 14
#define Spin 12
#define Dpin 13

#define ANALOG_X_PIN_RS 34
#define ANALOG_Y_PIN_RS 35
#define ANALOG_BUTTON_PIN_RS 32

#define ANALOG_X_PIN_LS 26
#define ANALOG_Y_PIN_LS 25
#define ANALOG_BUTTON_PIN_LS 33

const int deadzone_max = 253; // Change to the maximum value seen when joystick is at rest
const int deadzone_min = 2;  // Change to the minimum value seen when joystick is at rest

// for greater precision
const int deadzoneX_max = 200; // Change to the maximum X-value seen when joystick is at rest
const int deadzoneX_min = 50;  // Change to the minimum X-value seen when joystick is at rest

const int deadzoneY_max = 200; // Change to the maximum Y-value seen when joystick is at rest
const int deadzoneY_min = 50;  // Change to the minimum Y-value seen when joystick is at rest
	 
struct button { 
	 byte pressed = 0; 
}; 
	 
struct analog { 
	 short x, y; 
	 
	 button btn; 
}; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // buttin pin config
  pinMode(Wpin, INPUT_PULLUP);
  pinMode(Apin, INPUT_PULLUP);
  pinMode(Spin, INPUT_PULLUP);
  pinMode(Dpin, INPUT_PULLUP);

 

  // joystick config
  pinMode(ANALOG_BUTTON_PIN_RS, INPUT_PULLUP); 
  pinMode(ANALOG_BUTTON_PIN_LS, INPUT_PULLUP); 


  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  bool anyButtonPressed = false;
  bool isShiftPressed = false;

  if ( (digitalRead(Wpin) == LOW) || (digitalRead(Apin) == LOW) || (digitalRead(Spin) == LOW) || (digitalRead(Dpin) == LOW) ) {
    anyButtonPressed = true;
  } else {
    anyButtonPressed = false;
  }

   analog analogRS;
   analog analogLS; 
	 
    analogRS.x = readAnalogAxisLevel(ANALOG_X_PIN_RS); 
    analogRS.y = readAnalogAxisLevel(ANALOG_Y_PIN_RS); 

    analogLS.x = readAnalogAxisLevel(ANALOG_X_PIN_LS); 
    analogLS.y = readAnalogAxisLevel(ANALOG_Y_PIN_LS);
    
    analogRS.btn.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN_RS);
    analogLS.btn.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN_LS); 

  if(Keyboard.isConnected()) {

    bool isShiftPressed = false;

    Serial.print("X_RS:"); 
    Serial.print(analogRS.x);

    Serial.print("\t");
    
    Serial.print("Y_RS:"); 
    Serial.print(analogRS.y);

    Serial.print("\t");

    Serial.print("X_LS:"); 
    Serial.print(analogLS.x); 

    Serial.print("\t");

    Serial.print("Y_LS:"); 
    Serial.println(analogLS.y);

    // BUTTONS
    if (digitalRead(Wpin) == LOW) {
      Keyboard.press(119); // w
      Serial.println("W");
      delay(150);

    } else if (digitalRead(Apin) == LOW) {
      Keyboard.press(97); // a
      Serial.println("A");
      delay(15);

    } else if (digitalRead(Spin) == LOW) {
      Keyboard.press(115); // s
      Serial.println("S");
      delay(15);

    } else if (digitalRead(Dpin) == LOW) {
      Keyboard.press(100); // d
      Serial.println("D");
      delay(15);

    } 
    // JOYSTICK RS
    if (analogRS.x > deadzone_max) {
      
      Keyboard.press(218); // up arrow -> look up

    } if (analogRS.x < deadzone_min) {
      
      Keyboard.press(217); // down arrow -> look down

    } 
    if (analogRS.y > 200) {
      
      Keyboard.press(215); // right arrow -> look right

    } 
    if (analogRS.y < deadzone_min) {
      
      Keyboard.press(216); // left arrow -> look left

    } 

    if (analogRS.btn.pressed) {
      Keyboard.press(KEY_LEFT_SHIFT); // left shift -> sneak
      isShiftPressed = true;
    }

    // JOYSTICK LS
    if (analogLS.x > deadzone_max) {
      
      Keyboard.press(119); // w -> move forward

    } if (analogLS.x < deadzone_min) {
      
      Keyboard.press(115); // s -> move backward

    } 
    if (analogLS.y > deadzone_max) {
      
      Keyboard.press(100); // d -> strafe right

    } 
    if (analogLS.y < deadzone_min) {
      
      Keyboard.press(97); // a -> strafe left

    } 

    if (analogLS.btn.pressed) {
      Keyboard.press(0x20); // space bar -> jump
    } else {
      Keyboard.release(0x20);
    }

    if (!anyButtonPressed && isJoystickDead(analogRS) && isJoystickDead(analogLS)) {
      Keyboard.releaseAll();
      if (isShiftPressed) {
        Keyboard.press(KEY_LEFT_SHIFT);
      }
    } else if (isJoystickDead(analogRS)) {
      releaseRS();
    } else if (isJoystickDead(analogRS)) {
      releaseLS();
    }
    delay(100);
  }
}

byte readAnalogAxisLevel(int pin) 
{ 
	 return map(analogRead(pin), 0, 1023, 0, 1023); 
} 
	 
bool isAnalogButtonPressed(int pin) 
{ 
	 return digitalRead(pin) == 0; 
} 

bool isJoystickDead(analog analog) {
  if ((analog.x > deadzone_min) && (analog.y > deadzone_min) && (analog.x < deadzone_max) && (analog.y < deadzone_max)) {
      return true;
    } else {
      return false;
    }
}

void releaseRS() {
  Keyboard.release(218);
  Keyboard.release(217);
  Keyboard.release(215);
  Keyboard.release(216);
}

void releaseLS() {
  Keyboard.release(119);
  Keyboard.release(97);
  Keyboard.release(115);
  Keyboard.release(100);
}


