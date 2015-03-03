/*  metrics.c

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
    metrics.{h,c} implement routines to handle distance measurements.
*/
#include "metrics.h"


/*  hamming_distance:
    Given 2 sequences of bits (as long ints) of equal length, returns the number
    of places in which they differ.
*/
int
hamming_distance(
        long int *bits1,
        long int *bits2, 
        int length
) {
    assert((bits1 != NULL) && (bits2 != NULL));
    assert(length > 0);

    int d = 0;
    int at;

    for (at = 0; at < length; at += 1) {
        if (bits1[at] != bits2[at]) {
            d += 1;
        }
    }
    return d;
}

