/*
 * (Draft)
 * operators.c
 * Marcos Díez García
 * 26-12-14
 *
 * Routines to implement the genetic operators: selection, crossover, mutation and
 * replacement.
 *
 * */
#include "genome.c"


int single_point_crossover(struct individual *dad, struct individual *mom,
                           struct individual *son, struct individual *daughter)
{
	int at,
	    fst_half,
	    snd_half;

	if (!dad || !mom || !son || !daughter) {
                error_verbose(__FILE__, "single_point_crossover",
                              "One of the individuals is NULL.");
        }
	at = random_in_range(1, CHROMOSOME_LENGTH - 1);
        fst_half = at * GENE_BYTES;
	snd_half = CHROMOSOME_BYTE_SIZE - fst_half;

	memcpy(son->genes, dad->genes, fst_half);
	memcpy((son->genes + at), (mom->genes + at), snd_half); 	
	memcpy(daughter->genes, mom->genes, fst_half);
	memcpy((daughter->genes + at), (dad->genes + at), snd_half);

	return 0;
}

int single_point_mutation(struct individual *victim)
{
        int at;

        if (!victim) {
                error_verbose(__FILE__, "single_point_mutation",
                              "The victim is NULL.");
        }
        at = random_in_range(0, CHROMOSOME_LENGTH - 1);
        victim->genes[at] = random_excluding(NUCLEOTIDE_MIN,
                                                victim->genes[at],
                                                NUCLEOTIDE_MAX);
        return 0;
}

/*
int adaptative_mutation(struct population *pop,
                        double (*mutation_probability_function)(struct *individual))
{
        int i, r;

        for (i = 0; i < pop->current_size; i += 1) {
                r = random_in_range(0, 10);
                
                if (r < (*mutation_probability_function)(pop->individuals[i]) * 10) {
                        single_point_mutation(pop->individuals[i]);
                }
        }
}
*/

