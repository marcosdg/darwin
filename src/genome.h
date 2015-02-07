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
  genome.h
  Marcos Díez García
  02-01-2015

  This document constitutes the lowest abstraction level of DARWIN, defining
  how candidate solutions (also called individuals) to a particular problem are
  encoded. Such encoding corresponds to the "Search Space" (Genotype); its
  equivalent representation in the "Solution Space" (Phenotype) is obtained by
  means of a decoding function, which will be different for each problem.

  DARWIN assumes an integer-based genotipic representation. Thus, any problem
  involving a real-based (or any other) phenotipic representation needs to be
  mapped to an equivalent integer-based genotipic representation. This mapping
  can be achieved by means of a decoding function and choosing the right
  genetic representation of individuals for the problem.

*/
#ifndef GENOME_H_INCLUDED
#define GENOME_H_INCLUDED

#include <string.h>
#include "random.h"


#define UNIT_SIZE sizeof(long int)
#define MIN_UNITS_PER_GENE 1
/*
    To perform crossover individuals must have, at least, 2 genes.
*/
#define MIN_NUM_GENES 2


/*
    Data structures.
*/

struct Encoding {
    int units_per_gene;
    int num_genes;
    int dna_byte_size;
    int dna_length;
};

struct Individual {
    double fitness;
    double evolvability;
    long int *dna;
};

struct Population {
    struct Encoding *encoding;
    struct Individual **people;
    int next_free_spot;     /* helpful to add individuals */
    int generation;
    int current_size;
    int max_size;
};

/*
    Prototypes.
*/

/* encoding */

extern struct Encoding *
create_encoding(int units_per_gene,
                int num_genes);

/* individual */

extern struct Individual *
create_individual(struct Encoding *e);

extern struct Individual *
create_random_individual(struct Encoding *e);

extern void
invert(struct Individual *one,
        long int locus,
        struct Encoding *e);

/* population */

extern struct Population *
create_empty_population(struct Encoding *e,
                        int max_size);

extern struct Population *
create_random_population(struct Encoding *e,
                            int initial_size,
                            int max_size);
extern void
add_individual(struct Population *population,
                struct Individual *new);

#endif /* GENOME_H_INCLUDED */
