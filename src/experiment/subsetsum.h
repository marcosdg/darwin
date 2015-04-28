/*  subset_sum.h

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
    The Subset-Sum problem
    ----------------------

    An instance of the Subset-Sum problem is a pair (S, t), where S is a set of
    positive integers and t, the target, is also positive integer. The problem
    consists in determining whether S has a subset such that its sum is t.

    The genetic approach
    --------------------

    There are 5 essential elements we need to define:
        (1) Genotype representation
        (2) Phenotype representation
        (3) Decoding function
        (4) Penalty/Cost function
        (5) Objective function

    (1) Genotype representation:

        · Gene locus: the integer's position in the given set
        · Gene value (allele): '1' or '0' representing, respectively, whether the
                                integer at that locus is selected or not
        · Allele length: 1 (the only admitted values are '0' or '1')
        · DNA length: number of elements in S

    (2) Phenotype representation:

        The numbers of the given set selected by an individual's genotype.

    Example:
        S = {1, 5, 4, 7}

        An individual's genotype might be '0110', thus its equivalent phenotype
        is {5, 4}.

    (3) Decoding function:

        Returns the integers selected from the input set S.

    (4) Penalty/Cost function:

        Helps separate "good" candidate solutions from "bad" ones.

        Although darwin may generate alleles which do not belong to the problem
        instance's domain (as happens in the N-Queens problem), it is the
        specific genotypic representation here chosen that prevents it from
        happening. The reason behind is that, by restricting the allele length to
        be '1', is impossible for darwin to generate numbers other than '0' or '1'.
        In other words, there are no illegal alleles.

        Hence, in this case, the penalty function will only penalize individuals
        which are not a solution: those whose sum exceed or fall behind the
        target number.

            penalty = abs(target - candidate's sum)

    (5) Objective function:

        It is the function to be optimized and represents the nature of the
        problem. By contrast, the fitness function measures the quality or
        goodness of the elements in the objective function's domain space;
        though, for many problems (as in here) both the objective and fitness
        functions match:

            fitness === objective = (|S| - penalty)
                                    / |S|
        where |S| is the number of elements in S.
*/
#ifndef SUBSETSUM_H_INCLUDED
#define SUBSETSUM_H_INCLUDED

#include "../genome.h"


struct Subsetsum_candidate {
    int *subset;
    int subset_size;
};

struct Subsetsum {
    struct Encoding *e;

    struct Subsetsum_candidate *
    (*decode)(struct Individual *cryptic, struct Subsetsum *subsetsum);

    void
    (*print)(struct Subsetsum_candidate *candidate);

    int
    (*penalty)(struct Subsetsum_candidate *candidate);

    double
    (*objective)(struct Subsetsum_candidate *candidate);
};

extern struct Subsetsum *
create_subsetsum(
        int t,
        int *s,
        int s_size
);
#endif /* SUBSETSUM_H_INCLUDED */
