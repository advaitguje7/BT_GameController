This is a program to play games via Bluetooth using an ESP-32. It is designed around Minecraft's default binds, but the controls are modular. Note that this program uses the BleKeyboard library, which requires you to downgrade the ESP-32 version to 2.0.17. This program was designed for iOS, with other platforms untested as of writing this (5/18/26).

## Features
- [x] Standard features of a game controller
  - [x] ABXY
  - [x] D-Pad
  - [x] Triggers
  - [x] Buttons (LB, RB)
  - [x] Joysticks (LS, RS)
  - [ ] Start
  - [ ] Menu
- [x] Compatable with iOS
- [ ] Untested with any other platform (Andriod, Windows, etc)

## DevLog

### [1/31/26] - V.1
- [x] Basic motion: strafing (buttons), looking around (joystick 1)
- [x] Advanced Motion: Run linear and translational motion simultaneously (look around while walking)
- [x] Hardware-based Changes: Replace buttons with a second joystick, implement ABXY control with buttons, add other buttons (LT, RT, LB, RB)
- [ ] Optimization: Improve deadzones, turn speeds, and implement device naming functionality

### [5/12/26] - V.2
#### Modular Architecture
- [x] Structs hold the properties of a given input, including pin addresses, commands, debounce states, and button behaviors.
- [x]  `Construct` functions to allow the user to define said properties
- [x] Separate `Buttons` and `Joystick` files to hold specific functions in the HAL
#### Non-Blocking Code
- [x] Defined dedicated read/write functions for each section of the controller.
- [x] Replaced `delay()` with software timers for debouncing.

## Schematic
[In Progress]
