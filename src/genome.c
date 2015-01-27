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
#include "genome.h"


/*
    Encoding.
*/

struct Encoding *
create_encoding(int units_per_gene,
                int dna_length)
{
    assert((units_per_gene >= MIN_UNITS_PER_GENE)
            && (dna_length >= MIN_DNA_LENGTH));

    struct Encoding *e = (struct Encoding *) malloc(sizeof(struct Encoding));
    if (!e) {
        ERROR_VERBOSE("Could not create encoding");
    }
    e->units_per_gene = units_per_gene;
    e->dna_length = dna_length;

    return e;
}

int
dna_byte_size(struct Encoding *e)
{
    assert(e != NULL);
    return (UNIT_SIZE * (e->units_per_gene) * (e->dna_length));
}

/*
    Individual.
*/

struct Individual *
create_individual(struct Encoding *e)
{
    assert(e != NULL);

    struct Individual *one = (struct Individual *)
                                malloc(sizeof(struct Individual));
    long int *dna = (long int *) malloc(dna_byte_size(e));
    if (!one || !dna) {
        ERROR_VERBOSE("Could not create individual");
    }
    memset(dna, 0, dna_byte_size(e));
    one->dna = dna;
    one->fitness = 0.0;
    one->evolvability = 0.0;

    return one;
}

struct Individual *
create_random_individual(struct Encoding *e)
{
    assert(e != NULL);

    struct Individual *one = create_individual(e);
    randomize_bins(one->dna, e->dna_length);

    return one;
}

/*
    Population.
*/

struct Population *
create_empty_population(struct Encoding *e,
                        int max_size)
{
    assert((e != NULL) && (max_size > 0));

    struct Population *population = (struct Population *)
                                        malloc(sizeof(struct Population));
    struct Individual **people = (struct Individual **)
                                    malloc(max_size * sizeof(struct Individual));
    if (!population || !people) {
        ERROR_VERBOSE("Could not create empty population");
    }
    population->encoding = e;
    population->people = people;
    population->next_free_spot = 0;
    population->generation = 0;
    population->current_size = 0;
    population->max_size = max_size;

    return population;
}

struct Population *
create_random_population(struct Encoding *e,
                            int initial_size,
                            int max_size)
{
    assert((e != NULL) && (initial_size > 0) && (max_size > 0)
            && (initial_size <= max_size));

    struct Population *population = create_empty_population(e, max_size);
    struct Individual *one;
    int i;

    for (i = 0; i < initial_size; i += 1) {
        one = create_random_individual(e);
        add_individual(population, one);
    }
    return population;
}

void
add_individual(struct Population *population,
                struct Individual *new)
{
    assert((population != NULL) && (new != NULL));

    if (population->current_size < population->max_size) {
        population->people[population->next_free_spot] = new;
        population->current_size += 1;
        population->next_free_spot += 1;
    }
}
