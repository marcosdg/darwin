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

*/
#include <assert.h>
#include <math.h>       /* abs */
#include <stdlib.h>     /* malloc, free */
#include <string.h>     /* memset */
#include "base/report.h"
#include "life.h"


struct Evolution *
genesis(
        void
) {
    struct Evolution *evol = malloc(sizeof(struct Evolution));
    if (evol == NULL) {
        error("Could not begin genesis");
    }
    evol->max_generations = 0;
    evol->population_size = 0;
    evol->tournament_size = 0;
    evol->mutability = 0;

    return evol;
}