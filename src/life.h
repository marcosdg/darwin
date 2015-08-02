/*  life.h

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
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

    It relies on 'life-generic-protos.h' to decide the appropriate macro
    invocation, for the functions' prototypes, according to which problem the
    user chose.
*/
/*
    #included

    "genome.h" struct Individual, struct Population
    "experiment/hampath/hampath.h" struct Hampath, "../../genome.h"
    "experiment/nqueens/nqueens.h" struct NQueens
    "experiment/subsetsum/subsetsum.h" struct Subsetsum
*/
#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

#include "experiment/hampath/hampath.h"
#include "experiment/nqueens/nqueens.h"
#include "experiment/subsetsum/subsetsum.h"


struct Evolution_state {
    int generation;
    int best_fitness_generation;
    int worst_fitness_generation;
    double avg_fitness;
    double best_fitness_ever;
    double worst_fitness_ever;
};

extern struct Evolution_state *
get_evol_state(
        void
);

struct Evolution {
    int max_generations;
    int population_size;
    int tournament_size;
    double mutability;
};

extern struct Evolution *
create_evolution(
        void
);
extern void
apocalypse(
        struct Evolution *evol,
        struct Population *omega
);

#define DARWIN_DECLARE_FUNC_EVALUATE(T, problem)\
void                                            \
evaluate(                                       \
        struct Individual *child,               \
        struct Individual *dad,                 \
        struct Individual *mom,                 \
        struct T *problem                       \
);

#define DARWIN_DECLARE_FUNC_LIVE(T, problem)\
struct Population *                         \
live(                                       \
        struct Evolution *evol,             \
        struct T *problem                   \
);
#include "life-generic-protos.h"
#undef DARWIN_DECLARE_FUNC_EVALUATE
#undef DARWIN_DECLARE_FUNC_LIVE

#endif /* LIFE_H_INCLUDED */
