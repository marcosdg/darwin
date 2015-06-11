/*  parser_evolution.c

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
    The evolution configuration file parser.
*/
#include <stdio.h>          /* fclose, fgets, fopen, NULL */
#include <stdlib.h>         /* atoi, free */
#include <string.h>         /* strstr */
#include "../base/report.h"
#include "../base/xmem.h"   /* xmalloc */
#include "parse.h"          /* get_line */
#include "parser_evolution.h"
/*
    Parser features.
*/
static const int MAX_COLUMNS = 80;
/*
    Configuration file symbols.
*/
static const char *TOKEN_COMMENT = "#";
static const char *TOKEN_MAX_GENERATIONS = "MAX_GENERATIONS";
static const char *TOKEN_POPULATION_SIZE = "POPULATION_SIZE";
static const char *TOKEN_TOURNAMENT_SIZE = "TOURNAMENT_SIZE";
static const char *TOKEN_MUTATION_PROBABILITY = "MUTATION_PROBABILITY";


static int
valid_evolution_params(
        struct Evolution *evol
) {
    return (evol->max_generations > 0)
            && (evol->population_size > 0)
            && (evol->tournament_size > 0)
            && ((evol->mutability == -1) /* adaptative mutation */
                || ((evol->mutability >= 0) && (evol->mutability <= 1)));
}

struct Evolution *
load_evolution(
        const char *file_name
) {
    struct Evolution *evol = genesis();
    int i;
    char *line = xmalloc(MAX_COLUMNS * sizeof(char));
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        DARWIN_ERROR("Could not open evolution configuration file");
    }

    while (strstr(get_line(line, MAX_COLUMNS, file), TOKEN_COMMENT));

    do {
        if (strstr(line, TOKEN_MAX_GENERATIONS)) {
            evol->max_generations = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_POPULATION_SIZE)) {
            evol->population_size = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_TOURNAMENT_SIZE)) {
            evol->tournament_size = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_MUTATION_PROBABILITY)) {
            evol->mutability = atoi(get_line(line, MAX_COLUMNS, file));
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    if (!valid_evolution_params(evol)) {
        DARWIN_ERROR("Bad evolution configuration file");
    }
    return evol;
}
