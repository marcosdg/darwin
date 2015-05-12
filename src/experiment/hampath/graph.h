/*  graph.h

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
    The Hamiltonian Path submodule: basic structures and functions.
    (see hampath.{h, c})
*/
#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
/*
    A graph G is a pair (V, E) where V is the set of vertices,
                V = {v1, v2, ..., vn} (n: number of vertices)
    which will be tagged consecutively with positive integer numbers
    {0, 1, 2, ..., n} to facilitate the genotypic encoding (see hampath.h); and E
    is the set of edges,
                E = {e1, e2, ..., em} (m: number of edges)
    indicating which vertex is connected to which vertices. Both, V and E, are
    encoded by means of the adjacency matrix. The size of G will be taken as the
    number of vertices.
*/
struct Graph {
    int **adjacency;
    int size;
};

extern struct Graph *
create_graph(
        int **adjacency,
        int size
);

extern int
is_vertex(
        int v,
        struct Graph *graph
);

extern int
is_undirected_edge(
        int v1,
        int v2,
        struct Graph *graph /* undirected */
);
#endif /* GRAPH_H_INCLUDED */
