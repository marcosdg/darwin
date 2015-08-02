/*  random.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
    strategy.

    Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>

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
    #included

    <float.h> DBL_MIN
    <stdlib.h> NULL, RAND_MAX
    <time.h> clock_gettime, CLOCK_REALTIME, rand, srand, timespec
    "report.h" <stdio.h>, <stdlib.h>
*/
#ifdef HAVE_CONFIG_H
    #include "../../config.h"
#endif /* HAVE_CONFIG_H */

#include <assert.h>
#include <float.h>
#if defined HAVE_CLOCK_GETTIME
    #include <time.h>
#else
    #include <sys/time.h>
#endif
#include "report.h"
#include "random.h"

static int sequence_started = 0;

void
init_random_generator(
        void
) {
    unsigned int seed;
    int failure = 0;
#if defined HAVE_CLOCK_GETTIME
    struct timespec then;
    failure = clock_gettime(CLOCK_REALTIME, &then);
#else
    struct timeval now;
    failure = gettimeofday(&now, NULL);
#endif
    if (failure) {
        DARWIN_ERROR("Could not generate seed correctly");
    }
#if defined HAVE_CLOCK_GETTIME
    seed = (unsigned int) (then.tv_sec * then.tv_nsec);
#else
    seed = (unsigned int) (now.tv_sec * now.tv_usec);
#endif
    srand(seed);
    sequence_started = 1;
}

long int
random_int_exclusive(
        long int lower,
        long int upper
) {
    assert(lower <= upper);
    assert(sequence_started);

    long int width = upper - lower;

    return lower + ((rand() * width) / RAND_MAX);
}
double
random_double_exclusive(
        double lower,
        double upper
) {
    assert(lower <= upper);
    assert(sequence_started);

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
    return random_double_exclusive(lower, upper + DBL_MIN);
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
