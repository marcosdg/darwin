/*  test_hampath.c

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
#include <stdlib.h>
#include "experiment/hampath/hampath.h"

int main(int argc, char **argv)
{
    start_random_generator();

    printf("==== HAMILTONIAN PATH INSTANCE ====\n");
    printf("Adjacency matrix: \n");
    int a[5][5] = { {0, 1, 1, 0, 0},
                    {1, 0, 0, 1, 1},
                    {1, 0, 0, 1, 0},
                    {0, 1, 1, 0, 1},
                    {0, 1, 0, 1, 0}};
    int **adjacency = malloc(5 * sizeof(int *));
    int i;
    int j;
    for (i = 0; i < 5; i += 1) {
        adjacency[i] = malloc(5 * sizeof(int));
    }
    for (i = 0; i < 5; i += 1) {
        for (j = 0; j < 5; j += 1) {
            adjacency[i][j] = a[i][j];
            printf("%i ", adjacency[i][j]);
        }
        printf("\n");
    }
    struct Graph *graph = create_graph(adjacency, 5);
    struct Hampath *hampath = create_hampath(graph);

    printf("==== CONFIGURATION ====\n");
    printf("Hamiltonian Path individuals' encoding:\n");
    printf("  min. number of bits: %i\n", hampath->e->units_per_gene);
    printf("  number of genes: %i\n", hampath->e->num_genes);
    printf("  dna length: %i\n", hampath->e->dna_length);

    printf("Test individual:\n");
    struct Individual *test = create_random_individual(hampath->e);
    int locus;
    for (locus = 0; locus < hampath->e->dna_length; locus += 1) {
        printf("%li ", test->dna[locus]);
    }
    printf("\n");

    printf("==== DECODE ====\n");
    struct Hampath_candidate *candidate = (*hampath->decode)(test, hampath);
    (*hampath->print)(candidate);

    printf("==== EVALUATE ====\n");
    printf("Penalty: %i\n", (*hampath->penalty)(candidate));
    printf("Fitness: %lf\n", (*hampath->objective)(candidate));

    return 0;
}
