/*  test_nqueens.c

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
#include "experiment/nqueens.h"


int main(int argc, char **argv)
{
    start_random_generator();

    struct NQueens *nqueens = create_nqueens(5);
    
    printf("==== CONFIGURATION ====\n");
    printf("5-Queens individuals' encoding:\n");
    printf("  min. number of bits: %i\n", nqueens->e->units_per_gene);
    printf("  number of genes: %i\n", nqueens->e->num_genes);
    printf("  dna length: %i\n", nqueens->e->dna_length);
    /*
        Sample:

               0  1  2  3  4  5  6  7 COLUMNS
             -------------------------
            0| Q|  |  |  |  | X| X| X|
            1|  |  | Q|  |  | X| X| X|
            2|  |  |  |  |  | X|XQ| X|
            3|  | Q|  |  |  | X| X| X|
            4|  |  |  | Q|  | X| X| X|
        ROWS -------------------------

        Q: Queen, X: illegal board positions(alleles), XQ: illegal queen
    */
    printf("Test individual:\n");
    struct Individual *test = create_individual(nqueens->e);
    long int test_dna[15] = {0,0,0, 0,1,0, 1,1,0, 0,0,1, 0,1,1};
    int locus;
    for (locus = 0; locus < nqueens->e->dna_length; locus += 1) {
        test->dna[locus] = test_dna[locus];
        printf("%li ", test->dna[locus]);
    }
    printf("\n");
    
    printf("==== DECODE ====\n");
    struct NQueens_candidate *candidate = (*nqueens->decode)(test, nqueens);
    (*nqueens->print)(candidate);

    printf("==== EVALUATE ====\n");
    printf("Penalty: %i\n", (*nqueens->penalty)(candidate));
    printf("Fitness: %lf\n", (*nqueens->objective)(candidate));

    kill(test, nqueens->e);

    return 0;
}
