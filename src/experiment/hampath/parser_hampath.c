/*  parser_hampath.c

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
    The Hamiltonian Path problem (undirected version) configuration file parser.
*/
/*
    #included

    <stdio.h> fclose, fopen, NULL
    <stdlib.h> atoi, free
    <string.h> strstr
    "../../base/report.h" <stdio.h>, <stdlib>
    "../../base/xmem.h" xmalloc
    "../../base/bits.h" digit_to_int
    "../parse.h" get_line, str_chop
    "parser_hampath.h" "hampath.h"
*/
#include <string.h>
#include "../../base/report.h"
#include "../../base/xmem.h"
#include "../../base/bits.h"
#include "../parse.h"
#include "parser_hampath.h"

static const int MAX_COLUMNS = 1024;
/*
    Configuration file symbols.
*/
static const char *TOKEN_COMMENT = "#";
static const char *TOKEN_DIMENSION = "DIMENSION";
static const char *TOKEN_ADJACENCY = "ADJACENCY";


static int
valid_hampath_params(
        int **adjacency,
        int dimension
) {
    return (adjacency != NULL) && (dimension >= hampath_min_graph_size());
}

struct Hampath *
load_hampath(
       const char *file_name
) {
    int col;
    int *row;
    int **adjacency;
    int dimension = 0;
    int i = 0;

    char *chunks;
    char *line = xmalloc(MAX_COLUMNS * sizeof(char));
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        DARWIN_ERROR("Could not open such hamiltonian-path input file");
    }

    while (strstr(get_line(line, MAX_COLUMNS, file), TOKEN_COMMENT));

    do {
        if (strstr(line, TOKEN_DIMENSION)) {
            dimension = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_ADJACENCY)) {
            adjacency = xmalloc(dimension * sizeof(int *));
            while (get_line(line, MAX_COLUMNS, file)) {
                row = xmalloc(dimension * sizeof(int));
                chunks = str_chop(line, " ");
                for (col = 0; col < dimension; col += 1) {
                    row[col] = digit_to_int(chunks[col]);
                }
                free(chunks);
                adjacency[i] = row;
                i += 1;
            }
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    if (!valid_hampath_params(adjacency, dimension)) {
        DARWIN_ERROR("Bad hamiltonian-path input file: parameters exceeded"
                        " allowed boundaries");
    }
    return create_hampath(create_graph(adjacency, dimension));
}
