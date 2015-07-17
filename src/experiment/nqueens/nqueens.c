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
/*
    #included

    <math.h> ceil, log2
    <stdlib> free, NULL
    <string.h> memset, strcat, strlen
    "../../base/xmem.h" xmalloc
    "../../base/bits.h" bits_to_int, itods
    "nqueens.h" "../../genome.h"
*/
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../../base/xmem.h"
#include "../../base/bits.h"
#include "nqueens.h" 

static const int MIN_BOARD_SIZE = 4; /* No solutions exist for N=2 and N=3 */

static struct NQueens_candidate *
decode(struct Individual *cryptic, struct NQueens *nqueens);

static char *
candidate_to_string(struct NQueens_candidate *candidate);

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
    struct NQueens *instance = xmalloc(sizeof(struct NQueens));

    instance->e = e;
    instance->candidate_to_string = candidate_to_string;
    instance->decode = decode;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}
int
destroy_nqueens(
        struct NQueens *nqueens
) {
    int destroyed = 0;
    if (nqueens != NULL) {
        free(nqueens);
        destroyed = 1;
    }
    return destroyed;
}

int
nqueens_min_board_size(
        void
) {
    return MIN_BOARD_SIZE;
}

static struct NQueens_candidate *
create_nqueens_candidate(
        struct NQueens *nqueens
) {
    assert(nqueens != NULL);

    int *junk_alleles = xmalloc(nqueens->e->num_genes * sizeof(int));
    struct Queen **queens = xmalloc(nqueens->e->num_genes * sizeof(struct Queen *));
    struct NQueens_candidate *candidate = xmalloc(sizeof(struct NQueens_candidate));

    memset(junk_alleles, 0, nqueens->e->num_genes * sizeof(int));
    candidate->junk_alleles = junk_alleles;
    candidate->queens = queens;
    candidate->num_queens = nqueens->e->num_genes;

    return candidate;
}
int
destroy_nqueens_candidate(
        struct NQueens_candidate *candidate
) {
    int destroyed = 0;
    int i;
    if (candidate != NULL) {
        for (i = 0; i < candidate->num_queens; i += 1) {
            destroy_queen(candidate->queens[i]);
        }
        free(candidate->queens);
        free(candidate->junk_alleles);
        free(candidate);
        destroyed = 1;
    }
    return destroyed;
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
    int column;
    int gene = 0;
    int row = 0;
    int i = 0;
    struct NQueens_candidate *candidate = create_nqueens_candidate(nqueens);
    /*
        DNA's translation:
    */
    do {/*
            from Genotype (extract genetic info from allele)
        */
        locus = gene * nqueens->e->units_per_gene;
        column = bits_to_int(cryptic->dna + locus, nqueens->e->units_per_gene);
        /*
            to Phenotype
        */
        candidate->queens[i] = create_queen(row, column);
        candidate->junk_alleles[i] = is_junk_allele(column, nqueens);
        gene += 1;
        row += 1;
        i += 1;
    } while (gene < nqueens->e->num_genes);

    return candidate;
}
/*
    candidate_to_string:

    format: {(row r{0}, column c{0}) ... (r{i}, c{i}) ... (r{n-1}, c{n-1})}
    where
        0 <= i <= n - 1
        'n' Natural number: num queens == num rows == num columns
*/
static char *
candidate_to_string(
        struct NQueens_candidate *candidate
) {
    char *str;
    char *r_str;
    char *c_str;
    int arity = 2;
    int braces = 3; /* '{' <space> '}' */
    int num_delims = 4; /* '(' ',' ')' <space> */
    int str_bytes;
    int i;

    if (candidate == NULL) {
        return "";
    }
    str_bytes = (((arity * sizeof(int)) + num_delims) * candidate->num_queens) + braces;
    str = xmalloc(str_bytes * sizeof(char));

    strcpy(str, "{ ");
    for (i = 0; i < candidate->num_queens ; i += 1) {
        strcat(str, "(");
        r_str = itods(candidate->queens[i]->row);
        strcat(str, r_str);
        strcat(str, ",");

        c_str = itods(candidate->queens[i]->column);
        strcat(str, c_str);
        strcat(str, ")");

        strcat(str, " ");
        free(r_str);
        free(c_str);
    }
    strcat(str, "}");
    return str;
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

    return (double) candidate->num_queens
            / (double) (candidate->num_queens + penalty(candidate));
}
