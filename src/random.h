/*
  darwin. A simple genetic algorithm implementation with a
  self-adaptative strategy.

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
  (Draft)
  random.c
  Marcos Díez García
  02-01-15

  Routines to manipulate random numbers.

*/
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <assert.h>
#include <math.h>
#include <sys/time.h>
#include "report.h"

extern void
initialize_random_sequence(void);

extern long int
random_in_range_exclusive(long int lower,
                            long int upper);

extern long int
random_in_range_inclusive(long int lower,
                            long int upper);

extern long int
random_excluding(long int lower,
                    long int banned,
                    long int upper);

extern int
randomize_ints(long int *ints,
                int length,
                long int lower,
                long int upper);

#endif /* RANDOM_H_INCLUDED */