/*
 * (Draft)
 * random.c
 * Marcos Díez García
 * 26-12-14
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

long int random_in_range(long int lower, long int upper)
{
        long int length;

        if (!sequence_started) {
                error_verbose(__FILE__, "random_in_range",
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

        above = random_in_range(banned + 1, upper);
        below = random_in_range(lower, banned - 1);
        
        if (banned == lower) {
                the_one = above;
        } else if (banned == upper) {
                the_one = below;
        } else if ((lower < banned) && (banned < upper)){
                the_one = random_in_range(0, 1)? below : above;
        }
        return the_one;
}

int randomize_ints(int *ints, long int lower, long int upper)
{
        int i = 0;

        if (!ints) {
                error_verbose(__FILE__, "random_in_range", "'ints' is NULL.");
        }
        while (ints[i] != '\0') {
               ints[i] = random_in_range(lower, upper);
               i += 1;
        }
}

