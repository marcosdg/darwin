/*
 * genome.h
 * Marcos Díez García
 * 25-12-2014
 *
 *
 * This document constitutes the lowest abstraction level of the program, defining
 * how 'solutions' to a particular problem are encoded.
 *
 * This encoding corresponds to the 'Search Space' or 'Genotype'. Its equivalent
 * in the 'Solution Space' or 'Phenotype' is obtained by means of a 'decoding
 * function', which will be different for each problem.
 *
 * */
#define GENE_BYTES sizeof(int)
#define CHROMOSOME_LENGTH 6
#define CHROMOSOME_BYTE_SIZE (CHROMOSOME_LENGTH * GENE_BYTE_SIZE)
/*
 * Nucleotides represent the vocabulary used to build the genes of an
 * individual. 
 *
 * We may define them exhaustively if values cannot be represented as a range: 
 * static int nucleotides[] = {1, 3, 5, 7};
 */
#define NUCLEOTIDE_MIN 0
#define NUCLEOTIDE_MAX 1


struct individual {
        int *genes;
	double fitness;
	double evolvability;
};

struct population {
        int current_size;
        int max_size;
        struct individual *individuals;
};
