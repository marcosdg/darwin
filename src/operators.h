/*  operators.h

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
    operators.{h,c} implement the 4 basic evolutional operations of Genetic
    Algorithms:
        1. Selection:
            which individuals will produce new individuals?
        2. Crossover:
            maiting between selected individuals.
        3. Mutation:
            individuals' DNA alterations.
        4. Replacement:
            which individuals will persist from one generation to the next one?
*/
#ifndef OPERATORS_H_INCLUDED
#define OPERATORS_H_INCLUDED

#include "genome.h"
#include "lib/metrics.h"

extern struct Individual *
tournament_selection(
        struct Population *population,
        int num_rounds
);

extern struct Individual **
single_point_crossover(
        struct Individual *dad,
        struct Individual *mom,
        struct Encoding *e
);

extern long int
single_point_mutation(
        struct Individual *victim,
        struct Encoding *e
);
/*
extern int
adaptative_mutation(
        struct population *pop,
        double (*mutation_probability_function)(struct *individual)
);
*/

extern int
diversity_contribution(
        struct Individual *one,
        struct Population *population,
        struct Encoding *e
);
extern void
replace_worst(
        struct Individual *incomer,
        struct Population *population
);

#endif /* OPERATORS_H_INCLUDED */
