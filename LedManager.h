/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef NUMBERGUESSGAME_LEDMANAGER_H
#define NUMBERGUESSGAME_LEDMANAGER_H

#include <Arduino.h>
#include "Globals.h"
#include "Led.h"

/**
 * Led manager class.
 */
class LedManager {
public:
    /**
     * InputLED instances.
     */
    static Led *inputLeds;

    /**
     * Status LED instance.
     */
    static Led statusLed;
};

#endif //NUMBERGUESSGAME_LEDMANAGER_H
