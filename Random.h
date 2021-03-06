/**
 * HhsArduinoCircuitAdvanced.
 * An Arduino challenge for HHS by Tim Visee.
 *
 * @author Tim Visee
 * @website http://timvisee.com/
 */

#ifndef HHSARDUINOCIRCUITADVANCED_RANDOM_H
#define HHSARDUINOCIRCUITADVANCED_RANDOM_H

#include <Arduino.h>

/**
 * Random class.
 * A class to generate random numbers.
 */
class Random {
public:
    /**
     * Get a random number, from zero to the specified maximum number. The maximum number is excluded.
     *
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int max);

    /**
     * Get a random number, from the specified minimum number to the specified maximum number.
     * The maximum number is excluded.
     *
     * @param min Minimum number (included).
     * @param max Maximum number (excluded).
     *
     * @return A random number.
     */
    static int nextInt(int min, int max);

    /**
     * Get a random boolean.
     *
     * @return A random boolean.
     */
    static bool nextBool();

    /**
     * Randomize the current random seed.
     */
    static void randomize();

    /**
     * Set the current random seed.
     */
    static void setSeed(unsigned int seed);

    /**
     * Get a random number, that isn't based of a seed. The main random instance isn't used to generate this number.
     * This can be used to properly seed the current random instance with a number that is as random as possible.
     *
     * The returned value is 1 or greater.
     * The limit of the returned number isn't specified, and can differ greatly over time.
     *
     * @return A random number.
     */
    static unsigned int nextIntWithoutSeed();
};

#endif //HHSARDUINOCIRCUITADVANCED_RANDOM_H
