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
    Common random numbers utility functions.
*/
/*
    #includes

    <float.h> DBL_MIN
    <math.h> abs
    <stdlib.h> NULL, RAND_MAX
    <time.h> clock_gettime, CLOCK_REALTIME, rand, srand, timespec
    "report.h" <stdio.h>, <stdlib.h>
*/
#include <assert.h>
#include <float.h>
#include <math.h>
#include <time.h>
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
        DARWIN_ERROR("Could not generate seed correctly");
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
    assert(sequence_started == 1);
    assert(lower <= upper);

    long int width = abs(upper - lower);

    return lower + ((rand() * width) / RAND_MAX);
}
double
random_double_exclusive(
        double lower,
        double upper
) {
    assert(sequence_started == 1);
    assert(lower <= upper);

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
    assert(sequence_started == 1);
    assert(lower <= upper);

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
    assert(ints != NULL);
    assert(length > 0);

    int i;
    for (i = 0; i < length; i += 1) {
        ints[i] = random_int_inclusive(lower, upper);
    }
}
