/*
 * test.c
 * Marcos Díez García
 * 26-12-14
 *
 * Just to play around.
 *
 * */
#include "operators.c"


void main(void) 
{
	int i;

	struct individual *dad = create_raw_individual(6);
	struct individual *mom = create_raw_individual(6);
	struct individual *son = create_raw_individual(6);
	struct individual *daughter = create_raw_individual(6);

	dad->genes[0] = 0;
	dad->genes[1] = 1;
	dad->genes[2] = 0;
	dad->genes[3] = 1;
	dad->genes[4] = 0;
	dad->genes[5] = 0;

	mom->genes[0] = 0;
	mom->genes[1] = 0;
	mom->genes[2] = 1;
	mom->genes[3] = 0;
	mom->genes[4] = 1;
	mom->genes[5] = 0;

        initialise_random_sequence();

        printf("======== TEST CROSSOVER ========\n");
	
        single_point_crossover(dad, mom, son, daughter);

	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("SON GENE %d: %d\n", i, son->genes[i]);
	}
	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("DAUGHTER GENE %d: %d\n", i, daughter->genes[i]);
	}

        printf("======== TEST MUTATION ========\n");

        single_point_mutation(son);

	for (i = 0; i < CHROMOSOME_LENGTH; i += 1) {
		printf("SON GENE %d: %d\n", i, son->genes[i]);
	}
}
