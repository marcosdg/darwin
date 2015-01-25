/*
  darwin. A simple genetic algorithm implementation with a
  self-adaptative strategy.

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
  (Draft)
  random.c
  Marcos Díez García
  02-01-15

  Routines to manipulate random numbers.

*/
#include "random.h"


static int sequence_started = 0;


void
initialize_random_sequence(void)
{
    struct timespec now;
    unsigned int seed;

    if (clock_gettime(CLOCK_REALTIME, &now) == -1) {
        ERROR_VERBOSE("Could not generate seed correctly");
    }
    seed = (unsigned int) (now.tv_sec * now.tv_nsec);
    srand(seed);
    sequence_started = 1;
}

long int
random_in_range_exclusive(long int lower,
                            long int upper)
{
    assert((lower <= upper) && (sequence_started == 1));

    long int width = abs(upper - lower);

    return lower + ((rand() * width) / RAND_MAX);
}

long int
random_in_range_inclusive(long int lower,
                            long int upper)
{
    return random_in_range_exclusive(lower, upper + 1);
}

long int
random_excluding(long int lower,
                    long int banned,
                    long int upper)
{
    assert((lower <= banned) && (banned <= upper));

    long int r;
    do {
        r = random_in_range_inclusive(lower, upper);
    } while (r == banned);

    return r;
}

int
randomize_ints(long int *ints,
                int length,
                long int lower,
                long int upper)
{
    assert((ints != NULL) && (length > 0));

    int i;
    for (i = 0; i < length; i += 1) {
        ints[i] = random_in_range_inclusive(lower, upper);
    }
    return 0;
}
