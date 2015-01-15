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
    Encoding.
*/

struct Encoding *
create_encoding(unsigned int *nucleotides,
                int nucleotides_length,
                int genes_length)
{
    struct Encoding *e = (struct Encoding *) malloc(sizeof(struct Encoding));
    e->nucleotides = nucleotides;
    e->nucleotides_length = nucleotides_length;
    e->genes_length = genes_length;

    return e;
}

unsigned int
min_nucleotide_value(struct Encoding *encoding)
{
    if (!encoding) {
        error_verbose(__FILE__, "min_nucleotide_value", "'encoding' is NULL");
    }
    return encoding->nucleotides[0];
}
unsigned int
max_nucleotide_value(struct Encoding *encoding)
{
    if (!encoding) {
        error_verbose(__FILE__, "max_nucleotide_value", "'encoding' is NULL");
    }
    return encoding->nucleotides[encoding->nucleotides_length - 1];
}

/*
    Individual.
*/

struct Individual *
create_individual(struct Encoding *encoding)
{
    struct Individual *new = (struct Individual *)
                                malloc(sizeof(struct Individual));
    unsigned int *genes = (unsigned int *) malloc(encoding->genes_length * GENE_BYTES);

    memset(genes, 0, encoding->genes_length * GENE_BYTES);
    new->genes = genes;
    new->fitness = 0.0;
    new->evolvability = 0.0;

    return new;
}
struct Individual *
create_random_individual(struct Population *population)
{
    struct Individual *new;

    if (!population) {
        error_verbose(__FILE__,"create_random_individual", "'population is NULL'");
    }
    new = create_individual(population->encoding);
    randomize_ints(new->genes,
                   population->encoding->genes_length,
                   min_nucleotide_value(population->encoding),
                   max_nucleotide_value(population->encoding));
    return new;
}

/*
    Population.
*/

struct Population *
create_empty_population(struct Encoding *encoding,
                        int max_size)
{
    struct Population *population;
    struct Individual **people;

    if (!encoding) {
        error_verbose(__FILE__, "create_empty_population", "'encoding' is NULL");
    }
    population = (struct Population *) malloc(sizeof(struct Population));
    people = (struct Individual **) malloc(max_size * sizeof(struct Individual));

    population->encoding = encoding;
    population->people = people;
    population->next_free_spot = 0;
    population->generation = 0;
    population->current_size = 0;
    population->max_size = max_size;

    return population;
}
struct Population *
create_random_population(struct Encoding *encoding,
                            int initial_size,
                            int max_size)
{
    struct Population *population = create_empty_population(encoding, max_size);
    struct Individual *new;
    int i;

    for (i = 0; i < initial_size; i += 1) {
        new = create_random_individual(population);
        add_individual(population, new);
    }
    return population;
}

int
add_individual(struct Population *population,
                struct Individual *new)
{
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

