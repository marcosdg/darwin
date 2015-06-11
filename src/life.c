/*  life.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a self-adaptative
    strategy.

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
    This is darwin's third level of abstraction where the genetic algorithm is
    defined using the genetic operators (see src/operators.h) and the basic
    structures (see src/genome.h, src/experiment/hampath/hampath.h,
    src/experiment/nqueens/nqueens.h, src/experiment/nqueens/nqueens.c)

    It relies on 'life-generic-defs.h' to decide the appropriate macro invocation,
    for the functions defined here, according to which problem the user chose.
*/
#include <assert.h>
#include <stdio.h>      /* NULL */
#include <string.h>     /* memset */
#include "base/xmem.h"  /* xmalloc */
#include "experiment/hampath/parser_hampath.h"
#include "experiment/nqueens/parser_nqueens.h"
#include "experiment/subsetsum/parser_subsetsum.h"
#include "experiment/parser_evolution.h"
#include "life.h"


struct Evolution *
genesis(
        void
) {
    struct Evolution *evol = xmalloc(sizeof(struct Evolution));
    evol->max_generations = 0;
    evol->population_size = 0;
    evol->tournament_size = 0;
    evol->mutability = 0;

    return evol;
}

#define DARWIN_DEFINE_FUNC_LIVE(T, problem)                                     \
void                                                                            \
live(                                                                           \
        struct Evolution *evol,                                                 \
        char * problem##_file_name                                              \
) {                                                                             \
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
#include "life-generic-defs.h"
#undef DARWIN_DEFINE_FUNC_LIVE
//destroy_##problem(problem);
