/*  nqueens.c

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
    The N-Queens problem (see nqueens.h for details)
*/
#include <assert.h>
#include <math.h>           /* ceil, exp2, log2 */
#include <stdlib.h>         /* malloc, NULL */
#include <string.h>         /* memset */
#include "../base/report.h"
#include "../base/bits.h"
#include "nqueens.h"        /* genome.h */

static const int MIN_BOARD_SIZE = 4; /* No solutions for n=2 and n=3 */

static struct Candidate *
decode(struct Individual *cryptic, struct NQueens *nqueens);

static double
penalty(struct Candidate *candidate, struct NQueens *nqueens);

static double
objective(struct Candidate *candidate, struct NQueens *nqueens);



struct NQueens *
create_instance(
        int board_size
) {
    assert(board_size > MIN_BOARD_SIZE);

    int min_bits = (int) ceil(log2(board_size));
    struct Encoding *e = create_encoding(min_bits, board_size);
    struct NQueens *instance = (struct NQueens *) malloc(sizeof(struct NQueens));
    if (instance == NULL) {
        error("NQueens: Could not create instance");
    }
    instance->e = e;
    instance->decode = decode;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}

static struct Candidate *
create_candidate(
        struct NQueens *nqueens
) {
    assert(nqueens != NULL);

    int *loci_junk_alleles = (int *) malloc(nqueens->e->num_genes);
    struct Queen **queens = (struct Queen **)
                            malloc(nqueens->e->num_genes * sizeof(struct Queen *));
    struct Candidate *candidate = (struct Candidate *)
                                    malloc(sizeof(struct Candidate));
    if (loci_junk_alleles == NULL || queens == NULL || candidate == NULL) {
        error("NQueens: Could not create candidate");
    }
    memset(loci_junk_alleles, 0, nqueens->e->num_genes);
    candidate->loci_junk_alleles = loci_junk_alleles;
    candidate->queens = queens;

    return candidate;
}

static int
is_junk_allele(
        int column,
        struct NQueens *nqueens
) {
    assert(nqueens != NULL);

    return (column >= nqueens->e->num_genes)? 1 : 0;
}
static struct Candidate *
decode(
        struct Individual *cryptic,
        struct NQueens *nqueens
) {
    assert((cryptic != NULL) && (nqueens != NULL));

    int locus;
    int gene;
    int row;
    int column;
    int i;
    struct Candidate *candidate = create_candidate(nqueens);
    /*
        DNA's translation:
    */
    for (gene = 0; gene < nqueens->e->num_genes; gene += 1) {
        /*
            From Genotype (extract genetic info from allele)
        */
        locus = gene * nqueens->e->units_per_gene;
        column = bits2int(cryptic->dna + locus, nqueens->e->units_per_gene);
        /*
            To Phenotype
        */
        row = gene;
        i = gene;
        candidate->queens[i] = create_queen(row, column);
        candidate->loci_junk_alleles[i] = is_junk_allele(column, nqueens);
    }
    return candidate;
}

static double
penalty(
        struct Candidate *candidate,
        struct NQueens *nqueens
) {
    assert((candidate != NULL) && (nqueens != NULL));

    double attacks = 0.0;
    double illegals = 0.0;
    int at;
    int next;
    /*
        Count illegal alleles
    */
    for (at = 0; at < nqueens->e->num_genes; at += 1) {
        if (candidate->loci_junk_alleles[at]) {
            illegals += 1.0;
        }
    }
    /*
        Count attacks just against queens ahead to avoid repeated checks
        (if A attacks B, B also attacks A), only if legal
    */
    for (at = 0; at < nqueens->e->num_genes - 1; at += 1) {
        for (next = at + 1; next < nqueens->e->num_genes; next += 1) {
            if (!candidate->loci_junk_alleles[at]
                && !candidate->loci_junk_alleles[next]
                && attack(candidate->queens[at], candidate->queens[next])) {
                    attacks += 1.0;
            }
        }
    }
    return attacks + illegals;
}

static double
objective(
        struct Candidate *candidate,
        struct NQueens *nqueens
) {
    assert((candidate != NULL) && (nqueens != NULL));

    return (((double)(nqueens->e->num_genes) - penalty(candidate, nqueens))
            / (double)(nqueens->e->num_genes));
}
