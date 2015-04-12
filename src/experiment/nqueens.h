/*  nqueens.h

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
    The N-Queens problem
    --------------------

    Given a NxN matrix (board) and N queens, find the arrangement(s) of the
    queens such that none of them attack each other. A queen attacks another
    queen if both are in the same row, column, or diagonal.

    Observations
    ------------

    One important insight is that for each row (or column) only one queen will be
    placed. Taking this into account allow us to reduce complexity, as once we
    place one queen we do not have to consider again that row or column for the
    next queen. Indeed, we are recursively reducing the number of rows or columns
    by 1 each time we place a queen.

    Secondly, no solutions exist for board sizes equal to 2 or 3 so Darwin omits
    them as well as the trivial case of 1.

    The genetic approach
    --------------------

    There are 5 essential elements we need to define:
        (1) Genotype representation
        (2) Phenotype representation
        (3) Decoding function
        (4) Penalty/Cost function
        (3) Objective function

    (1) Genotype representation:

        · Gene locus: the row at which the queen is placed.
        · Gene value (allele): the column at which the queen is placed.

        It is trivial to see that, under this representation, we have implicitly
        encoded the aforementioned observation, since each locus is unique.
        Similarly, the analogous representation in which we consider the gene
        locus to be the columns, works as well.

    (2) Phenotype representation:

        The list of queens equivalent to the Genotype representation.

    (3) Decoding function:

        Essentially, translates a number in base 2 (binary) to base 10 (decimal)

    (4) Penalty/Cost function:

        Helps to separate "good" candidate solutions from "bad" ones.

        Darwin may generate alleles which do not belong to the problem instance's
        domain. The penalty function will be used to penalize not just individuals
        who are not a solution, but individuals with illegal alleles.

            penalty = number of attacking queens + number of illegal alleles

    (5) Objective function:

        It is the function to be optimized and represents the nature of the
        problem. By contrast, the fitness function measures the quality or
        goodness of the elements in the objective function's domain space;
        though, for many problems (as in here) both the objective and fitness
        functions match:

            fitness === objective = (N - penalty)
                                    / N
        where N is the total number of queens.
*/
#ifndef NQUEENS_H_INCLUDED
#define NQUEENS_H_INCLUDED

#include "../genome.h"
#include "queen.h"


struct Candidate {
    struct Queen **queens;
    /*
        The binary encoding rises the problem of illegal (or 'junk') alleles
        being produced in an individual. They are illegal in the sense that they
        are values not considered in the problem domain for a particular instance.
        Thus, loci_junk_alleles will be used in the decoding stage to store
        positions of illegal alleles as it is needed to evaluate solutions.
    */
    int *loci_junk_alleles;
};

struct NQueens {
    struct Encoding *e;

    struct Candidate *
    (*decode)(struct Individual *cryptic, struct NQueens *nqueens);

    double
    (*penalty)(struct Candidate *candidate, struct NQueens *nqueens);

    double
    (*objective)(struct Candidate *candidate, struct NQueens *nqueens);
};

extern struct NQueens *
create_instance(
        int board_size
);
#endif /* NQUEENS_H_INCLUDED */
