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

    /**
     * Defines the states of each input LED.
     */
    static bool *inputStates;

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
    static void setSelectedLedIndex(uint8_t index);

    /**
     * Select the next LED.
     */
    static void nextLed();

    /**
     * Get the input state of a specific input LED.
     *
     * @return Input state.
     */
    static bool getInputState(uint8_t index);

    /**
     * Set the input state of a specific input LED.
     *
     * @param index Input LED index.
     * @param state Input state.
     */
    static void setInputState(uint8_t index, bool state);

    /**
     * Toggle the state of the specified input LED.
     *
     * @param index Input LED index.
     */
    static void toggleInputState(uint8_t index);

    /**
     * Set the input state of all input LEDs.
     *
     * @param state Input state.
     */
    static void setInputStates(bool state);
};

#endif //HHSARDUINOCIRCUITADVANCED_LEDMANAGER_H
