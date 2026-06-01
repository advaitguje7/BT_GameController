This is a program to play games via Bluetooth using an ESP-32. It is designed around Minecraft's default binds, but the controls are modular. Note that this program uses the BleKeyboard library, which requires you to downgrade the ESP-32 version to 2.0.17. This program was designed for iOS, with other platforms untested as of writing this (5/18/26).

## Features
- [ ] General features of an xbox/playstation controller
  - [x] ABXY Pad
  - [x] D-Pad
  - [x] Triggers
  - [x] Buttons (LB, RB)
  - [x] Joysticks (2)
  - [ ] Start
  - [ ] Menu
- [x] Compatable with iOS
- [ ] Untested with any other platform (Andriod, Windows, etc)

## DevLog

### [1/31/26] - V1: Spagetti Code
- [x] Basic motion: strafing (buttons), looking around (joystick 1)
- [x] Advanced Motion: Run linear and translational motion simultaneously (look around while walking)
- [x] Hardware-based Changes: Replace buttons with a second joystick, implement ABXY control with buttons, add other buttons (LT, RT, LB, RB)
- [ ] Optimization: Improve deadzones, turn speeds, and implement device naming functionality

The goal was to get a basic skeleton that worked. This involved an if-else tree that polled every single input and either pressed or released each corresponding command. The program worked, although multiple delay() uses blocked the code. The controller was also not especially sensitive due to these delays.

### [5/12/26] - V2: Refactor
#### Modular Architecture
- [x] Structs hold all the properties of a given input, including pin addresses, commands, debounce states, and button behaviors.
- [x]  `Construct` functions to allow the user to define said properties
- [x] Separate `Buttons` and `Joystick` files to hold specific functions in the HAL
#### Non-Blocking Code
- [x] Defined dedicated read/write functions for each section of the controller to poll each input once every loop iteration.
- [x] Replaced `delay()` with software timers (using `millis()`) and a Finite State Machine (FSM) to debounce buttons (shown below).

The program was completely restructured. A button struct held the properties of each button so the name, pin, command, type (tapped, pressed), and debounce variables. This allowed for a debounce FSM. A construct function was then able to define every button's properties.

## Schematic
[In Progress]
