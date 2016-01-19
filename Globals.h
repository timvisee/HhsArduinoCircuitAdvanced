/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_GLOBALS_H
#define NUMBERGUESSGAME_GLOBALS_H

#include <Arduino.h>

/**
 * Debug mode.
 * True to enable, false to disable.
 */
const bool DEBUG = true;

/**
 * Memory update timer, in milliseconds.
 */
const int MEMORY_REPORT_INTERVAL = 2500;

/**
 * The number of LEDs available as input.
 */
const int LED_INPUT_COUNT = 4;

/**
 * The pin's of the input LEDs;
 */
const uint8_t LED_INPUT_PIN[LED_INPUT_COUNT] = {5, 6, 9, 10};

/**
 * Defines whether the input LED's are in analog or digital mode.
 */
const bool LED_INPUT_ANALOG = true;

/**
 * The pin of the output LED.
 */
const int LED_OUTPUT_PIN = 12;

/**
 * Defines whether the output LED is in analog or digital mode.
 */
const bool LED_OUTPUT_ANALOG = false;

/**
 * Defines the pin of the button that is used to shift the LED that should be toggled.
 */
const int BUTTON_SHIFT_PIN = 7;

/**
 * Defines the pin of the button that is used to toggle the selected LED.
 */
const int BUTTON_TOGGLE_PIN = 8;

/**
 * Defines the number of milliseconds when a button state has changed to prevent jitter (/bouncing).
 */
const int BUTTON_JITTER_DELAY = 50;

/**
 * Defines the number of milliseconds to show the new state of a LED before making it dimmed again.
 */
const int LED_TOGGLE_SHOW_DURATION = 1000;

/**
 * The USB serial baud rate.
 */
const int SERIAL_USB_BAUD = 19200;

#endif //NUMBERGUESSGAME_GLOBALS_H
