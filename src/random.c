/**
 * @file    random.c
 * @brief   Implementations of uniform random number generation.
 *
 * Some functions were adapted from "Numerical Recipes: The Art of Scientific
 * Computing" by William H. Press, Saul A. Teukolsky, William T. Vetterling, and
 * Brian P. Flannery, and are copyright (C) 1988 Cambridge University Press.
 *
 * @author  D. Trinchero (dario.trinchero@pm.me)
 * @date    2019-09-17
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "random.h"

/* --- global variables ----------------------------------------------------- */

static Ullong u, v, w;

/* --- initialization routines ---------------------------------------------- */

void rnd_init(void)
{
	int fd;
	Ullong seed;

	if ((fd = open("/dev/urandom", O_RDONLY)) < 0) {
		printf("cannot read random data from /dev/urandom");
		exit(2);
	}
	if (read(fd, &seed, sizeof(Ullong)) < (ssize_t) sizeof(Ullong)) {
		close(fd);
		printf("cannot read random data from /dev/urandom");
		exit(2);
	}

	close(fd);

	rnd_seed(seed);
}

void rnd_seed(Ullong seed)
{
	w = 1; v = 4101842887655102017LL;
	u = seed ^ v; rnd_uint64();
	v = u; rnd_uint64();
	w = v; rnd_uint64();
}

/* --- number generation routines ------------------------------------------- */

Ullong rnd_uint64(void)
{
	u = u * 2862933555777941757LL + 7046029254386353087LL;
	v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
	w = 4294957665U * (w & 0xffffffff) + (w >> 32);
	Ullong x = u ^ (u << 21); x ^= x >> 35; x ^= x << 4;
	return (x + v) ^ w;
}

unsigned int rnd_uint32(void)
{
	return (unsigned int) rnd_uint64();
}

signed int rnd_int32(int a, int b)
{
	unsigned int i, limit = b - a;
	do { /* avoid modulo bias */
		i = rnd_uint32();
	} while(i < (-limit % limit)); /* i < (2**size % limit) */

	return (i % limit) + a;
}

double rnd_udbl(void)
{
	return 5.42101086242752217E-20 * rnd_uint64();
}

double rnd_dbl(double a, double b)
{
	return rnd_udbl() * (b - a) + a;
}
