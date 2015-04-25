/*  graph.c

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
#include <assert.h>
#include <stdlib.h>         /* malloc */
#include "../base/report.h"
#include "graph.h"

const int MIN_GRAPH_SIZE = 2; /* a minimum of 2 genes is required for crossover */



struct Graph *
create_graph(
        int **adjacency,
        int size
) {
    assert(adjacency != NULL);
    assert(size >= MIN_GRAPH_SIZE);

    struct Graph *graph = (struct Graph *) malloc(sizeof(struct Graph));
    if (graph == NULL) {
        error("Could not create graph");
    }
    graph->adjacency = adjacency;
    graph->size = size;

    return graph;
}

int
is_vertex(
        int x,
        struct Graph *graph
) {
    assert(graph != NULL);
    return (0 <= x) && (x < graph->size);
}
/*
    is_undirected_edge:

    It checks if both (v1, v2) and (v2, v1) are edges in the given graph; if one
    them fails it means that the edge is directed, and if both fail it means that
    there is no edge. Loops (v1, v1) or (v2, v2) are prohibited.
*/
int
is_undirected_edge(
        int v1,
        int v2,
        struct Graph *graph /* undirected */
) {
    assert(graph != NULL);
    return is_vertex(v1, graph) && is_vertex(v2, graph)
            && (v1 != v2)
            && (graph->adjacency[v1][v2] == 1)
            && (graph->adjacency[v2][v1] == 1);
}
