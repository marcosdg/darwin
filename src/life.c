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
/*
    #includes

    <stdlib.h> free, NULL
    "base/xmem.h" xmalloc
    "hampath.h" "../../genome.h"
    "experiment/hampath/parser_hampath.h" "hampath.h"
    "experiment/nqueens/parser_nqueens.h" "nqueens.h"
    "experiment/subsetsum/parser_subsetsum.h" "subsetsum.h"
    "experiment/parser_evolution.h" "../life.h"
*/
#include <stdlib.h>
#include "base/xmem.h"
#include "experiment/hampath/parser_hampath.h"
#include "experiment/nqueens/parser_nqueens.h"
#include "experiment/subsetsum/parser_subsetsum.h"
#include "experiment/parser_evolution.h"
#include "operators.h"

static struct Evolution_state *evol_state;


static void
start_evolution_state(
        void
) {
    evol_state = xmalloc(sizeof(struct Evolution_state));
    evol_state->generation = 0;
    evol_state->best_fitness = 0.0;
    evol_state->avg_fitness = 0.0;
    evol_state->worst_fitness = 0.0;
}
static int
destroy_evolution_state(
        void
) {
    int destroyed = 0;
    if (evol_state != NULL) {
        free(evol_state);
        destroyed = 1;
    }
    return destroyed;
}

void
update_evol_state(
        void
) {
    evol_state->generation += 1;
}

struct Evolution *
create_evolution(
        void
) {
    struct Evolution *evol = xmalloc(sizeof(struct Evolution));
    evol->max_generations = 0;
    evol->population_size = 0;
    evol->tournament_size = 0;
    evol->mutability = 0.0;

    return evol;
}
static int
destroy_evolution(
        struct Evolution *evol
) {
    int destroyed = 0;
    if (evol != NULL) {
        free(evol);
        destroyed = 1;
    }
    return destroyed;
}

#define DARWIN_DEFINE_FUNC_GENESIS(T, problem)                                  \
static void                                                                     \
genesis(                                                                        \
        char *problem##_file_name,                                              \
        struct T **problem,                                                     \
        struct Evolution **evol,                                                \
        struct Population **alpha                                               \
) {                                                                             \
    int i;                                                                      \
                                                                                \
    start_random_generator();                                                   \
    start_evolution_state();                                                    \
    if ((*evol)->mutability != -1.0) {                                          \
        set_constant_mutation_risk((*evol)->mutability);                        \
    }                                                                           \
    *problem = load_##problem(problem##_file_name);                             \
    *alpha = create_random_population((*evol)->population_size, (*problem)->e); \
    for (i = 0; i < (*alpha)->current_size; i += 1) {                           \
        evaluate((*alpha)->people[i], NULL, NULL, *problem); /* no parents */   \
    }                                                                           \
}
void
apocalypse(
        struct Evolution *evol,
        struct Population *omega
) {
    destroy_population(omega);
    destroy_evolution(evol);
    destroy_evolution_state();
}

#define DARWIN_DEFINE_FUNC_EVALUATE(T, problem)                             \
void                                                                        \
evaluate(                                                                   \
        struct Individual *child,                                           \
        struct Individual *dad,                                             \
        struct Individual *mom,                                             \
        struct T *problem                                                   \
) {                                                                         \
    struct T##_candidate *candidate = (*problem->decode)(child, problem);   \
    child->fitness = (*problem->objective)(candidate);                      \
    if (dad != NULL && mom != NULL) {                                       \
        child->evolvability = (dad->fitness + mom->fitness) / 2;            \
    }                                                                       \
    destroy_##problem##_candidate(candidate);                               \
}

#define DARWIN_DEFINE_FUNC_LIVE(T, problem)                                 \
struct Population *                                                         \
live(                                                                       \
        struct Evolution *evol,                                             \
        char *problem##_file_name                                           \
) {                                                                         \
    struct T *problem;                                                      \
    struct Population *city;                                                \
    struct Individual *dad;                                                 \
    struct Individual *mom;                                                 \
    struct Individual **offspring;                                          \
    int couples;                                                            \
    int half_city_size;                                                     \
                                                                            \
    genesis(problem##_file_name, &problem, &evol, &city);                   \
    half_city_size = city->current_size / 2;                                \
    /*                                                                      \
        The life's cycle                                                    \
    */                                                                      \
    while (evol_state->generation < evol->max_generations) {                \
        for (couples = 0; couples < half_city_size; couples += 1) {         \
            dad = tournament_selection(city, evol->tournament_size);        \
            mom = tournament_selection(city, evol->tournament_size);        \
            offspring = single_point_crossover(dad, mom, problem->e);       \
            if (evol->mutability == -1.0) {                                 \
                mutagen(adaptative_mutation_risk, offspring[0], problem->e);\
                mutagen(adaptative_mutation_risk, offspring[1], problem->e);\
            } else {                                                        \
                mutagen(constant_mutation_risk, offspring[0], problem->e);  \
                mutagen(constant_mutation_risk, offspring[1], problem->e);  \
            }                                                               \
            evaluate(offspring[0], dad, mom, problem);                      \
            evaluate(offspring[1], dad, mom, problem);                      \
            replace_worst(offspring[0], city);                              \
            replace_worst(offspring[1], city);                              \
            free(offspring);                                                \
        }                                                                   \
        update_evol_state();                                                \
    }                                                                       \
    destroy_##problem(problem);                                             \
                                                                            \
    return city;                                                            \
}
#include "life-generic-defs.h"
#undef DARWIN_DEFINE_FUNC_GENESIS
#undef DARWIN_DEFINE_FUNC_EVALUATE
#undef DARWIN_DEFINE_FUNC_LIVE
