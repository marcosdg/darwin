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
#include "operators.h"


int main(int argc, char **argv)
{

    start_random_generator();

    int i;
    int locus;
    struct Encoding *e = create_encoding(
            1                               /* units per gene */,
            6                               /* number of genes */
    );

    struct Population *pop = create_random_population(
            e,
            4                               /* size */
    );
    struct Individual *dad = pop->people[0];
    struct Individual *mom = pop->people[1];
    struct Individual *ind3 = pop->people[2];
    struct Individual *ind4 = pop->people[3];
    dad->fitness = 0.57;
    mom->fitness = 0.30;
    ind3->fitness = 0.75;
    ind4->fitness = 0.70;

    for (i = 0; i < pop->current_size; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");

        for (locus = 0; locus < (e->dna_length); locus += 1) {
            printf("%li -- ", (pop->people[i])->dna[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
/*
    printf("======== TEST TOURNAMENT SELECTION ========\n");

    dad->fitness = 0.50;
    mom->fitness = 0.60;
    ind3->fitness = 0.75;
    ind4->fitness = 0.70;

    for (i = 0; i < pop->current_size; i += 1) {
        printf("Individual %i fitness: %lf \n", i, (pop->people[i])->fitness);
    }
    struct Individual *best = tournament_selection(pop, 1);
    printf("Best individual fitness: %lf \n", best->fitness);

    printf("======== TEST CROSSOVER ========\n");

    struct Individual **offspring = single_point_crossover(dad, mom, e);
    struct Individual *son = offspring[0];
    struct Individual *daughter = offspring[1];

    printf("SON DNA:\n");
    for (i = 0; i < (e->dna_length); i += 1) {
		printf("%li -- ", son->dna[i]);
	}
    printf("\n");
    printf("DAUGHTER DNA:\n");
    for (i = 0; i < (e->dna_length); i += 1) {
		printf("%li -- ", daughter->dna[i]);
	}
    printf("\n");

    printf("======== TEST MUTATION ========\n");

    single_point_mutation(son, e);

    printf("SON DNA:\n");
	for (i = 0; i < (e->dna_length); i += 1) {
		printf("%li -- ", son->dna[i]);
	}
    printf("\n");
*/
    printf("======== TEST REPLACEMENT  ========\n");
    
    printf("DIVERSITY CONTRIBUTION\n");

    int dadd = diversity_contribution(dad, pop, e);
    int momd = diversity_contribution(mom, pop, e);
    printf(" diversity contribution DAD: %d\n", dadd);
    printf(" diversity contribution MOM: %d\n", momd);
     
    printf("REPLACE WORST\n");

    struct Individual *new = create_random_individual(e);
    new->fitness = 0.55;

    replace_worst(new, pop);

    for (i = 0; i < pop->current_size; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");

        for (locus = 0; locus < (e->dna_length); locus += 1) {
            printf("%li -- ", (pop->people[i])->dna[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (pop->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (pop->people[i])->evolvability);
    }
    return 0;
}
