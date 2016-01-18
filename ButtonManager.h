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
     * Main button instance.
     */
    static Button button;
};

#endif //HHSARDUINOCIRCUITADVANCED_BUTTONMANAGER_H
