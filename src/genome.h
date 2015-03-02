/*  genome.h

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
    genome.h constitutes the lowest abstraction level of DARWIN in which the
    fundamentals of the genetic algorithm to be implemented are specified.

    It defines how candidate solutions (also called individuals) to a particular
    problem are encoded. All solutions can be represented in 2 different,
    but related, ways: in the "Search Space" or in the "Solution space". The
    former is also known as the "Genotype" and the latter as the "Phenotype".
    For different problems they will be different, as well as the mapping
    function (decoding function) which translates Genotype to Phenotype.

    Darwin forces an integer-based (limited to 0 and 1) genotypic representation.
    Thus, every problem must be encoded in a binary fashion, independently of
    the phenotypic representation chosen.
*/
#ifndef GENOME_H_INCLUDED
#define GENOME_H_INCLUDED

#include <string.h>
#include "lib/random.h"

/*
 * Encoding.
 */

#define UNIT_BYTE_SIZE sizeof(long int)
#define MIN_UNITS_PER_GENE 1
#define MIN_NUM_GENES 2 /* at least, to perform crossover */

struct Encoding {
    int units_per_gene;
    int num_genes;
    int dna_byte_size;
    int dna_length;
};

extern struct Encoding *
create_encoding(
        int units_per_gene,
        int num_genes
);

/*
    Individual.
*/

struct Individual {
    double fitness;
    double evolvability;
    long int *dna;
};

extern struct Individual *
create_individual(
        struct Encoding *e
);
extern struct Individual *
create_random_individual(
        struct Encoding *e
);

extern void
invert(
        struct Individual *one,
        long int locus,
        struct Encoding *e
);

extern double
fitness_proportion(
        struct Individual *whom,
        struct Individual *other
);

/*
    Population.
*/

struct Population {
    struct Encoding *encoding;
    struct Individual **people;
    int next_free_spot;     /* helpful to add individuals */
    int generation;
    int current_size;
    int max_size;
};

extern struct Population *
create_empty_population(
        struct Encoding *e,
        int max_size
);
extern struct Population *
create_random_population(
        struct Encoding *e,
        int size
);
extern void
add_individual(
        struct Population *population,
        struct Individual *new
);

extern struct Individual *
pick_random_individual(
        struct Population *population
);
#endif /* GENOME_H_INCLUDED */
