/*  test_parser_hampath.c

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
//#include <assert.h>
//#include <stdio.h>
#include <stdlib.h> /* free */
//#include <string.h>
/*
#include "experiment/nqueens/parser_nqueens.h"
#include "experiment/subsetsum/parser_subsetsum.h"
#include "experiment/hampath/parser_hampath.h"
*/
#include "experiment/parser_evolution.h"
#include "life.h"

//#define TEST(T, problem, ...)                                               \
//    struct T *problem;                                                      \
//    if (#problem == "nqueens") {                                            \
//        problem = create_nqueens(atoi(__VA_ARGS__));                        \
//    } else {                                                                \
//        problem = load_##problem(__VA_ARGS__);                              \
//    }                                                                       \
//    printf("problem->e->units_per_gene %i\n", problem->e->units_per_gene);  \
//    printf("INSTANCE->e->num_genes %i\n", problem->e->num_genes);           \
//    printf("INSTANCE->e->dna_length %i\n", problem->e->dna_length);         \
//                                                                            \
//    printf("Test individual:\n");                                           \
//    struct Individual *test = create_random_individual(problem->e);         \
//    int locus;                                                              \
//    for (locus = 0; locus < problem->e->dna_length; locus += 1) {           \
//        printf("%li ", test->dna[locus]);                                   \
//    }                                                                       \
//    printf("\n");                                                           \
//    printf("==== DECODE ====\n");                                           \
//    struct T##_candidate *candidate = (*problem->decode)(test, problem);    \
//    (*problem->print)(candidate);                                           \
//    printf("==== EVALUATE ====\n");                                         \
//    printf("Penalty: %i\n", (*problem->penalty)(candidate));                \
//    printf("Fitness: %lf\n", (*problem->objective)(candidate));
/*
#define DARWIN_DEFINE_LIVE(T, problem)                                          \
void                                                                            \
live(                                                                           \
        struct Evolution *evol,                                                 \
        char * problem##_file_name                                              \
) {                                                                             \
    assert(evol != NULL);                                                       \
    assert(problem##_file_name != NULL);                                        \
                                                                                \
    start_random_generator();                                                   \
                                                                                \
    struct T *problem = load_##problem(problem##_file_name);                    \
    struct Population *city = create_random_population(evol->population_size,   \
                                                        problem->e);            \
    struct T##_candidate *candidate;                                            \
    int i;                                                                      \
    for (i = 0; i < city->current_size; i += 1) {                               \
        printf("----------------------\n");                                     \
        printf("Individual %i\n", i);                                           \
        candidate = (*problem->decode)(city->people[i], problem);               \
        (*problem->print)(candidate);                                           \
        printf("Penalty: %i\n", (*problem->penalty)(candidate));                \
        printf("Fitness: %lf\n", (*problem->objective)(candidate));             \
        printf("----------------------\n");                                     \
    }                                                                           \
    exterminate(city);                                                          \
}
//destroy_##problem(problem);

#if !defined(DARWIN_USE_NQUEENS) && !defined(DARWIN_USE_SUBSETSUM) \
    && !defined(DARWIN_USE_HAMPATH)
#pragma message "Compiling darwin using NQueens (default)"
    DARWIN_DEFINE_LIVE(NQueens, nqueens)
#endif
#ifdef DARWIN_USE_NQUEENS
    DARWIN_DEFINE_LIVE(NQueens, nqueens)
#endif
#ifdef DARWIN_USE_SUBSETSUM
    DARWIN_DEFINE_LIVE(Subsetsum, subsetsum)
#endif
#ifdef DARWIN_USE_HAMPATH
    DARWIN_DEFINE_LIVE(Hampath, hampath)
#endif
*/

int main(int argc, char **argv)
{
    //TEST(NQueens, nqueens, argv[1]);

    struct Evolution *evol = load_evolution(argv[1]);
    live(evol, argv[2]);

    free(evol);
    /*
    start_random_generator();

    struct Abstract_problem *it = load_problem(argv);


    printf("Test individual:\n");
    struct Individual *test = create_random_individual(it->problem->e);
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
*/
    return 0;
}
