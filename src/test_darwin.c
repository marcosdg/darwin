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
#include <stdio.h>
#include "experiment/parser_evolution.h"

int main(int argc, char **argv)
{
    struct Evolution *evol = load_evolution(argv[1]);
    struct Population *city = live(evol, argv[2]);
    struct Evolution_state *evol_state = get_evol_state();

    printf("generations: %i\n", evol_state->generation);
    printf("avg fitness: %lf\n", evol_state->avg_fitness);
    printf("best fitness: %lf, at generation: %i\n",
            evol_state->best_fitness_ever, evol_state->best_fitness_generation);
    printf("worst fitness: %lf, at generation: %i\n",
            evol_state->worst_fitness_ever, evol_state->worst_fitness_generation);

    apocalypse(evol, city);

    return 0;
}
