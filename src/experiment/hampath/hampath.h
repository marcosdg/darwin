/*  hampath.h

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
    The Hamiltonian Path problem (undirected version)
    -------------------------------------------------

    Given an undirected graph determine whether such graph has a path which
    visits each vertex exactly once.

    The genetic approach
    --------------------

    There are 5 essential elements we need to define:
        (1) Genotype representation
        (2) Phenotype representation
        (3) Decoding function
        (4) Penalty/Cost function
        (5) Objective function

    (1) Genotype representation:

        · Gene locus: vertex's position in the path
        · Gene value (allele): the visited vertex
        · Allele's length: minimum number of bits required to encode the number
                            of vertices: ceil(log2(graph size))
        · DNA length: number of vertices

        Unfortunately, a binary coding scheme may lead to individuals with
        illegal or 'junk' alleles; illegal in the sense that they are
        values not considered in the problem domain for a particular instance.

    (2) Phenotype representation:

        The sequence of visited vertices (path).

    Example:
        Graph G:    0       1
                    o-------o
                    |       |
                    |       |
                    o-------o
                    2       3
        adjacency = {{0, 1, 1. 0},
                     {1, 0, 0, 1},
                     {1, 0, 0, 1},
                     {0, 1, 1, 0}}

        An individual's dna might be "10-00-01-11", which is equivalent to
        {2, 0, 1, 3} and is a hamiltonian path. Another might be "10-01-10-11"
        which is a path but not hamiltonian.

    (3) Decoding function:

        Returns the list of nodes (path) encoded in the DNA strand.

    (4) Penalty/Cost function:

        Helps separate "good" candidate solutions from "bad" ones.

        Penalizes paths containing edges that do not belong to the given graph
        (possibly due to illegal alleles) or edges which have one of its vertices
        already visited.

            penalty = illegal edges + edges with vertices visited

    (5) Objective function:

        It is the function to be optimized and represents the nature of the
        problem. By contrast, the fitness function measures the quality or
        goodness of the elements in the objective function's domain space;
        though, for many problems (as in here) both the objective and fitness
        functions match:

            fitness === objective = (path_length - penalty)
                                    / path_length
        where
            path_length === num. of edges in the path === num. of vertices - 1
*
*/
#ifndef HAMPATH_H_INCLUDED
#define HAMPATH_H_INCLUDED

#include "../../genome.h"
#include "graph.h"

struct Hampath_candidate {
    int *path;
};

struct Hampath {
    struct Encoding *e;

    struct Hampath_candidate *
    (*decode)(struct Individual *cryptic, struct Hampath *hampath);

    void
    (*print)(struct Hampath_candidate *candidate);

    int
    (*penalty)(struct Hampath_candidate *candidate);

    double
    (*objective)(struct Hampath_candidate *candidate);
};

extern struct Hampath *
create_hampath(
        struct Graph *graph
);
#endif /* HAMPATH_H_INCLUDED */
