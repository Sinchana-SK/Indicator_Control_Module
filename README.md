Indicator Control Module — Embedded Firmware
This project implements embedded firmware for a vehicle Indicator Control Module (ICM) simulating real automotive indicator and hazard light behaviour.
Hardware

Arduino Uno
2x push buttons (left and right indicator inputs)
2x LEDs with resistors (left and right indicator outputs)
Breadboard and jumper wires

Features

Left and right indicator toggle with 1 second button hold
Automatic indicator switching (left to right and vice versa)
Hazard mode activated by holding both buttons simultaneously
300ms LED blink timing for active indicators and hazard mode
Button debouncing with hold detection
100ms task scheduler
UART logging of all system events via Serial Monitor
State machine based application logic designed in MATLAB Simulink Stateflow

Software Architecture

Base Software layer — GPIO, timer, UART, and debounce drivers in C++
Application Software layer — indicator state machine logic

Tools Used

Arduino IDE
MATLAB Simulink + Stateflow + Embedded Coder
