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
  operators.c
  Marcos Díez García
  02-01-15

  Routines to implement the genetic operators: selection, crossover, mutation and
  replacement.

*/
#include "operators.h"


long int
single_point_crossover(struct Individual *dad,
                        struct Individual *mom,
                        struct Individual *son,
                        struct Individual *daughter,
                        struct Encoding *e)
{
    assert((dad != NULL) && (mom != NULL) && (son != NULL) && (daughter != NULL)
            && (e != NULL));

    long int locus = random_in_range_inclusive(1, (e->dna_length - 1));
    int fst_half = locus * UNIT_SIZE;
    int snd_half = e->dna_byte_size - fst_half;

    memcpy(son->dna, dad->dna, fst_half);
    memcpy((son->dna + locus), (mom->dna + locus), snd_half);
    memcpy(daughter->dna, mom->dna, fst_half);
    memcpy((daughter->dna + locus), (dad->dna + locus), snd_half);

    return locus;
}

long int
single_point_mutation(struct Individual *victim,
                        struct Encoding *e)
{
    assert ((victim != NULL) && (e != NULL));

    long int locus = random_in_range_exclusive(0, e->dna_length);
    invert(victim, locus, e);

    return locus;
}

/*
int adaptative_mutation(struct population *pop,
                        double (*mutation_probability_function)(struct *individual))
{
    int i, r;

    for (i = 0; i < pop->current_size; i += 1) {
        r = random_in_range(0, 10);
        if (r < (*mutation_probability_function)(pop->individuals[i]) * 10) {
            single_point_mutation(pop->individuals[i]);
        }
    }
}
*/

