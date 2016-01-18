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
    // Define the new seed variable
    unsigned int seed = 1;

    // Create a semi-random number to use as seed
    for(int i = 0; i < 6; i++)
        seed *= analogRead((uint8_t) i);

    // Set the actual seed
    setSeed(seed);
}

void Random::setSeed(unsigned int seed) {
    // Set the seed in the Arduino library
    randomSeed(seed);
}

unsigned int Random::nextIntWithoutSeed() {
    // Define the base number
    unsigned int num = 1;

    // Semi-randomize the defined number using analog reads
    for(int i = 0; i < 6; i++)
        num *= analogRead((uint8_t) i);

    // Return the random value
    return num;
}