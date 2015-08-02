/*  subset_sum.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
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
    The Subset-Sum problem (see subset_sum.h for details)
*/
/*
    #included

    <stdlib.h> abs, free, NULL
    <string.h> memset
    "../../base/xmem.h" xmalloc
    "../../base/bits.h" itods
    "../../base/darwin_limits.h" MAX_INT32_STRLEN
    "subsetsum.h" "../../genome.h"
*/
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../../base/xmem.h"
#include "../../base/bits.h"
#include "../../base/darwin_limits.h"
#include "subsetsum.h"

static const int MIN_TARGET = 0;
/*
    MIN_SET_SIZE:
    Cross-over requires at least 2 genes.
*/
static const int MIN_SET_SIZE = 2;
static const int MIN_SUBSET_SIZE = 0;
static int target;
static int *set;

static struct Subsetsum_candidate *
decode(struct Individual *cryptic, struct Subsetsum *subsetsum);

static char *
candidate_to_string(struct Subsetsum_candidate *candidate);

static int
penalty(struct Subsetsum_candidate *candidate);

static double
objective(struct Subsetsum_candidate *candidate);


struct Subsetsum *
create_subsetsum(
        int t,
        int *s,
        int s_size
) {
    assert(t >= MIN_TARGET);
    assert(t <= MAX_INT);
    assert(s_size >= MIN_SET_SIZE);
    assert(s != NULL);

    struct Encoding *e = create_encoding(1      /* units_per_gene */,
                                         s_size /* dna_length */);
    struct Subsetsum *instance = xmalloc(sizeof(struct Subsetsum));
    char *max_int_str;
    target = t;
    set = s;
    instance->e = e;
    instance->decode = decode;
    instance->candidate_to_string = candidate_to_string;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}
int
destroy_subsetsum(
        struct Subsetsum *subsetsum
) {
    int destroyed = 0;
    if (subsetsum != NULL) {
        free(set);
        free(subsetsum);
        destroyed = 1;
    }
    return destroyed;
}

int
subsetsum_min_target(
        void
) {
    return MIN_TARGET;
}
int
subsetsum_min_set_size(
        void
) {
    return MIN_SET_SIZE;
}
/*
    create_subsetsum_candidate:

    Relies on the 'decode' function to know the size of the subset, so that it
    can avoid allocating more memory than needed.
*/
static struct Subsetsum_candidate *
create_subsetsum_candidate(
        int subset_size,                    /* from decoding stage */
        struct Subsetsum *subsetsum
) {
    assert(subset_size >= MIN_SUBSET_SIZE); /* empty set is a valid subset */
    assert(subsetsum != NULL);

    int *subset = xmalloc(subset_size * sizeof(int));
    struct Subsetsum_candidate *candidate = xmalloc(sizeof(struct Subsetsum_candidate));

    memset(subset, 0, subset_size * sizeof(int));
    candidate->subset = subset;
    candidate->subset_size = subset_size;

    return candidate;
}
int
destroy_subsetsum_candidate(
        struct Subsetsum_candidate *candidate
) {
    int destroyed = 0;
    if (candidate != NULL) {
        free(candidate->subset);
        free(candidate);
        destroyed = 1;
    }
    return destroyed;
}

static struct Subsetsum_candidate *
decode(
        struct Individual *cryptic,
        struct Subsetsum *subsetsum
) {
    assert(cryptic != NULL);
    assert(subsetsum != NULL);

    int locus;  /* location in DNA strand */
    int i = 0;  /* location in candidate subset */

    int subset_size = 0;
    struct Subsetsum_candidate *candidate;
    for (locus = 0; locus < subsetsum->e->dna_length; locus += 1) {
        if (cryptic->dna[locus] == 1) {
            subset_size += 1;
        }
    }
    candidate = create_subsetsum_candidate(subset_size, subsetsum);
    /*
        DNA translation (dna has the same length as set S)
    */
    for (locus = 0; locus < subsetsum->e->dna_length; locus += 1) {
        if (cryptic->dna[locus] == 1) {
            candidate->subset[i] = set[locus];
            i += 1;
        }
    }
    return candidate;
}

static char *
candidate_to_string(
        struct Subsetsum_candidate *candidate
) {
    char *str;
    char *num_str;
    char *max_int_str;
    int braces = 2 * sizeof(char); /* {} */
    int space = sizeof(char);
    int str_bytes;
    int i;

    if (candidate == NULL) {
        return "";
    }
    /*
        Allocate enough bytes to hold the largest possible 32 bits int inside
        'str'.
    */
    str_bytes = braces + space
                + ((MAX_INT32_STRLEN + space) * candidate->subset_size);
    str = xmalloc(str_bytes * sizeof(char)) ;

    strcpy(str, "{ ");
    for (i = 0; i < candidate->subset_size ; i += 1) {
        num_str = itods(candidate->subset[i]);
        strcat(str, num_str);
        strcat(str, " ");
        free(num_str);
    }
    strcat(str, "}");
    return str;
}

static int
penalty(
        struct Subsetsum_candidate *candidate
) {
    assert(candidate != NULL);

    int i;
    int sum = 0;

    for (i = 0; i < candidate->subset_size; i += 1) {
        sum += candidate->subset[i];
    }
    return abs(target - sum);
}

static double
objective(
        struct Subsetsum_candidate *candidate
) {
    assert(candidate != NULL);

    return (double) target / (double) (target + penalty(candidate));
}
