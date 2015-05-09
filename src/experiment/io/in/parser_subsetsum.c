/*  parser_subsetsum.c

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
    The Subset Sum problem configuration file parser.
*/
#include <assert.h>
#include <stdio.h>              /* fclose, fgets, fopen */
#include <stdlib.h>             /* atoi, free, malloc, NULL */
#include <string.h>             /* strstr */
#include "../../../base/report.h"
#include "parse.h"
#include "parser_subsetsum.h"
/*
    Parser features.
*/
const int MAX_COLUMNS = 80;
/*
    Configuration file symbols.
*/
const char *TOKEN_COMMENT = "#";
const char *TOKEN_TARGET = "TARGET";
const char *TOKEN_SETSIZE = "SETSIZE";
const char *TOKEN_SET = "SET";


struct Subsetsum *
load_subsetsum(
        const char *file_name /* subsetsum instance */
) {
    int target = 0;
    int set_size = 0;
    int *set;
    int i;

    char *line = (char *) malloc(MAX_COLUMNS * sizeof(char));
    //char *file_name = get_path(instance_name);
    FILE *file;
    if (line == NULL) {
        error("Could not start parsing. Out of memory");
    }
    file = fopen(file_name, "r");
    if (file == NULL) {
        error("Could not open configuration file");
    }

    while (strstr(get_line(line, MAX_COLUMNS, file), TOKEN_COMMENT));

    do {
        if (strstr(line, TOKEN_TARGET)) {
            target = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_SETSIZE)) {
            set_size = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_SET)) {
            set = (int *) malloc(set_size * sizeof(int));
            for (i = 0; i < set_size; i += 1) {
                set[i] = atoi(get_line(line, MAX_COLUMNS, file));
            }
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    return create_subsetsum(target, set, set_size);
}
