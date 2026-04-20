#include <vector>
#include <BleCombo.h>


//BleComboKeyboard Keyboard("BT-Controller");
//BleComboMouse Mouse;

// To-Do
/*
- Add Naming functionality
- Somehow make isPressed a thing that can be applied to any button
*/
// GPIO 13x, 18x, 19x, 21x, 22w, 23w, 25x, 26x, 27x, 32x, 33x.
// Buttons
#define Ypin 27
#define Xpin 14
#define Apin 12
#define Bpin 13

// D-pad
#define Dpad_up 21
#define Dpad_down 2 // 22
#define Dpad_right 5 // 23
#define Dpad_left 15

// Triggers
#define LT 19
#define RT 18
#define LB 22
#define RB 23

// Joystick
#define ANALOG_X_PIN_RS 34
#define ANALOG_Y_PIN_RS 35
#define ANALOG_BUTTON_PIN_RS 32

#define ANALOG_X_PIN_LS 26
#define ANALOG_Y_PIN_LS 25
#define ANALOG_BUTTON_PIN_LS 33

const int deadzone_max = 254; // Change to the maximum value seen when joystick is at rest
const int deadzone_min = 1;  // Change to the minimum value seen when joystick is at rest

// for greater precision
const int deadzoneX_max = 200; // Change to the maximum X-value seen when joystick is at rest
const int deadzoneX_min = 50;  // Change to the minimum X-value seen when joystick is at rest

const int deadzoneY_max = 200; // Change to the maximum Y-value seen when joystick is at rest
const int deadzoneY_min = 50;  // Change to the minimum Y-value seen when joystick is at rest

// bools
bool anyButtonPressed = false;
bool isRSPressed = false;
bool isXpinPressed = false;


struct button { 
	byte pressed = 0; 
}; 
	 
struct analog { 
	 short x, y; 
	 
	 button btn; 
}; 

std::vector<int> buttonStates {Apin, Bpin, Xpin, Ypin, Dpad_up, Dpad_down, Dpad_left, Dpad_right, RT, LT};
std::vector<int> impulseButtons {Apin, Bpin, Dpad_down};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // buttin pin config
  pinMode(Xpin, INPUT_PULLUP);
  pinMode(Ypin, INPUT_PULLUP);
  pinMode(Apin, INPUT_PULLUP);
  pinMode(Bpin, INPUT_PULLUP);

  // triggers config
  pinMode(RT, INPUT_PULLUP);
  pinMode(LT, INPUT_PULLUP);

  // dpad config
  pinMode(Dpad_up, INPUT_PULLUP);
  pinMode(Dpad_down, INPUT_PULLUP);
  pinMode(Dpad_left, INPUT_PULLUP);
  pinMode(Dpad_right, INPUT_PULLUP);

  // joystick config
  pinMode(ANALOG_BUTTON_PIN_RS, INPUT_PULLUP); 
  pinMode(ANALOG_BUTTON_PIN_LS, INPUT_PULLUP); 


  Keyboard.begin();
  Mouse.begin();
}
void loop() {
  // put your main code here, to run repeatedly:

   analog analogRS;
   analog analogLS; 
	 
    analogRS.x = readAnalogAxisLevel(ANALOG_X_PIN_RS); 
    analogRS.y = readAnalogAxisLevel(ANALOG_Y_PIN_RS); 
    analogLS.x = readAnalogAxisLevel(ANALOG_X_PIN_LS); 
    analogLS.y = readAnalogAxisLevel(ANALOG_Y_PIN_LS);   
    analogRS.btn.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN_RS);
    analogLS.btn.pressed = isAnalogButtonPressed(ANALOG_BUTTON_PIN_LS); 

  if(Keyboard.isConnected()) {

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
    
    if (digitalRead(Xpin) == LOW) {
      Keyboard.press(99); // X -> inventory
      Serial.println("X");
      isXpinPressed = true;
      
      while (isXpinPressed) {
        if (digitalRead(Xpin) == LOW) {
          Keyboard.release(99);
          isXpinPressed = false;
        } else {
          Keyboard.press(99);
        }
      delay(15);
    }
    } else if (digitalRead(Ypin) == LOW) {
      // To-Do // Y -> Undetermined
      Serial.println("Y");
      delay(15);
    } else if (digitalRead(Apin) == LOW) {
      Keyboard.press(0x20); // A -> jump 
      Serial.println("A");
      delay(15);

    } else if (digitalRead(Bpin) == LOW) {
      Keyboard.press(122); // B -> drop item
      Serial.println("B");
      delay(15);
      Keyboard.release(122);

    } 

    // Triggers
    if (digitalRead(RT) == LOW) { // RT
      Keyboard.press(113); // q -> attack/destroy
    } else {
      Keyboard.release(113);
    }

    if (digitalRead(LT) == LOW) { // LT
      Keyboard.press(101); // e -> place/use
    } else {
      Keyboard.release(101);
    }

    // Dpad
    if (digitalRead(Dpad_left) == LOW) {
      Keyboard.press(KEY_PAGE_UP);
      delay(30);
      Keyboard.release(KEY_PAGE_UP);
    } else if (digitalRead(Dpad_right) == LOW) {
      Keyboard.press(KEY_PAGE_DOWN);
      delay(15);
      Keyboard.release(KEY_PAGE_DOWN);
    } else if (digitalRead(Dpad_up) == LOW) {
      Keyboard.press(KEY_F5);
      delay(15);
      Keyboard.release(KEY_F5);
    } else if (digitalRead(Dpad_down) == LOW) {
      Keyboard.press(112);
      delay(15);
      Keyboard.release(112);
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
      isRSPressed = true;
    } 

    // JOYSTICK LS
    if (analogLS.x > deadzone_max) {
      Keyboard.press(119); // w -> move forward
    } 

    if (analogLS.y < deadzone_min) {
      Keyboard.press(97); // a -> strafe left
    } 
    
    if (analogLS.x < deadzone_min) {
      Keyboard.press(115); // s -> move backward
    } 
    if (analogLS.y > deadzone_max) {
      Keyboard.press(100); // d -> strafe right
    } 
    if (analogLS.btn.pressed && analogLS.y < 200) {
      // To-Do
      delay(500);
    } else {
      // To-Do
    }
/////////////////////////////// RELEASE CONDITION ///////////////////////////////////////
    
    if (isJoystickDead(analogRS)) {
      releaseRS();
    }
    if (isJoystickDead(analogLS)) {
      releaseLS();
    }

    // Impulse Buttons
    if (!isAnalogButtonPressed(Apin)) {
      Keyboard.release(0x20);
    }
    
    if (isAnalogButtonPressed(ANALOG_BUTTON_PIN_RS) && isRSPressed) {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
  

    delay(100);
  }
}

////////////////////////////////////////////////////
////////////////////////////////////////////////////

byte readAnalogAxisLevel(int pin) 
{ 
	 return map(analogRead(pin), 0, 4095, 0, 255); 
} 
	 
bool isAnalogButtonPressed(int pin) { 
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
  for (int i = 215; i <= 218; i++) {
    Keyboard.release(i);
  }
}

void releaseLS() {
  Keyboard.release(119);
  Keyboard.release(97);
  Keyboard.release(115);
  Keyboard.release(100);
}

void causalButtonPress(int pin, int code) {
  while (isAnalogButtonPressed(pin)) {
    Keyboard.press(code);
  }
}

void readJoysticks();
void readButtons();
void writeJoysticks();
void writeButtons();
