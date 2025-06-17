# Stopwatch with 7-Segment Display

## Overview

This is a simple stopwatch project built using an **ATmega16 microcontroller** 
and **4-digit 7-segment display**. The stopwatch displays time in the format `SS.MM` 
(Seconds.Milliseconds) with a blinking decimal point to enhance readability. 
A single push button is used to start and stop the stopwatch.

## Hardware Setup

| Pin | Connection |
|-----|------------|
| PA0–PA6 | Segments A–G |
| PA7 | Decimal Point (DP) |
| PB0–PB3 | Digit control (CC1–CC4) |
| PD0 | Push Button (active low) |

## Project Structure
- `main.c` – Main application logic: button handling, time tracking, display updates.
- `digit.c` – Controls the 7-segment digit display, multiplexing, and segment patterns.
- `digit.h` – Header file for digit display functions and `digitmap` declaration.
- `timer.c` – Initializes Timer1, handles millisecond counting and ISR.
- `timer.h` – Header file for timer functions like `get_millis()` and `timer_init()`.

## Demo Video
[▶️ Watch the demo video](stopwatch_demo.mp4)

## License
MIT License - free for educational and personal use
