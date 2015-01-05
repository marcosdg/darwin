/*
 * darwin. A simple genetic algorithm implementation with a
 * self-adaptative strategy.
 *
 * Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */
/*
 * (Draft)
 * random.c
 * Marcos Díez García
 * 02-01-15 
 *
 * Routines to manipulate random numbers
 *
 * */
#include <math.h>
#include <time.h>
#include "utils.c"

static sequence_started = 0;


void initialise_random_sequence()
{
        srand((unsigned int) time(NULL));
        sequence_started = 1;
}

long int random_in_range_exclusive(long int lower, long int upper)
{
        long int length;

        if (!sequence_started) {
                error_verbose(__FILE__, "random_in_range_exclusive",
                              "Random sequence not started.");
        }
        length = abs(upper - lower);
	return lower + ((rand() * length) / RAND_MAX);
}

long int random_in_range_inclusive(long int lower, long int upper)
{
        long int length;

        if (!sequence_started) {
                error_verbose(__FILE__, "random_in_range_inclusive",
                              "Random sequence not started.");
        }
        length = abs((upper + 1) - lower);
	return lower + ((rand() * length) / RAND_MAX);
}
long int random_excluding(long int lower, long int banned, long int upper)
{
        long int above,
                 below,
                 the_one;
        
        if (!sequence_started) {
                error_verbose(__FILE__, "random_in_range",
                              "Random sequence not started");
        }
        if (banned < lower || upper < banned) {
                error_verbose(__FILE__, "random_in_range",
                              "'banned' out of range.");
        }

        above = random_in_range_inclusive(banned + 1, upper);
        below = random_in_range_inclusive(lower, banned - 1);
        
        if (banned == lower) {
                the_one = above;
        } else if (banned == upper) {
                the_one = below;
        } else if ((lower < banned) && (banned < upper)){
                the_one = random_in_range_inclusive(0, 1)? below : above;
        }
        return the_one;
}

int randomize_ints(int *ints, long int lower, long int upper)
{
        int i = 0;

        if (!ints) {
                error_verbose(__FILE__, "random_in_range", 
                              "'ints' is NULL.");
        }
        while (ints[i] != '\0') {
               ints[i] = random_in_range_inclusive(lower, upper);
               i += 1;
        }
}

