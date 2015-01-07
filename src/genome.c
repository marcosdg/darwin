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


struct individual * create_individual(int chromosome_length)
{
    struct individual *new = (struct individual *) malloc(sizeof(struct individual));
    int *genes = (int *) malloc(chromosome_length * GENE_BYTES);

    memset(genes, 0, chromosome_length * GENE_BYTES);
    new->genes = genes;
    new->fitness = 0.0;
    new->evolvability = 0.0;

    return new;
}

/*
bytes_from_to(struct individual *who, int from, int to)
{
    return (from * GENES_BYTES) - to * GENES_BYTES
}
*/

/*
struct population * create_empty_population(int max_size, int chromosome_length,
                                            int bytes_gene, int *nucleotides)
{
    struct population *population = (struct population *)
                                        malloc(sizeof(struct population));
    struct individual **people = (struct individual **)
                                     malloc(max_size * sizeof(struct individual));
    population->people = people;
    population->current_size = 0;
    population->max_size = max_size;
    population->chromosome_length = chromosome_length;
    population->bytes_gene = bytes_gene;
    population->nuleotides = nucleotides;
}
*/

/* struct population * create_random_population(...){}

*/

