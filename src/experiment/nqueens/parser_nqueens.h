/*  parser_nqueens.h

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
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
#ifndef PARSER_NQUEENS_H_INCLUDED
#define PARSER_NQUEENS_H_INCLUDED

#include "nqueens.h"

extern struct NQueens *
load_nqueens(
        const char *file_name
);
#endif /* PARSER_NQUEENS_H_INCLUDED */
