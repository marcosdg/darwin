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
  test.c
  Marcos Díez García
  26-12-14

  Just to play around.

*/
#include "random.h"


static double NUM_RUNS = 1000;

int main(int argc, char **argv)
{
	int i;
    long int r;
    long int ints[] = {1, 1, 1, 0, 0, 0};
    double zeroes = 0.0,
           ones = 0.0,
           twos = 0.0,
           threes = 0.0,
           fours = 0.0;

    initialize_random_sequence();
/*
    printf("======== TEST RANDOM_IN_RANGE_EXCLUSIVE ========\n");

    for (i = 0; i < NUM_RUNS; i += 1) {
        r = random_in_range_exclusive(0,5);
        switch(r) {
        case 0:
            zeroes += 1.0;
            break;
        case 1:
            ones += 1.0;
            break;
        case 2:
            twos += 1.0;
            break;
        case 3:
            threes += 1.0;
            break;
        case 4:
            fours += 1.0;
            break;
        }
    }
    printf("\t\t Distribution \n");
    printf("Zeroes: %f \n", zeroes / NUM_RUNS);
    printf("Ones: %f \n", ones / NUM_RUNS);
    printf("Twos: %f \n", twos / NUM_RUNS);
    printf("Threes: %f \n", threes / NUM_RUNS);
    printf("Fours: %f \n", fours / NUM_RUNS);
*/
/*
    printf("======== TEST RANDOM_IN_RANGE_INCLUSIVE ========\n");

    zeroes = 0.0;
    ones = 0.0;

    for (i = 0; i < NUM_RUNS; i += 1) {
        r = random_in_range_inclusive(0, 1);
        switch(r) {
        case 0:
            zeroes += 1.0;
            break;
        case 1:
            ones += 1.0;
            break;
        }
    }
    printf("\t\t Distribution \n");
    printf("Zeroes: %f \n", zeroes / NUM_RUNS);
    printf("Ones: %f \n", ones / NUM_RUNS);
*/
/*
    printf("======== TEST RANDOM_EXCLUDING ========\n");

    zeroes = 0.0,
    ones = 0.0,
    twos = 0.0,
    threes = 0.0,
    fours = 0.0;

    for (i = 0; i < NUM_RUNS; i += 1) {
        r = random_excluding(0, 3, 4);
        switch(r) {
        case 0:
            zeroes += 1.0;
            break;
        case 1:
            ones += 1.0;
            break;
        case 2:
            twos += 1.0;
            break;
        case 3:
            threes += 1.0;
            break;
        case 4:
            fours += 1.0;
            break;
        }
    }
    printf("\t\t Distribution \n");
    printf("Zeroes: %f \n", zeroes / NUM_RUNS);
    printf("Ones: %f \n", ones / NUM_RUNS);
    printf("Twos: %f \n", twos / NUM_RUNS);
    printf("Threes: %f \n", threes / NUM_RUNS);
    printf("Fours: %f \n", fours / NUM_RUNS);
*/
    printf("======== TEST RANDOMIZE_INTS ========\n");

    randomize_ints(ints, 6, 0, 4);

    for (i = 0; i < 6; i += 1) {
        printf("%li \n", ints[i]);
    }
    return 0;
}

