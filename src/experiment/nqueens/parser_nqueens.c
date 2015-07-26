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
    The N-Queens problem configuration file parser.
*/
/*
    #included

    <stdio.h> fclose, fopen, NULL
    <stdlib.h> atoi, free
    <string.h> strstr
    "../../base/report.h" <stdio.h>, <stdlib.h>
    "../../base/xmem.h" xmalloc
    "../../base/darwin_limits.h" MAX_INT32
    "../parse.h" get_line
    "parser_nqueens.h" "nqueens.h"
*/
#include <string.h>
#include "../../base/report.h"
#include "../../base/xmem.h"
#include "../../base/darwin_limits.h"
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


static int
valid_nqueens_args(
        int board_size
) {
    return  (board_size >= nqueens_min_board_size())
            && (board_size <= MAX_INT32);
}

struct NQueens *
load_nqueens(
        const char *file_name
) {
    int board_size = 0;
    char *line = xmalloc(MAX_COLUMNS * sizeof(char));
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        DARWIN_ERROR("Could not open such n-queens input file");
    }

    while (strstr(get_line(line, MAX_COLUMNS, file), TOKEN_COMMENT));

    do {
        if (strstr(line, TOKEN_BOARD_SIZE)) {
           board_size = atoi(get_line(line, MAX_COLUMNS, file));
        }
    } while (get_line(line, MAX_COLUMNS, file) != NULL);

    free(line);
    fclose(file);

    if (!valid_nqueens_args(board_size)) {
        DARWIN_ERROR("Bad n-queens input file: parameters out of allowed"
                        " boundaries");
    }
    return create_nqueens(board_size);
}
