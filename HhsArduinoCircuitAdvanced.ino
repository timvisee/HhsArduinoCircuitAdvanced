/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 *
 * This project requires some external libraries to be installed, in the Arduino libraries directory.
 * - Arduino:
 *   The default Arduino libraries, installed with the Arduino installer.
 *
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include <Arduino.h>
#include "Core.h"

/**
 * Core instance. For all basic logic.
 */
Core core;

/**
 * Called one on set up.
 */
void setup() {
    // Route the setup call to the core class
    core.setup();
}

/**
 * Called each loop.
 */
void loop() {
    // Route the loop call to the core class
    core.loop();
}