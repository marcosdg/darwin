/*  random.h

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a self-adaptative
    strategy.

    Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>

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
    Common random numbers utility functions.
*/
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

extern void
init_random_generator(
        void
);

extern long int
random_int_exclusive(
        long int lower,
        long int upper
);
extern double
random_double_exclusive(
        double lower,
        double upper
);
extern long int
random_int_inclusive(
        long int lower,
        long int upper
);
extern double
random_double_inclusive(
        double lower,
        double upper
);

extern void
randomize_ints(
        long int *ints,
        int length,
        long int lower,
        long int upper
);
#endif /* RANDOM_H_INCLUDED */
