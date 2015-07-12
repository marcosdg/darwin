/*  queen.c

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
    The N-Queens submodule: basic structures and functions.
    (see nqueens.{h, c})
*/
/*
    #included

    <math.h> abs
    <stdlib.h> free, NULL
    "../../base/xmem.h" xmalloc
*/
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include "../../base/xmem.h"
#include "queen.h"


struct Queen *
create_queen(
        int row,
        int column
) {
    assert(row >= 0);
    assert(column >= 0);

    struct Queen *queen = xmalloc(sizeof(struct Queen));
    queen->row = row;
    queen->column = column;

    return queen;
}
int
destroy_queen(
        struct Queen *queen
) {
    int destroyed = 0;
    if (queen != NULL) {
        free(queen);
        destroyed = 1;
    }
    return destroyed;
}
/*
    attack:

    Darwin assumes that if A attacks B, then B also attacks A.
*/
int
attack(
        struct Queen *q1,
        struct Queen *q2
) {
    assert(q1 != NULL);
    assert(q2 != NULL);

    /* same row||column||diagonal ? */
    return (q1->row == q2->row) || (q1->column == q2->column)
            || (abs(q1->row - q2->row) == abs(q1->column - q2->column));
}
