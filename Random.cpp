/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#include "Random.h"

int Random::nextInt(int max) {
    return nextInt(0, max);
}

int Random::nextInt(int min, int max) {
    return (int) random((long) min, (long) max);
}

void Random::randomize() {
    setSeed(Random::nextIntWithoutSeed());
}

void Random::setSeed(unsigned int seed) {
    // Set the seed in the Arduino library
    randomSeed(seed);
}

unsigned int Random::nextIntWithoutSeed() {
    // Determine a base number, based on the number of milliseconds the Arduino has run
    unsigned int num = (unsigned int) (millis() % 9999);

    // Semi-randomize the defined number using analog reads
    for(int i = 0; i < 6; i++)
        num *= analogRead((uint8_t) i);

    // Return the random value
    return num;
}