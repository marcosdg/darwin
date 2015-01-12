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
#define GENE_BYTES sizeof(long int)
/*
    To perform crossover individuals must have, at least, 2 genes.
*/
#define CHROMOSOME_MIN_LENGTH 2

/*
    Data types.
*/

struct encoding {
    int genes_length;
    int nucleotides_length;
    long int *nucleotides;  /* possible gene values */
};

struct individual {
    long int *genes;
    double fitness;
    double evolvability;
};

struct population {
    struct individual **people;
    struct encoding *encoding;
    int next_free_spot;     /* helpful to add individuals */
    int generation;
    int current_size;
    int max_size;
};


/*
    Encoding functions.
*/


struct encoding * create_encoding(
    int genes_length,
    int nucleotides_length,
    long int *nucleotides
);
long int min_nucleotide_value(struct encoding *encoding);
long int max_nucleotide_value(struct encoding *encoding);


/*
    Individual functions.
*/


struct individual * create_individual(struct encoding *encoding);
struct individual * create_random_individual(struct population *population);


/*
    Population functions.
*/


struct population * create_empty_population(
    int max_size,
    struct encoding *encoding
);
struct population * create_random_population(
    int initial_size,
    int max_size,
    struct encoding *encoding
);
int add_individual(
    struct population *population,
    struct individual *new
);

