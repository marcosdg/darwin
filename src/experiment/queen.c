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
    queen.{h,c} provide the basic structures and functions to the N-Queens
    problem.
*/
#include <assert.h>
#include <math.h>           /* abs */
#include <stdlib.h>         /* malloc */
#include "../base/report.h"
#include "queen.h"


struct Queen *
create_queen(
        int row,
        int column
) {
    assert((row >= 0) && (column >= 0));

    struct Queen *queen = (struct Queen *) malloc(sizeof(struct Queen));
    if (queen == NULL) {
        error("Could not create queen");
    }
    queen->row = row;
    queen->column = column;

    return queen;
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
    assert((q1 != NULL) && (q2 != NULL));

    /* same row|column|diagonal ? */
    return ((q1->row == q2->row) || (q1->column == q2->column)
            || (abs(q1->row - q2->row) == abs(q1->column - q2->column))) ? 1 : 0;
}
