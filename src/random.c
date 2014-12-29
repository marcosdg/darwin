/*
 * (Draft)
 * random.c
 * Marcos Díez García
 * 26-12-14
 *
 * Routines to manipulate random numbers
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

static sequence_started = 0;

void initialise_random_sequence()
{
        srandom((unsigned int) time(NULL));
        sequence_started = 1;
}

long int random_in_range(long int lower, long int upper)
{
        if (!sequence_started) {
                goto exit;
        }
	long int length = abs((upper + 1) - lower);
	
	return lower + ((random() * length) / RAND_MAX);

exit:
        printf("ERROR random_in_range: Random sequence not started.\n");
        return -1;
}

long int random_excluding(long int lower, long int banned, long int upper)
{
        long int above,
                 below,
                 the_one;
        
        if (!sequence_started) {
                goto exit;
        }
        if (banned < lower || upper < banned) {
                goto out_of_range;
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

exit:
        printf("ERROR random_in_range: Random sequence not started.\n");
        return -1;

out_of_range:
        printf("ERROR random_in_range: 'banned' is out of range.\n");
        return -1;
}


int randomize(int *integers, long int lower, long int upper)
{
        int i = 0;

        while (integers[i] != '\0') {
               integers[i] = random_in_range(lower, upper);
               i += 1;
        }
}
