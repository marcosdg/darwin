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
#include "experiment/subset_sum.h"


int main(int argc, char **argv)
{
    start_random_generator();

    int t = 3;
    int s[3] = {4, 1, 2};
    struct Subset_sum *subset_sum = create_subset_sum(t, s, 3);

    printf("==== SUBSET SUM INSTANCE ====\n");
    printf("Target: %i\n", t);
    printf("Set: ");
    int i;
    for (i = 0; i < 3; i += 1) {
        printf("%i ", s[i]);
    }
    printf("\n");

    printf("==== CONFIGURATION ====\n");
    
    printf("Subset Sum individuals' encoding:\n");
    printf("  min. number of bits: %i\n", subset_sum->e->units_per_gene);
    printf("  number of genes: %i\n", subset_sum->e->num_genes);
    printf("  dna length: %i\n", subset_sum->e->dna_length);
    
    printf("Test individual: ");
    struct Individual *test = create_random_individual(subset_sum->e);
    int locus;
    for (locus = 0; locus < subset_sum->e->dna_length; locus += 1) {
        printf("%li ", test->dna[locus]);
    }
    printf("\n");

    printf("==== DECODE ====\n");

    struct Candidate *candidate = (*subset_sum->decode)(test, subset_sum);
    printf("Subset size: %i\n", candidate->subset_size);
    for (i = 0; i < candidate->subset_size; i += 1) {
        printf("%i ", candidate->subset[i]);
    }
    printf("\n");

    printf("==== EVALUATE ====\n");
    printf("Penalty: %i\n", (*subset_sum->penalty)(candidate, subset_sum));
    printf("Fitness: %lf\n", (*subset_sum->objective)(candidate, subset_sum));
    
    return 0;
}
