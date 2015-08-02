/*  stats.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
    strategy.

    Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>

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
    Common statistical utility functions
*/
/*
    #included

    <stddef.h> NULL
    "stats.h" "../genome.h"
*/
#include <assert.h>
#include <stddef.h>
#include "stats.h"

double
stats_best_fitness(
        struct Population *city
) {
    assert(city != NULL);

    double best = 0.0;
    int next;

    best = city->people[0]->fitness;
    for (next = 1; next < city->current_size; next += 1) {
        if (city->people[next]->fitness > best) {
            best = city->people[next]->fitness;
        }
    }
    return best;
}

double
stats_worst_fitness(
        struct Population *city
) {
    assert(city != NULL);

    double worst = 0.0;
    int next;

    worst = city->people[0]->fitness;
    for (next = 1; next < city->current_size; next += 1) {
        if (city->people[next]->fitness < worst) {
            worst = city->people[next]->fitness;
        }
    }
    return worst;
}

double
stats_avg_fitness(
        struct Population *city
) {
    assert(city != NULL);

    double sum = 0.0;
    int i;

    for (i = 0; i < city->current_size; i += 1) {
        sum += city->people[i]->fitness;
    }
    return sum / (double) city->current_size;
}
