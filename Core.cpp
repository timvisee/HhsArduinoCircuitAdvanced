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

Core::Core() {
    // Set the started flag
    this->started = false;

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

    // The device has been started, update the flag
    this->started = true;
}

void Core::loop() {
    // Show the slide animation before showing the number
    playSlideAnimation();
    smartDelay(400);

    // Reset the game number
    gameNumber = 0;

    // Generate a random number if this is the master when playing multiplayer
    if(!ConnectionManager::isMultiplayer() || ConnectionManager::isMaster())
        gameNumber = generateNewGameNumber();

    // Send the number to the other client when playing multiplayer
    if(ConnectionManager::isMultiplayer() && ConnectionManager::isMaster()) {
        // Create a packet to send the game start in
        Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_START);

        // Create an array with the game number, add it to the packet
        int *intArr = new int[1];
        intArr[0] = (int) gameNumber;
        connectPacket.setIntegers(intArr, 1);

        // Send the packet
        PacketHandler::sendPacket(connectPacket);

        // Destroy the packet afterwards
        connectPacket.destroy();
    }

    // Wait for a number to be received if this is the slave
    if(ConnectionManager::isMultiplayer() && !ConnectionManager::isMaster()) {
        // Wait for a number, and update in the meanwhile
        while(!ConnectionManager::hasGameNumber())
            updateLogic();

        // Get the number
        gameNumber = ConnectionManager::getGameNumber();
        ConnectionManager::resetGameNumber();
    }

    // Show the number as binary for the specified duration
    showNumber(gameNumber);
    smartDelay(ANSWER_VISIBLE_DURATION);
    showNumber(0);

    // Start a stopwatch to measure the time the user takes to input
//    Stopwatch inputStopwatch = Stopwatch(true);

    // Start the timer
    Timer timer(INPUT_TIMEOUT);
    timer.start();

    // Define a variable to store the number in the user has entered
    uint8_t userAnswer = 0;

    // Use a while loop to handle the button presses
    while(!timer.isFinished() || userAnswer <= 0) {
        // TODO: Remove this, or change it to use a different LED? (because the green and red don't support analog anymore)
        // Pulse the green light
        if(!LedManager::greenLed.isFading()) {
            // Fade the lights in or out
            if(LedManager::greenLed.getBrightness() <= PULSE_BRIGHTNESS_LOW) {
                LedManager::greenLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);

                // Only fade red out if it is currently on
                if(LedManager::redLed.getBrightness() != Led::BRIGHTNESS_LOW)
                    LedManager::redLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);

            } else if(LedManager::greenLed.getBrightness() >= PULSE_BRIGHTNESS_HIGH) {
                LedManager::greenLed.fade(PULSE_BRIGHTNESS_LOW, PULSE_DURATION);
                LedManager::redLed.fade(PULSE_BRIGHTNESS_HIGH, PULSE_DURATION);
            }
        }

        // Update everything
        updateLogic();

        // Handle button presses
        if(ButtonManager::button.isPressedOnce()) {
            // Increase the answer
            userAnswer++;

            // Reset the answer
            timer.start();

            // Show some feedback, a button is pressed
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].fade(FEEDBACK_BRIGHTNESS_HIGH, FEEDBACK_VISIBLE_DURATION);
            smartDelay(FEEDBACK_VISIBLE_DURATION);
            for(int i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].fade(FEEDBACK_BRIGHTNESS_LOW, FEEDBACK_VISIBLE_DURATION);
        }
    }

    // Measure the input duration
//    long userInputDuration = inputStopwatch.getTime();

    // Stop the timer
    timer.stop();

    // Turn off the pulsing LEDs
    LedManager::greenLed.setState(false);
    LedManager::redLed.setState(false);

    // Clear the current results
    ConnectionManager::clearResult();

    // Do some extra stuff if playing multiplayer
    if(ConnectionManager::isMultiplayer()) {
        // As a slave, send the result to the master.
        if(!ConnectionManager::isMaster()) {
            // Create the packet
            Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_ANSWER);

            // Create an array with the answer, add it to the packet
            int *intArr = new int[1];
            intArr[0] = (int) userAnswer;
            connectPacket.setIntegers(intArr, 1);

            // Create an array with input duration, add it to the packet
//            String *strArr = new String[1];
//            strArr[0] = String(userInputDuration);
//            connectPacket.setStrings(strArr, 1);

            // Send the packet
            PacketHandler::sendPacket(connectPacket);

            // Destroy the packet afterwards
            connectPacket.destroy();

            // Wait for the results to be send, update in the meanwhile
            while(!ConnectionManager::hasReceivedResult())
                updateLogic();

        } else {
            // As master, wait for the result to be received, update in the meanwhile
            while(!ConnectionManager::hasOtherInputAnswer())
                updateLogic();

            // Store the values, reset them afterwards
            uint8_t otherUserInputAnswer = ConnectionManager::getOtherInputAnswer();
//            long otherUserInputDuration = ConnectionManager::getOtherInputDuration();
            ConnectionManager::resetOtherInputAnswer();
            ConnectionManager::resetOtherInputDuration();

            // Determine which player wins
            bool masterWin = (userAnswer == gameNumber);
            bool slaveWin = (otherUserInputAnswer == gameNumber);

            // If both players are correct, choose the fastest
//            if(masterWin && slaveWin) {
//                masterWin = (userInputDuration >= otherUserInputDuration);
//                slaveWin = (userInputDuration < otherUserInputDuration);
//            }

            // Create the packet
            Packet connectPacket = Packet(1, Protocol::PACKET_TYPE_GAME_RESULTS);

            // Create an array with the answer, add it to the packet
            int *intArr = new int[2];
            intArr[0] = (int) userAnswer;
            intArr[1] = (int) otherUserInputAnswer;
            connectPacket.setIntegers(intArr, 2);

            // Create an array with the answer, add it to the packet
            bool *boolArr = new bool[2];
            intArr[0] = (bool) masterWin;
            intArr[1] = (bool) slaveWin;
            connectPacket.setBooleans(boolArr, 2);

            // Create an array with input duration, add it to the packet
//            String *strArr = new String[2];
//            strArr[0] = String(userInputDuration);
//            strArr[1] = String(otherUserInputDuration);
//            connectPacket.setStrings(strArr, 2);

            // Send the packet
            PacketHandler::sendPacket(connectPacket);

            // Destroy the packet afterwards
            connectPacket.destroy();

            // Store the answers for this device
            ConnectionManager::setResult(masterWin, userAnswer, otherUserInputAnswer);
        }
    }

    // Wait a second before showing the input
    smartDelay(500);

    // Show the result the user has entered
    showNumber(userAnswer);
    smartDelay(USER_INPUT_VISIBLE_DURATION);
    showNumber(0);

    // Wait a second before showing the input
    smartDelay(1000);

    // Determine whether the user has won
    bool hasWon = (userAnswer == gameNumber);
    if(ConnectionManager::isMultiplayer())
        hasWon = ConnectionManager::hasWonGame();

    // FIXME: Minor tweak, in case the result breaks in packet transfer
    if(ConnectionManager::isMultiplayer())
        hasWon = (userAnswer == gameNumber);

    // Show the result
    if(hasWon) {
        // Turn on the green LED if available
        LedManager::greenLed.setState(true);
        smartDelay(250);

        // Animate the screen
        for(uint8_t j = 0; j < 3; j++) {
            for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].setState(true);
            smartDelay(250);
            for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
                LedManager::screenLeds[i].setState(false);
            smartDelay(250);
        }

        // Turn off the green LED
        smartDelay(250);
        LedManager::greenLed.setState(false);

    } else {
        // Turn on the red LED if available
        LedManager::redLed.setState(true);
        smartDelay(250);

        // Animate the screen
        for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
            LedManager::screenLeds[i].fade(80, 500);
        smartDelay(500);
        for(uint8_t i = 0; i < SCREEN_LED_COUNT; i++)
            LedManager::screenLeds[i].fade(0, 1000);
        smartDelay(1000);

        // Turn off the red LED
        smartDelay(250);
        LedManager::redLed.setState(false);
    }

    // Wait a little for the slave to catch up
    smartDelay(250);
}

/**
 * Update method, should be called often to update things like the animation controllers of the LEDs.
 */
void Core::updateLogic() {
    // Update the screen LEDs
    for(short i = 0; i < SCREEN_LED_COUNT; i++)
        LedManager::screenLeds[i].update();

    // Update the green and red LED
    LedManager::greenLed.update();
    LedManager::redLed.update();

    // Update the button state
    ButtonManager::button.update();

    // Update the memory manager
    MemoryManager::update();

    // Only update the following if the device is started
    if(!this->started)
        return;

    // Handle received data from the multiplayer connection
    // TODO: Only if multiplayer is enabled?
    while(con.available()) {
        // Enable the activity light
        LedManager::statusLed.setState(true);

        // Handle the new data
        while(con.available())
            PacketHandler::receive((char) con.read());

        // Disable the activity light
        LedManager::statusLed.setState(false);
    }
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
