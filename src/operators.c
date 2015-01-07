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
#include "genome.c"


int single_point_crossover(struct individual *dad, struct individual *mom,
                           struct individual *son, struct individual *daughter)
{
    int at,
        fst_half,
        snd_half;

	if (!dad || !mom || !son || !daughter) {
        error_verbose(__FILE__, "single_point_crossover",
                      "One of the individuals is NULL.");
    }
	at = random_in_range_exclusive(1, CHROMOSOME_LENGTH);
    fst_half = at * GENE_BYTES;
	snd_half = CHROMOSOME_BYTE_SIZE - fst_half;

    memcpy(son->genes, dad->genes, fst_half);
	memcpy((son->genes + at), (mom->genes + at), snd_half); 	
	memcpy(daughter->genes, mom->genes, fst_half);
	memcpy((daughter->genes + at), (dad->genes + at), snd_half);

	return 0;
}

int single_point_mutation(struct individual *victim)
{
    int at;

    if (!victim) {
        error_verbose(__FILE__, "single_point_mutation", "The victim is NULL.");
    }
    at = random_in_range_inclusive(0, CHROMOSOME_LENGTH);
    victim->genes[at] = random_excluding(NUCLEOTIDE_MIN, victim->genes[at],
                                         NUCLEOTIDE_MAX);
    return 0;
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

