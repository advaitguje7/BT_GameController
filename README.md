This is a program to play games via Bluetooth using an ESP-32. It is designed around Minecraft's default binds, but the controls are modular. Note that this program uses the BleKeyboard library, which requires you to downgrade the ESP-32 version to 2.0.17. This program was designed for iOS, with other platforms untested as of writing this (5/18/26).

## Features
- [x] General eatures of an xbox/playstation controller (ABXY, triggers, D-pad, buttons)
- [x] Compatable with iOS
- [ ] Non-blocking Joystick Control
- [ ] Untested with any other platform

## DevLog

### [1/31/26] - First Iteration: Spagetti Code
- [x] Basic motion: strafing (buttons), looking around (joystick 1)
- [x] Advanced Motion: Run linear and translational motion simultaneously (look around while walking)
- [x] Hardware-based Changes: Replace buttons with a second joystick, implement ABXY control with buttons, add other buttons (LT, RT, LB, RB)
- [x] Optimization: Improve deadzones, turn speeds, and implement device naming functionality

### [5/12/26] - Second Iteration: Refactor
#### Modular Architecture
- [x] Implemented a `Button` struct to hold pin addresses, commands, debounce states, and button behaviors.
- [x] Created separate `Buttons` and `Joystick` files to hold specific functions in the HAL
#### Non-Blocking Code
- [x] Defined dedicated read/write functions for each section of the controller to poll each input once every loop iteration.
- [x] Replaced  `delay()` with software timers (using `millis()` and a Finite State Machine to debounce buttons.
- [x] Added  separate `tap` and `pressed` logic for modular button handling. 

## Schematic
<img width="808" height="501" alt="image" src="https://github.com/user-attachments/assets/acdf3180-b2ea-4c29-97d9-1294470191ae" />
