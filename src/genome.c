/*  genome.c

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
    This is darwin's first level of abstraction, in which the fundamentals of the
    genetic algorithm are specified (see genome.h for details)
*/
#include <assert.h>
#include <math.h>       /* abs */
#include <stdio.h>
#include <stdlib.h>     /* malloc */
#include <string.h>     /* memset */
#include "base/report.h"
#include "base/random.h"
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
    if (e == NULL) {
        error("Could not create encoding");
    }
    e->units_per_gene = units_per_gene;
    e->num_genes = num_genes;
    e->dna_byte_size = UNIT_BYTE_SIZE * units_per_gene * num_genes;
    e->dna_length = units_per_gene * num_genes;

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
    if (one == NULL || dna == NULL) {
        error("Could not create individual");
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
kill(
        struct Individual *it,
        struct Encoding *e
) {
    assert((e != NULL) && (it != NULL));

    free(it->dna);
    free(it);
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
/*
    Population.
*/
struct Population *
create_empty_population(
        int max_size,
        struct Encoding *e
) {
    assert((e != NULL) && (max_size > 0));

    struct Population *city = (struct Population *)
                                malloc(sizeof(struct Population));
    struct Individual **people = (struct Individual **)
                                    malloc(max_size * sizeof(struct Individual));
    if (city == NULL || people == NULL) {
        error("Could not create empty population");
    }
    city->e = e;
    city->people = people;
    city->next_free_spot = 0;
    city->generation = 0;
    city->current_size = 0;
    city->max_size = max_size;

    return city;
}
struct Population *
create_random_population(
        int size,
        struct Encoding *e
) {
    assert((e != NULL) && (size > 0));

    struct Population *city = create_empty_population(size, e);
    struct Individual *one;

    do {
        one = create_random_individual(e);
        add_individual(city, one);
     } while(city->current_size != size);

    return city;
}
void
exterminate(
        struct Population *city
) {
    assert(city != NULL);

    int at;

    for (at = 0; at < city->current_size; at += 1) {
        kill(city->people[at], city->e);
    }
    free(city->people);
    free(city->e);
    free(city);
}

void
add_individual(
        struct Population *city,
        struct Individual *new
) {
    assert((city != NULL) && (new != NULL));

    if (city->current_size < city->max_size) {
        city->people[city->next_free_spot] = new;
        city->current_size += 1;
        city->next_free_spot += 1;
    }
}

struct Individual *
pick_random_individual(
        struct Population *city
) {
    assert(city != NULL);

    int at = random_int_exclusive(0, city->current_size);

    return city->people[at];
}
