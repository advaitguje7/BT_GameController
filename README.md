This is a program to play games via Bluetooth using an ESP-32. It is designed around Minecraft's default binds, but the controls can be changed as needed. Note that this program uses the BleKeyboard library, which requires you to downgrade the ESP-32 version to 2.0.17.

## Current To-Do
- [ ] Make README more detailed
- [ ] Revamp Software
- [ ] Revamp Hardware

## Engineering DevLog

### [1/31/26] - First Iteration: Spagetti Code
- [x] Basic motion: strafing (buttons), looking around (joystick 1)
- [x] Advanced Motion: Run linear and translational motion simultaneously (look around while walking)
- [x] Hardware-based Changes: Replace buttons with a second joystick, implement ABXY control with buttons, add other buttons (LT, RT, LB, RB)
- [x] Optimization: Improve deadzones, turn speeds, and implement device naming functionality

### [5/12/26] - Second Iteration: Refactor
- [x] Implemented a `Button` struct to encapsulate pin addresses, commands, debounce states, and button behaviors.
- [x] Replaced blocking delays with `millis()` software timers and a Finite State Machine (FSM) for button debouncing.
- [x] Refactored monolithic polling into a modular HAL/Application architecture with dedicated read/write functions.
- [x] Added discrete `tap`, `toggle`, and `pressed` logic for scalable button behavior handling.
- [ ] Future Work: Implement long-press functionality and transition to external pull-down resistors.

## Schematic
<img width="808" height="501" alt="image" src="https://github.com/user-attachments/assets/acdf3180-b2ea-4c29-97d9-1294470191ae" />
