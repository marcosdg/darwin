/*  test_subset_sum.c

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
#include "experiment/subsetsum/subsetsum.h"


int main(int argc, char **argv)
{
    start_random_generator();

    int t = 4032;
    int s[4] = {120000, 80367, 110029, 4032};
    struct Subsetsum *subsetsum = create_subsetsum(t, s, 4);

    printf("==== SUBSET SUM INSTANCE ====\n");
    printf("Target: %i\n", t);
    printf("Set:\n");
    int i;
    for (i = 0; i < 4; i += 1) {
        printf("%i ", s[i]);
    }
    printf("\n");

    printf("==== CONFIGURATION ====\n");
    printf("Subset Sum individuals' encoding:\n");
    printf("  min. number of bits: %i\n", subsetsum->e->units_per_gene);
    printf("  number of genes: %i\n", subsetsum->e->num_genes);
    printf("  dna length: %i\n", subsetsum->e->dna_length);

    printf("Test individual:\n");
    struct Individual *test = create_random_individual(subsetsum->e);
    int locus;
    for (locus = 0; locus < subsetsum->e->dna_length; locus += 1) {
        printf("%li ", test->dna[locus]);
    }
    printf("\n");

    printf("==== DECODE ====\n");
    struct Subsetsum_candidate *candidate = (*subsetsum->decode)(test, subsetsum);
    (*subsetsum->print)(candidate);

    printf("==== EVALUATE ====\n");
    printf("Penalty: %i\n", (*subsetsum->penalty)(candidate));
    printf("Fitness: %lf\n", (*subsetsum->objective)(candidate));

    return 0;
}
