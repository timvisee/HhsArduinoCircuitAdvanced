/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "LedManager.h"

Led *LedManager::inputLeds = new Led[INPUT_LED_COUNT];
Led LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);