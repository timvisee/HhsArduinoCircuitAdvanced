/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef HHSARDUINOCIRCUITADVANCED_LEDMANAGER_H
#define HHSARDUINOCIRCUITADVANCED_LEDMANAGER_H

#include <Arduino.h>
#include "Globals.h"
#include "Led.h"

/**
 * Led manager class.
 */
class LedManager {
private:
    /**
     * Defines the index of the selected LED.
     */
    static uint8_t selectedLedIndex;

public:
    /**
     * InputLED instances.
     */
    static Led *inputLeds;

    /**
     * Output LED instance.
     */
    static Led outputLed;

    /**
     * Status LED instance.
     */
    static Led statusLed;

    /**
     * Get the index of the selected LED.
     *
     * @return The index of the selected LED.
     */
    static uint8_t getSelectedLedIndex();

    /**
     * Set the index of the selected LED.
     *
     * @param index LED index.
     */
    static void setSelectedLedIndex(int index);

    /**
     * Select the next LED.
     */
    static void nextLed();
};

#endif //HHSARDUINOCIRCUITADVANCED_LEDMANAGER_H
