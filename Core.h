/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef HHSARDUINOCIRCUITADVANCED_CORE_H
#define HHSARDUINOCIRCUITADVANCED_CORE_H

#include <Arduino.h>
#include "Globals.h"
#include "Led.h"
#include "LedManager.h"
#include "Button.h"

/**
 * Core class.
 */
class Core {
private:
    /**
     * Flag whether the device has been fully started or not.
     */
    bool started;

    /**
     * Flag whether we're currently in the input mode.
     * True if we're in the input mode, false if not.
     */
    bool inputMode;

public:
    /**
     * Constructor.
     */
    Core();

    /**
     * Called once on set up.
     */
    void setup();

    /**
     * Called each loop.
     */
    void loop();

    /**
     * Method used to update all game logic.
     */
    void updateLogic();

    /**
     * A smart delay method, to efficiently execute the update call while waiting.
     */
    void smartDelay(int delay);

    /**
     * Check whether the device is currently in input mode.
     *
     * @return True if in input mode, false otherwise.
     */
    bool isInputMode();

    /**
     * Start the input mode.
     */
    void startInputMode();

    /**
     * Stop the input mode.
     */
    void stopInputMode();
};

#endif //HHSARDUINOCIRCUITADVANCED_CORE_H
