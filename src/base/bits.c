/*  bits.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a self-adaptative
    strategy.

    Copyright (C) 2015 Marcos Díez García <marcos.diez.garcia@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
/*
    Common bit-manipulation utility functions.
*/
#include <assert.h>
#include <ctype.h>  /* isascii */
#include <math.h>   /* exp2 */
#include <stdlib.h> /* NULL */
#include "bits.h"
/*
    bits2int:

    Undefined behaviour if:
        1. 'length' does not match the actual 'bits' length
        2. Elements in 'bits' are greater than INT_MAX (see TODO in genome.h)
*/
int
bits2int(
        long int *bits,
        int length
) {
    assert(bits != NULL);
    assert(length > 0);

    int result = 0;
    double place = 0.0;
    int at;
    /*
        result = (b{length-1} * 2^(length-1)) +...+ (b{1} * 2^1) + (b{0} * 2^0)
    */
    for (at = length - 1; 0 <= at; at -= 1) {
        result += ((int) bits[at]) * ((int) exp2(place));
        place += 1.0;
    }
    return result;
}

/*
    digit_to_int:

    ISO C standard imposes the ten decimal digits from '0' up to '9' to have
    consecutive values in the character set.
*/
int
digit_to_int(
        char digit
) {
    return digit - '0';
}
