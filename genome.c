/*
 * genome.c
 * Marcos Díez García
 * 26-12-14
 *
 * Basic routines to manipulate individuals and the population.
 *
 * */

#include<string.h>
#include "genome.h"
#include "random.c"


struct individual * create_raw_individual(int chromosome_length)
{
        struct individual *new = (struct individual *)
					malloc(sizeof(struct individual));

	int *genes = (int *) malloc(chromosome_length * GENE_BYTES);
	memset(genes, 0, chromosome_length * GENE_BYTES);
        new->genes = genes;
        new->fitness = 0.0;
	new->evolvability = 0.0;

        return new;
}
/* struct population * create_random_population(...){}
 */
