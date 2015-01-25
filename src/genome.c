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
create_encoding(long int *nucleotides,
                int nucleotides_length,
                int genes_length)
{
    assert((nucleotides != NULL) && (nucleotides_length > 0)
            && (genes_length >= MIN_CHROMOSOME_LENGTH));

    struct Encoding *e = (struct Encoding *) malloc(sizeof(struct Encoding));
    if (!e) {
        ERROR_VERBOSE("Could not create encoding");
    }
    e->nucleotides = nucleotides;
    e->nucleotides_length = nucleotides_length;
    e->genes_length = genes_length;

    return e;
}

long int
min_nucleotide_value(struct Encoding *encoding)
{
    assert(encoding != NULL);
    return encoding->nucleotides[0];
}

long int
max_nucleotide_value(struct Encoding *encoding)
{
    assert(encoding != NULL);
    return encoding->nucleotides[encoding->nucleotides_length - 1];
}

/*
    Individual.
*/

struct Individual *
create_individual(struct Encoding *encoding)
{
    assert(encoding != NULL);

    struct Individual *new = (struct Individual *)
                                malloc(sizeof(struct Individual));
    long int *genes = (long int *) malloc(encoding->genes_length * GENE_BYTES);
    if (!new || !genes) {
        ERROR_VERBOSE("Could not create individual");
    }
    memset(genes, 0, encoding->genes_length * GENE_BYTES);
    new->genes = genes;
    new->fitness = 0.0;
    new->evolvability = 0.0;

    return new;
}

struct Individual *
create_random_individual(struct Encoding *encoding)
{
    assert(encoding != NULL);

    struct Individual *new = create_individual(encoding);
    randomize_ints(new->genes,
                    encoding->genes_length,
                    min_nucleotide_value(encoding),
                    max_nucleotide_value(encoding));
    return new;
}

/*
    Population.
*/

struct Population *
create_empty_population(struct Encoding *encoding,
                        int max_size)
{
    assert((encoding != NULL) && (max_size > 0));

    struct Population *population = (struct Population *)
                                        malloc(sizeof(struct Population));
    struct Individual **people = (struct Individual **)
                                    malloc(max_size * sizeof(struct Individual));
    if (!population || !people) {
        ERROR_VERBOSE("Could not create empty population");
    }
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
    assert((encoding != NULL) && (initial_size > 0) && (max_size > 0)
            && (initial_size <= max_size));

    struct Population *population = create_empty_population(encoding, max_size);
    struct Individual *new;
    int i;

    for (i = 0; i < initial_size; i += 1) {
        new = create_random_individual(encoding);
        add_individual(population, new);
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
