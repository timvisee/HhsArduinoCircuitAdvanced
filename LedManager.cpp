/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "LedManager.h"

Led *LedManager::inputLeds = new Led[LED_INPUT_COUNT];
Led LedManager::outputLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);
Led LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);

uint8_t LedManager::getSelectedLedIndex() {
    return LedManager::selectedLedIndex;
}

void LedManager::setSelectedLedIndex(int index) {
    LedManager::selectedLedIndex = index;
}

void LedManager::nextLed() {
    // Increase the LED index
    LedManager::selectedLedIndex++;

    // Make sure the selection doesn't go out of bounds
    if(LedManager::selectedLedIndex >= LED_INPUT_COUNT || LedManager::selectedLedIndex < 0)
        LedManager::selectedLedIndex = 0;
}