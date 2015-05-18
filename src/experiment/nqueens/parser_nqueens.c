/*  parser_nqueens.c

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
#include <stdio.h>              /* fclose, fgets, fopen */
#include <stdlib.h>             /* atoi, free, NULL */
#include <string.h>             /* strstr */
#include "../../base/report.h"
#include "../parse.h"
#include "parser_nqueens.h"
/*
    Parser features.
*/
static const int MAX_COLUMNS = 80;
/*
    Configuration file symbols.
*/
static const char *TOKEN_COMMENT = "#";
static const char *TOKEN_BOARD_SIZE = "BOARD_SIZE";


struct NQueens *
load_nqueens(
        const char *file_name
) {
    int board_size = 0;
    char *line = malloc(MAX_COLUMNS * sizeof(char));
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
        if (strstr(line, TOKEN_BOARD_SIZE)) {
           board_size = atoi(get_line(line, MAX_COLUMNS, file));
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    return create_nqueens(board_size);
}
