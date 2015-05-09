/*  test_operators.c

    This is part of the darwin program.

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
    Just to play around.
*/
#include <stdio.h>
#include "base/report.h"
#include "base/random.h"
#include "genome.h"
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

    struct Population *city = create_random_population(
            4                               /* size */,
            e
    );

    struct Individual *ind1 = city->people[0];
    struct Individual *ind2 = city->people[1];
    struct Individual *ind3 = city->people[2];
    struct Individual *ind4 = city->people[3];
    ind1->fitness = 0.57;
    ind2->fitness = 0.30;
    ind3->fitness = 0.75;
    ind4->fitness = 0.70;

    for (i = 0; i < city->current_size; i += 1) {
        printf("\t Individual %i info: \n", i);
        printf("\t\t genes: ");

        for (locus = 0; locus < (e->dna_length); locus += 1) {
            printf("%li -- ", (city->people[i])->dna[locus]);
        }
        printf("\n");
        printf("\t\t fitness: %lf \n", (city->people[i])->fitness);
        printf("\t\t evolvability: %lf \n", (city->people[i])->evolvability);
    }
    printf("======== TEST TOURNAMENT SELECTION ========\n");

    double times_ind1 = 0;
    double times_ind2 = 0;
    double times_ind3 = 0;
    double times_ind4 = 0;

    int trial;
    for (trial = 0; trial < 10000; trial += 1) {
        struct Individual *best = tournament_selection(city, 1);
        if (best->fitness == 0.57) {
            times_ind1 += 1.0;
        } else if (best->fitness == 0.30) {
            times_ind2 += 1.0;
        } else if (best->fitness == 0.75) {
            times_ind3 += 1.0;
        } else /* best finess == 0.70 */ {
            times_ind4 += 1.0;
        }
    }
    printf("%% times ind1 (0.57) wins: %lf\n", times_ind1 / 10000);
    printf("%% times ind2 (0.30) wins: %lf\n", times_ind2 / 10000);
    printf("%% times ind3 (0.75) wins: %lf\n", times_ind3 / 10000);
    printf("%% times ind4 (0.70) wins: %lf\n", times_ind4 / 10000);

/*
    printf("======== TEST CROSSOVER ========\n");

    struct Individual **offspring = single_point_crossover(ind1, ind2, e);
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
*/
/*
    printf("======== TEST MUTATION ========\n");

    ind1->evolvability = ind1->fitness
                            / ((ind2->fitness + ind3->fitness) * 0.5);

    double risk1 = adaptative_mutation_risk(ind1);

    printf("evolvability ind1 = %lf \n", ind1->evolvability);
    printf("risk ind1 = %lf \n", risk1);

    double mutations;
    int mutated;
    for (i = 0; i < 100000; i += 1) {
        mutated = mutagen(adaptative_mutation_risk, ind1, e);
        if (mutated) {
            mutations += 1.0;
        }
    }
    printf("%% mutations =  %lf (should be close to the risk factor)\n",
            mutations / 100000.0);
*/
/*
    printf("======== TEST REPLACEMENT  ========\n");

    struct Individual *new = create_random_individual(e);
    new->fitness = 0.40;

    int replaced = replace_worst(new, city);
    if (replaced) {
        for (i = 0; i < city->current_size; i += 1) {
            printf("\t Individual %i info: \n", i);
            printf("\t\t genes: ");

            for (locus = 0; locus < (e->dna_length); locus += 1) {
                printf("%li -- ", (city->people[i])->dna[locus]);
            }
            printf("\n");
            printf("\t\t fitness: %lf \n", (city->people[i])->fitness);
            printf("\t\t evolvability: %lf \n", (city->people[i])->evolvability);
        }
    }
*/
    return 0;
}
