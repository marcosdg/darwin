/*  random.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a self-adaptative
    strategy.

    Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*
    random.{h,c} implement routines to handle random numbers.
*/
#include <assert.h>
#include <float.h>  /* DBL_MIN */
#include <math.h>   /* abs */
#include <stdio.h>  /* printf */
#include <stdlib.h> /* RAND_MAX */
#include <time.h>   /* clock_gettime, CLOCK_REALTIME, rand, srand, timespec */
#include "report.h"
#include "random.h"

static int sequence_started = 0;


void
start_random_generator(
        void
) {
    struct timespec now;
    unsigned int seed;

    if (clock_gettime(CLOCK_REALTIME, &now) == -1) {
        error("Could not generate seed correctly");
    }
    seed = (unsigned int) (now.tv_sec * now.tv_nsec);
    srand(seed);
    sequence_started = 1;
}

long int
random_int_exclusive(
        long int lower,
        long int upper
) {
    assert((lower <= upper) && (sequence_started == 1));

    long int width = abs(upper - lower);

    return lower + ((rand() * width) / RAND_MAX);
}
double
random_double_exclusive(
        double lower,
        double upper
) {
    assert((lower <= upper) && (sequence_started == 1));

    double width = upper - lower;

    return lower + ((rand() * width) / RAND_MAX);
}
long int
random_int_inclusive(
        long int lower,
        long int upper
) {
    return random_int_exclusive(lower, upper + 1);
}
double
random_double_inclusive(
        double lower,
        double upper
) {
    assert((lower <= upper) && (sequence_started == 1));

    return random_double_exclusive(lower, upper + DBL_MIN);
}

long int
random_excluding(
        long int lower,
        long int banned,
        long int upper
) {
    assert((lower <= banned) && (banned <= upper));

    long int r;
    do {
        r = random_int_inclusive(lower, upper);
    } while (r == banned);

    return r;
}

void
randomize_ints(
        long int *ints,
        int length,
        long int lower,
        long int upper
) {
    assert((ints != NULL) && (length > 0));

    int i;
    for (i = 0; i < length; i += 1) {
        ints[i] = random_int_inclusive(lower, upper);
    }
}
void
randomize_bins(
        long int *bins,
        int length
) {
    randomize_ints(bins, length, 0, 1);
}
