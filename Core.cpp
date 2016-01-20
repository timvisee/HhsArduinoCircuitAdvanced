/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Core.h"
#include "ButtonManager.h"
#include "Log.h"
#include "Random.h"
#include "Timer.h"
#include "MemoryManager.h"

Core::Core() {
    // Set the flag defaults
    this->started = false;
    this->inputMode = false;

    // Initialize the input LED array
    LedManager::inputLeds = new Led[LED_INPUT_COUNT];

    // Construct the screen LED instances
    for(int i = 0; i < LED_INPUT_COUNT; i++)
        LedManager::inputLeds[i] = Led(LED_INPUT_PIN[i], LED_INPUT_ANALOG);

    // Set up the output and status LEDs
    LedManager::outputLed = Led(LED_OUTPUT_PIN, LED_OUTPUT_ANALOG);
    LedManager::statusLed = Led(Led::STATUS_LED_PIN, Led::STATUS_LED_ANALOG);

    // Initialize the buttons
    ButtonManager::toggleButton = Button(BUTTON_TOGGLE_PIN);
    ButtonManager::shiftButton = Button(BUTTON_SHIFT_PIN);
}

void Core::setup() {
    // Initial startup delay
    delay(200);

    // Initialize the logger
    Log::init();

    // Randomize the random seed
    Random::randomize();

    // Set up the answer LED pins
    for(int i = 0; i < LED_INPUT_COUNT; i++)
        LedManager::inputLeds[i].setupPin();

    // Set up the output and status LEDs
    LedManager::outputLed.setupPin();
    LedManager::statusLed.setupPin();

    // Set up the toggle and shift button
    ButtonManager::toggleButton.setupPin();
    ButtonManager::shiftButton.setupPin();

    // Randomize the state of the input LEDs
    for(int i = 0; i < LED_INPUT_COUNT; i++)
        LedManager::inputLeds->setState(Random::nextBool());

    // The device has been started, update the flag
    this->started = true;
}

void Core::loop() {
    // Start the input mode if the shift button is pressed
    if(ButtonManager::shiftButton.isPressedOnce())
        startInputMode();

    // Handle the input mode logic, loop as long as this mode is enabled
    while(isInputMode()) {
        // TODO: Handle all input interaction here.

        // Update all logic
        updateLogic();
    }

    // Update everything
    updateLogic();
}

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
void Core::updateLogic() {
    // Update the screen LEDs
    for(short i = 0; i < LED_INPUT_COUNT; i++)
        LedManager::inputLeds[i].update();

    // Update the output and status LEDs
    LedManager::outputLed.update();
    LedManager::statusLed.update();

    // Update the toggle and shift button states
    ButtonManager::toggleButton.update();
    ButtonManager::shiftButton.update();

    // Update the memory manager
    MemoryManager::update();
}

/**
 * A smart delay method.
 * This method is similar to Arduino's delay method, but it keeps calling the update() method while the delay method is executed instead of freezing the Arduino.
 *
 * @param delay The delay in milliseconds to wait.
 */
void Core::smartDelay(int delay) {
    // Create a timer, to track the passed time
    Timer timer(delay);

    // Start the timer
    timer.start();

    // Call the update method until the timer has passed the specified delay
    while(!timer.isFinished())
        updateLogic();
}

bool Core::isInputMode() {
    return this->inputMode;
}

void Core::startInputMode() {
    // Set the input mode flag
    this->inputMode = true;

    // Reset the selected LED index
    LedManager::setSelectedLedIndex(0);
}

void Core::stopInputMode() {
    // Reset the input mode flag
    this->inputMode = false;
}