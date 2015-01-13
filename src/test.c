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
#include "operators.c"


void main(void)
{
    initialize_random_sequence();

    int i;
    int locus;
    struct Encoding *encoding = create_encoding(
            (long int []){0, 1}             /* nucleotides */,
            2                               /* nucleotides length */,
            6                               /* genes length */
    );
    
    struct Population *pop = create_random_population(
            encoding,
            3                               /* initial size */,
            10                              /* max size */
    );

    for (i = 0; i < pop->current_size; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");
        for (locus = 0; locus < 6; locus += 1) {
            printf("%li -- ", (pop->people[i])->genes[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
    /*

    //long int alphabet[] = {0, 1};
    struct population *pop = create_random_population(10, 10, 6, 2, alphabet);
    //struct population *pop = create_empty_population(4, 6, 2, alphabet);

    //struct individual *dad = create_individual(6);
    //struct individual *dad = create_random_individual(pop);

    printf("Population details:\n");
    printf("\t current size: %i\n", pop->current_size);
    printf("\t max size: %i\n", pop->max_size);
    printf("\t chromosome length: %i\n", pop->chromosome_length);

    for (i = 0; i < pop->current_size; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");
        for (locus = 0; locus < 6; locus += 1) {
            printf("%li--", (pop->people[i])->genes[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
*/
    /*
    int succeded = add_individual(pop, dad);

    if (succeded) {
        printf("\t Individual 0 info: \n");
        printf("\t\t genes: ");
        for (locus = 0; locus < 6; locus += 1) {
            printf("%li--", (pop->people[0])->genes[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
    */
    /*
    printf(" --- Randomize individual ---\n");

    initialize_random_sequence();
    randomize_individual(dad, pop);

    printf("\t\t genes: ");
    for (locus = 0; locus < 6; locus += 1) {
        printf("%li--", (pop->people[0])->genes[locus]);
    }
    printf("\n");

    */
/*
    for (i = 0; i < 4; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");
        for (locus = 0; locus < 6; locus += 1) {
            printf("%li--", (pop->people[i])->genes[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
*/

/*
	struct individual *dad = create_raw_individual(6);
	struct individual *mom = create_raw_individual(6);
	struct individual *son = create_raw_individual(6);
	struct individual *daughter = create_raw_individual(6);

	dad->genes[0] = 0;
	dad->genes[1] = 1;
	dad->genes[2] = 0;
	dad->genes[3] = 1;
	dad->genes[4] = 0;
	dad->genes[5] = 0;

	mom->genes[0] = 0;
	mom->genes[1] = 0;
	mom->genes[2] = 1;
	mom->genes[3] = 0;
	mom->genes[4] = 1;
	mom->genes[5] = 0;

    initialise_random_sequence();

    printf("======== TEST CROSSOVER ========\n");

    single_point_crossover(dad, mom, son, daughter);

	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("SON GENE %d: %d\n", i, son->genes[i]);
	}
	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("DAUGHTER GENE %d: %d\n", i, daughter->genes[i]);
	}

    printf("======== TEST MUTATION ========\n");

    single_point_mutation(son);

	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("SON GENE %d: %d\n", i, son->genes[i]);
	}
*/
}
