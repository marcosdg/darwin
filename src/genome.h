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
    This is darwin's first level of abstraction, in which the fundamentals of the
    genetic algorithm are specified.

    It defines how candidate solutions (also called individuals) to a particular
    problem are encoded. All solutions can be represented within 2 different,
    but related, spaces: "Search Space" or "Solution Space". The former is also
    known as the "Genotype" and the latter as the "Phenotype". Normally, these
    will be different for each problem at hand, as well as the mapping function
    (decoding function) which translates from Genotype to Phenotype.

    Darwin assumes:

        1. An INTEGER-BASED (limited to 0 and 1) genotypic representation.
        Thus, every problem must be encoded in a binary scheme, independently of
        the phenotypic representation of the problem.

        2. All problems are treated as MAXIMIZATION problems. Hence, higher
        fitness means better solutions. Minimization problems can be equivalently
        interpreted as maximization ones.

        3. Fitness is normalized to the range [0, 1].

    TODO:
        Use a more appropriate type than 'long int' to encode binary sequences.
        Initially, 'long int' was chosen to avoid a possible overflow error in
        random_int_exlusive (see base/random.{h,c}) due to the limitation of
        the GNU C Library of having: RAND_MAX == INT_MAX.
*/
#ifndef GENOME_H_INCLUDED
#define GENOME_H_INCLUDED
/*
    Encoding.
*/
#define UNIT_BYTE_SIZE sizeof(long int)
#define MIN_UNITS_PER_GENE 1
#define MIN_NUM_GENES 2     /* required by crossover operator */

struct Encoding {
    int units_per_gene;     /* allele's length */
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
    double fitness;         /* solution's goodness */
    double evolvability;    /* parent's average fitness */
    long int *dna;          /* genotypical solution representation */
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
kill(
        struct Individual *it,
        struct Encoding *e
);

extern void
invert(
        struct Individual *one,
        long int locus,
        struct Encoding *e
);
/*
    Population.
*/
struct Population {
    struct Encoding *e;
    struct Individual **people;
    int next_free_spot;     /* helpful to add individuals */
    int generation;
    int current_size;
    int max_size;
};

extern struct Population *
create_empty_population(
        int max_size,
        struct Encoding *e
);
extern struct Population *
create_random_population(
        int size,
        struct Encoding *e
);
extern void
exterminate(
        struct Population *city
);

extern void
add_individual(
        struct Population *city,
        struct Individual *new
);

extern struct Individual *
pick_random_individual(
        struct Population *city
);
#endif /* GENOME_H_INCLUDED */
