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
create_encoding(
        int units_per_gene,
        int num_genes
) {
    assert((units_per_gene >= MIN_UNITS_PER_GENE)
            && (num_genes >= MIN_NUM_GENES));

    struct Encoding *e = (struct Encoding *) malloc(sizeof(struct Encoding));
    if (!e) {
        ERROR_VERBOSE("Could not create encoding");
    }
    e->units_per_gene = units_per_gene;
    e->num_genes = num_genes;
    e->dna_byte_size = UNIT_BYTE_SIZE * (e->units_per_gene) * (e->num_genes);
    e->dna_length = (e->units_per_gene) * (e->num_genes);

    return e;
}

/*
    Individual.
*/

struct Individual *
create_individual(
        struct Encoding *e
) {
    assert(e != NULL);

    struct Individual *one = (struct Individual *)
                                malloc(sizeof(struct Individual));
    long int *dna = (long int *) malloc(e->dna_byte_size);
    if (!one || !dna) {
        ERROR_VERBOSE("Could not create individual");
    }
    memset(dna, 0, e->dna_byte_size);
    one->dna = dna;
    one->fitness = 0.0;
    one->evolvability = 0.0;

    return one;
}

struct Individual *
create_random_individual(
        struct Encoding *e
) {
    assert(e != NULL);

    struct Individual *one = create_individual(e);
    randomize_bins(one->dna, e->dna_length);

    return one;
}

void
invert(
        struct Individual *one,
        long int locus,
        struct Encoding *e
) {
    assert((one != NULL) && (e != NULL));
    assert((locus >= 0) && (locus < e->dna_length));

    one->dna[locus] = abs(1 - (one->dna[locus]));
}

/* fitness_proportion:
 * How much better is 'whom' than 'other'?
 *
 * If one has zero or negative fitness is disregarded to avoid possible
 * divisions by zero or misleading results. In consequence, tournament
 * selection will behave 'determinalistically', as this function decides
 * who is likely to be selected.
 */
double
fitness_proportion(
        struct Individual *whom,
        struct Individual *other
) {
    assert((whom != NULL) && (other != NULL));

    if (whom->fitness <= 0.0) { /* other is the best */
        return 0.0;
    } else if (other->fitness <= 0.0) { /* whom is the best */
        return 1.0;
    }
    return whom->fitness / (whom->fitness + other->fitness);
}

/*
    Population.
*/

struct Population *
create_empty_population(
        struct Encoding *e,
        int max_size
) {
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
create_random_population(
        struct Encoding *e,
        int size
) {
    assert((e != NULL) && (size > 0));

    struct Population *population = create_empty_population(e, size);
    struct Individual *one;
    int much;

    for (much = 1; much <= size; much += 1) {
        one = create_random_individual(e);
        add_individual(population, one);
    }
    return population;
}

void
add_individual(
        struct Population *population,
        struct Individual *new
) {
    assert((population != NULL) && (new != NULL));

    if (population->current_size < population->max_size) {
        population->people[population->next_free_spot] = new;
        population->current_size += 1;
        population->next_free_spot += 1;
    }
}

struct Individual *
pick_random_individual(
        struct Population *population
) {
    assert(population != NULL);

    int at = random_in_range_exclusive(0, population->max_size);

    return population->people[at];
}

