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
#include <math.h>           /* abs, ceil, exp2, log2 */
#include <stdio.h>
#include <stdlib.h>         /* malloc, NULL */
#include <string.h>         /* memset */
#include "../base/report.h"
#include "../base/bits.h"
#include "nqueens.h"        /* genome.h */

const int MIN_BOARD_SIZE = 4; /* No solutions exist for N=2 and N=3 */

static struct NQueens_candidate *
decode(struct Individual *cryptic, struct NQueens *nqueens);

static void
print(struct NQueens_candidate *candidate);

static int
penalty(struct NQueens_candidate *candidate);

static double
objective(struct NQueens_candidate *candidate);



struct NQueens *
create_nqueens(
        int board_size
) {
    assert(board_size >= MIN_BOARD_SIZE);

    int min_bits = (int) ceil(log2(board_size));
    struct Encoding *e = create_encoding(min_bits, board_size);
    struct NQueens *instance = (struct NQueens *) malloc(sizeof(struct NQueens));
    if (instance == NULL) {
        error("NQueens: Could not create instance");
    }
    instance->e = e;
    instance->print = print;
    instance->decode = decode;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}

static struct NQueens_candidate *
create_nqueens_candidate(
        struct NQueens *nqueens
) {
    assert(nqueens != NULL);

    int *junk_alleles = (int *) malloc(nqueens->e->num_genes * sizeof(int));
    struct Queen **queens = (struct Queen **)
                            malloc(nqueens->e->num_genes * sizeof(struct Queen *));
    struct NQueens_candidate *candidate = (struct NQueens_candidate *)
                                    malloc(sizeof(struct NQueens_candidate));
    if (junk_alleles == NULL || queens == NULL || candidate == NULL) {
        error("NQueens: Could not create candidate");
    }
    memset(junk_alleles, 0, nqueens->e->num_genes * sizeof(int));
    candidate->junk_alleles = junk_alleles;
    candidate->queens = queens;
    candidate->num_queens = nqueens->e->num_genes;

    return candidate;
}

static int
is_junk_allele(
        int column,
        struct NQueens *nqueens
) {
    assert(nqueens != NULL);

    return column >= nqueens->e->num_genes;
}
static struct NQueens_candidate *
decode(
        struct Individual *cryptic,
        struct NQueens *nqueens
) {
    assert(cryptic != NULL);
    assert(nqueens != NULL);

    int locus;
    int gene = 0;
    int row = 0;
    int column;
    int i = 0;
    struct NQueens_candidate *candidate = create_nqueens_candidate(nqueens);
    /*
        DNA's translation:
    */
    do {/*
            from Genotype (extract genetic info from allele)
        */
        locus = gene * nqueens->e->units_per_gene;
        column = bits2int(cryptic->dna + locus, nqueens->e->units_per_gene);
        /*
            to Phenotype
        */
        candidate->queens[i] = create_queen(row, column);
        candidate->junk_alleles[i] = is_junk_allele(column, nqueens);
        i += 1;
        row += 1;
        gene += 1;
    } while (gene < nqueens->e->num_genes);

    return candidate;
}
static void
print(
        struct NQueens_candidate *candidate
) {
    assert(candidate != NULL);

    int i;
    for (i = 0; i < candidate->num_queens; i += 1) {
        printf("Queen %i row %i column %i \n", i, candidate->queens[i]->row,
                candidate->queens[i]->column);
    }
}

static int
penalty(
        struct NQueens_candidate *candidate
) {
    assert(candidate != NULL);

    int attacks = 0;
    int illegals = 0;
    int at;
    int next;
    /*
        Count illegal alleles (queens)
    */
    for (at = 0; at < candidate->num_queens; at += 1) {
        if (candidate->junk_alleles[at]) {
            illegals += 1;
        }
    }
    /*
        Count attacks just against (legal) queens ahead to avoid repeated checks
        (if A attacks B, B also attacks A)
    */
    for (at = 0; at < candidate->num_queens - 1; at += 1) {
        for (next = at + 1; next < candidate->num_queens; next += 1) {
            if (!candidate->junk_alleles[at] && !candidate->junk_alleles[next]
                && attack(candidate->queens[at], candidate->queens[next])) {
                    attacks += 1;
            }
        }
    }
    return attacks + illegals;
}

static double
objective(
        struct NQueens_candidate *candidate
) {
    assert(candidate != NULL);

    return ((double) abs(candidate->num_queens - penalty(candidate)))
            / (double) (candidate->num_queens);
}
