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
/*
    #included
    
    <stdio.h> fclose, fopen, NULL
    <stdlib.h> atoi, free
    <string.h> strstr
    "../../base/report.h" <stdlio.h>, <stdlib.h>
    "../../base/xmem.h" xmalloc
    "../parse.h" get_line
    "parser_subsetsum.h" "subsetsum.h"
*/
#include <string.h>
#include "../../base/report.h"
#include "../../base/xmem.h"
#include "../parse.h"
#include "parser_subsetsum.h"
/*
    Parser features.
*/
static const int MAX_COLUMNS = 80;
/*
    Configuration file symbols.
*/
static const char *TOKEN_COMMENT = "#";
static const char *TOKEN_TARGET = "TARGET";
static const char *TOKEN_SETSIZE = "SETSIZE";
static const char *TOKEN_SET = "SET";


static int
valid_subsetsum_params(
        int target,
        int *set,
        int set_size
) {
    return (set != NULL)
            && (target >= subsetsum_min_target())
            && (set_size >= subsetsum_min_set_size());
}

struct Subsetsum *
load_subsetsum(
        const char *file_name
) {
    int target = 0;
    int set_size = 0;
    int *set;
    int i;

    char *line = xmalloc(MAX_COLUMNS * sizeof(char));
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        DARWIN_ERROR("Could not open the subset-sum configuration file");
    }

    while (strstr(get_line(line, MAX_COLUMNS, file), TOKEN_COMMENT));

    do {
        if (strstr(line, TOKEN_TARGET)) {
            target = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_SETSIZE)) {
            set_size = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_SET)) {
            set = xmalloc(set_size * sizeof(int));
            for (i = 0; i < set_size; i += 1) {
                set[i] = atoi(get_line(line, MAX_COLUMNS, file));
            }
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    if (!valid_subsetsum_params(target, set, set_size)) {
        DARWIN_ERROR("Bad subset-sum configuration file");
    }
    return create_subsetsum(target, set, set_size);
}
