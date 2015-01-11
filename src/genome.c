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
  genome.c
  Marcos Díez García
  02-01-15

  Basic routines to manipulate individuals and the population.

*/
#include <string.h>
#include "genome.h"
#include "random.c"

/*
    Individual.
*/

struct individual * create_individual(int chromosome_length)
{
    struct individual *new = (struct individual *)
                                malloc(sizeof(struct individual));
    long int *genes = (long int *) malloc(chromosome_length * GENE_BYTES);

    memset(genes, 0, chromosome_length * GENE_BYTES);
    new->genes = genes;
    new->fitness = 0.0;
    new->evolvability = 0.0;

    return new;
}
struct individual * create_random_individual(struct population *population)
{
    struct individual *new;

    if (!population) {
        error_verbose(__FILE__,"create_random_individual", "'population is NULL'");
    }
    new = create_individual(population->chromosome_length);
    randomize_ints(new->genes, population->chromosome_length,
                    min_nucleotide_value(population),
                    max_nucleotide_value(population));
    return new;
}

/*
    Population.
*/

struct population * create_empty_population(
    int max_size,
    int chromosome_length,
    int nucleotides_length,
    long int *nucleotides
) {
    struct population *population = (struct population *)
                                    malloc(sizeof(struct population));
    struct individual **people = (struct individual **)
                                 malloc(max_size * sizeof(struct individual));
    population->people = people;
    population->next_free_spot = 0;
    population->current_size = 0;
    population->max_size = max_size;

    population->chromosome_length = chromosome_length;
    population->nucleotides_length = nucleotides_length;
    population->nucleotides = nucleotides;

    return population;
}
struct population * create_random_population(
    int initial_size,
    int max_size,
    int chromosome_length,
    int nucleotides_length,
    long int *nucleotides
) {
    struct population *population = create_empty_population(max_size,
                                                            chromosome_length,
                                                            nucleotides_length,
                                                            nucleotides);
    struct individual *new;
    int i;
    for (i = 0; i < initial_size; i += 1) {
        new = create_random_individual(population);
        add_individual(population, new);
    }
    return population;
}

int add_individual(
    struct population *population,
    struct individual *new
) {
    int added = 0;

    if (!population || !new) {
       error_verbose(__FILE__, "add_individual",
                     "'population' or 'new' is NULL.");
    }
    if (population->current_size < population->max_size) {
        population->people[population->next_free_spot] = new;
        population->current_size += 1;
        population->next_free_spot += 1;
        added = 1;
    }
    return added;
}
/* 
    Encoding.
*/
long int min_nucleotide_value(struct population *population)
{
    if (!population) {
        error_verbose(__FILE__, "min_nucleotide_value", "'population is NULL'");
    }
    return population->nucleotides[0];
}
long int max_nucleotide_value(struct population *population)
{
    if (!population) {
        error_verbose(__FILE__, "min_nucleotide_value", "'population is NULL'");
    }
    return population->nucleotides[population->nucleotides_length - 1];
}

