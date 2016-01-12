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
     * Screen LED instances.
     */
    static Led * screenLeds;

    /**
     * Status LED instance.
     */
    static Led statusLed;
};

#endif //NUMBERGUESSGAME_LEDMANAGER_H
