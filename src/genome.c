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
    genetic algorithm that it implements are specified (see genome.h for details)
*/
/*
    #included

    <stdlib.h> labs, free, NULL
    <string.h> memset
    "base/xmem.h" xmalloc
    "base/random.h" randomize_ints, random_int_inclusive
*/
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "base/xmem.h"
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
    assert(units_per_gene >= MIN_UNITS_PER_GENE);
    assert(num_genes >= MIN_NUM_GENES);

    struct Encoding *e = xmalloc(sizeof(struct Encoding));
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

    struct Individual *one = xmalloc(sizeof(struct Individual));
    long int *dna = xmalloc(e->dna_byte_size);

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
    randomize_ints(one->dna, e->dna_length, 0, 1);

    return one;
}
int
destroy_individual(
        struct Individual *it
) {
    int destroyed = 0;
    if (it != NULL) {
        free(it->dna);
        free(it);
        destroyed = 1;
    }
    return destroyed;
}

void
invert(
        struct Individual *one,
        long int locus,
        struct Encoding *e
) {
    assert(one != NULL);
    assert(e != NULL);
    assert((locus >= 0) && (locus < e->dna_length));

    one->dna[locus] = labs(1 - (one->dna[locus]));
}
/*
    Population.
*/
struct Population *
create_empty_population(
        int max_size,
        struct Encoding *e
) {
    assert(e != NULL);
    assert(max_size > 0);

    struct Population *city = xmalloc(sizeof(struct Population));
    struct Individual **people = xmalloc(max_size * sizeof(struct Individual *));

    city->e = e;
    city->people = people;
    city->next_free_spot = 0;
    city->current_size = 0;
    city->max_size = max_size;

    return city;
}
struct Population *
create_random_population(
        int size,
        struct Encoding *e
) {
    assert(e != NULL);
    assert(size > 0);

    struct Population *city = create_empty_population(size, e);
    struct Individual *one;

    do {
        one = create_random_individual(e);
        add_individual(city, one);
     } while(city->current_size != size);

    return city;
}
int
destroy_population(
        struct Population *city
) {
    int destroyed = 0;
    int at;
    if (city != NULL) {
        for (at = 0; at < city->current_size; at += 1) {
            destroy_individual(city->people[at]);
        }
        free(city->people);
        free(city->e);
        free(city);
        destroyed = 1;
    }
    return destroyed;
}

void
add_individual(
        struct Population *city,
        struct Individual *new
) {
    assert(city != NULL);
    assert(new != NULL);

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
