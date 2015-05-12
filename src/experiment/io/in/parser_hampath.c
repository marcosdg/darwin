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
#include <assert.h>
#include <stdio.h>              /* fclose, fgets, fopen */
#include <stdlib.h>             /* atoi, free, malloc, NULL */
#include <string.h>             /* strstr */
#include "../../../base/report.h"
#include "../../../base/bits.h"
#include "parse.h"
#include "parser_hampath.h"

static const int MAX_COLUMNS = 1024;
/*
    Configuration file symbols.
*/
static const char *TOKEN_COMMENT = "#";
static const char *TOKEN_DIMENSION = "DIMENSION";
static const char *TOKEN_ADJACENCY = "ADJACENCY";

struct Hampath *
load_hampath(
       const char *file_name /* hampath instance */
) {
    int *row;
    int col;
    int dimension;
    int **adjacency;
    int i = 0;

    char *chunks;
    char *line = (char *) malloc(MAX_COLUMNS * sizeof(char));
    // char *file_name = get_path(instance_name);
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
        if (strstr(line, TOKEN_DIMENSION)) {
            dimension = atoi(get_line(line, MAX_COLUMNS, file));

        } else if (strstr(line, TOKEN_ADJACENCY)) {
            adjacency = (int **) malloc(dimension * sizeof(int *));
            while (get_line(line, MAX_COLUMNS, file)) {
                row =  (int *) malloc(dimension * sizeof(int));
                chunks = str_chop(line, " ");
                for (col = 0; col < dimension; col += 1) {
                    row[col] = digit_to_int(chunks[col]);
                }
                adjacency[i] = row;
                i += 1;
            }
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    return create_hampath(create_graph(adjacency, dimension));
}
