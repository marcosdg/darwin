/*  subset_sum.c

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
    The Subset-Sum problem (see subset_sum.h for details)
*/
#include <assert.h>
#include <math.h>           /* abs */
#include <stdlib.h>         /* malloc, NULL */
#include <string.h>         /* memset */
#include "../base/report.h"
#include "subset_sum.h"     /* genome.h */

const int MIN_TARGET = 0;
const int MIN_SET_SIZE = 2; /* a minimum of 2 genes is required for crossover */
const int MIN_SUBSET_SIZE = 0;
static int target;
static int *set;

static struct Candidate *
decode(struct Individual *cryptic, struct Subset_sum *subset_sum);

static int
penalty(struct Candidate *candidate, struct Subset_sum *subset_sum);

static double
objective(struct Candidate *candidate, struct Subset_sum *subset_sum);


struct Subset_sum *
create_subset_sum(
        int t,
        int *s,
        int s_size
) {
    assert(t >= MIN_TARGET);
    assert(s_size >= MIN_SET_SIZE);
    assert(s != NULL);

    struct Encoding *e = create_encoding(1, s_size);
    struct Subset_sum *instance = (struct Subset_sum *)
                                    malloc(sizeof(struct Subset_sum));
    if (instance == NULL) {
        error("subset sum: Could not create instance");
    }
    target = t;
    set = s;
    instance->e = e;
    instance->decode = decode;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}
/*
    create_candidate:

    Relies on the 'decode' function to know the size of the subset, so that it can
    avoid allocating more memory than needed.
*/
static struct Candidate *
create_candidate(
        int subset_size,                    /* from decoding stage */
        struct Subset_sum *subset_sum
) {
    assert(subset_size >= MIN_SUBSET_SIZE); /* empty set is a valid subset */
    assert(subset_sum != NULL);

    int *subset = (int *) malloc(subset_size * sizeof(int));
    struct Candidate *candidate = (struct Candidate *)
                                    malloc(sizeof(struct Candidate));
    if (subset == NULL || candidate == NULL) {
        error("subset sum: Could not create candidate");
    }
    memset(subset, 0, subset_sum->e->num_genes * sizeof(int));
    candidate->subset = subset;
    candidate->subset_size = subset_size;

    return candidate;
}

static struct Candidate *
decode(
        struct Individual *cryptic,
        struct Subset_sum *subset_sum
) {
    assert((cryptic != NULL) && (subset_sum != NULL));

    int locus;  /* location in DNA strand */
    int i = 0;  /* location in candidate subset */
    
    int subset_size = 0;
    struct Candidate *candidate;
    for (locus = 0; locus < subset_sum->e->dna_length; locus += 1) {
        if (cryptic->dna[locus] == 1) {
            subset_size += 1;
        }
    }
    candidate = create_candidate(subset_size, subset_sum);
    /*
        DNA translation (dna has the same length as set S)
    */
    for (locus = 0; locus < subset_sum->e->dna_length; locus += 1) {
        if (cryptic->dna[locus] == 1) {
            candidate->subset[i] = set[locus];
            i += 1;
        }
    }
    return candidate;
}

static int
penalty(
        struct Candidate *candidate,
        struct Subset_sum *subset_sum
) {
    assert((candidate != NULL) && (subset_sum != NULL));

    int i;
    int sum = 0;

    if (candidate->subset_size > 0) {
        for (i = 0; i < candidate->subset_size; i += 1) {
            sum += candidate->subset[i];
        }
    }
    return abs(target - sum);
}

static double
objective(
        struct Candidate *candidate,
        struct Subset_sum *subset_sum
) {
    assert((candidate != NULL) && (subset_sum != NULL));

    return (((double) target - penalty(candidate, subset_sum))
            / (double) target);
}
