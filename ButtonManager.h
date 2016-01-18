/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef HHSARDUINOCIRCUITADVANCED_BUTTONMANAGER_H
#define HHSARDUINOCIRCUITADVANCED_BUTTONMANAGER_H

#include <Arduino.h>
#include "Globals.h"
#include "Button.h"

/**
 * Button manager class.
 */
class ButtonManager {
public:
    /**
     * Toggle button instance.
     */
    static Button toggleButton;

    /**
     * Shift button instance.
     */
    static Button shiftButton;
};

#endif //HHSARDUINOCIRCUITADVANCED_BUTTONMANAGER_H
