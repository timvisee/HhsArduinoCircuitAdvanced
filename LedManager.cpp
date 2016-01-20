/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "LedManager.h"

// Initializations
bool *LedManager::inputStates = new bool[LED_INPUT_COUNT];
Led *LedManager::inputLeds = new Led[LED_INPUT_COUNT];
Led LedManager::outputLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);
Led LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);

uint8_t LedManager::getSelectedLedIndex() {
    return LedManager::selectedLedIndex;
}

void LedManager::setSelectedLedIndex(uint8_t index) {
    LedManager::selectedLedIndex = index;
}

void LedManager::nextLed() {
    // Increase the LED index
    LedManager::selectedLedIndex++;

    // Make sure the selection doesn't go out of bounds
    if(LedManager::selectedLedIndex >= LED_INPUT_COUNT || LedManager::selectedLedIndex < 0)
        LedManager::selectedLedIndex = 0;
}

bool LedManager::getInputState(uint8_t index) {
    return LedManager::inputStates[index];
}

void LedManager::setInputState(uint8_t index, bool state) {
    LedManager::inputStates[index] = state;
}

void LedManager::toggleInputState(uint8_t index) {
    LedManager::inputStates[index] = !LedManager::inputStates[index];
}

void LedManager::toggleCurrentInputState() {
    LedManager::toggleInputState(LedManager::getSelectedLedIndex());
}

void LedManager::setInputStates(bool state) {
    // Use a for loop to set the state of each LED
    for(uint8_t i = 0; i < LED_INPUT_COUNT; i++)
        LedManager::setInputState(i, state);
}