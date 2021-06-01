/**
 * @file    random.h
 * @brief   Uniform random number generation.
 *
 * This file contains prototypes for functions which generate random unsigned
 * 32- and 64-bit integers, as well as signed 32-bit integers in a given range,
 * and random doubles in the range [0.0,1.0), or in a given range.
 *
 * @author  D. Trinchero (dario.trinchero@pm.me)
 * @date    2019-09-17
 */

#ifndef RANDOM_H
#define RANDOM_H

typedef unsigned long long int Ullong;

/**
 * Initializes the random number generator, seeding from /dev/urandom.
 */
void rnd_init(void);

/**
 * Resets the random number generator, starting from the given seed.
 *
 * @param[in]   seed
 *     seed which is used to begin random number generation
 */
void rnd_seed(Ullong seed);

/**
 * Generates a uniformly-distributed 64-bit unsigned integer.
 *
 * @return      the random 64-bit unsigned integer
 */
Ullong rnd_uint64(void);

/**
 * Generates a uniformly-distributed 32-bit unsigned integer.
 *
 * @return      the random 32-bit unsigned integer
 */
unsigned int rnd_uint32(void);

/**
 * Generates a uniformly-distributed 32-bit signed integer in the range [a,b).
 *
 * @param[in]   a
 *     the lower bound for the random integer (included)
 * @param[in]   b
 *     the upper bound for the random integer (excluded)
 * @return      the random 32-bit signed integer in the range [a,b)
 */
signed int rnd_int32(int a, int b);

/**
 * Generates a uniformly-distributed double in the range [0.0,1.0).
 *
 * @return      the random double in the range [0.0,1.0)
 */
double rnd_udbl(void);

/**
 * Generates a uniformly-distributed double in the range [a,b).
 *
 * @param[in]   a
 *     the lower bound for the random double (included)
 * @param[in]   b
 *     the upper bound for the random double (excluded)
 * @return      the random double in the range [a,b)
 */
double rnd_dbl(double a, double b);

#endif /* RANDOM_H */
