/*  life.h

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
    This is darwin's third level of abstraction where the genetic algorithm is
    defined using the genetic operators (see src/operators.h) and the basic
    structures (see src/genome.h, src/experiment/hampath/hampath.h,
    src/experiment/nqueens/nqueens.h, src/experiment/nqueens/nqueens.c)

    It relies on 'life-generic-protos.h' to decide the appropriate macro
    invocation, for the functions' prototypes, according to which problem the
    user chose.
*/
#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

struct Evolution {
    int max_generations;
    int population_size;
    int tournament_size;
    int mutability;
};

extern struct Evolution *
genesis(
        void
);

#define DARWIN_DECLARE_FUNC_LIVE(T, problem)\
void                                        \
live(                                       \
        struct Evolution *evol,             \
        char * problem##_file_name          \
);
#include "life-generic-protos.h"
#undef DARWIN_DECLARE_FUNC_LIVE

#endif /* LIFE_H_INCLUDED */
