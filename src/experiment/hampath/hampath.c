/*  hampath.c

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
    The Hamiltonian Path problem (undirected version) (see hampath.h for details)
*/
/*
    #includes

    <math.h> ceil, log2
    <stdio.h> NULL, printf
    <stdlib.h> free
    <string.h> memset
    "../../base/xmem.h" xmalloc
    "../../base/bits.h" bits2int
    "hampath.h" genome.h
*/
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../base/xmem.h"
#include "../../base/bits.h"
#include "hampath.h"

static struct Graph *graph;

static struct Hampath_candidate *
decode(struct Individual *cryptic, struct Hampath *hampath);

static void
print(struct Hampath_candidate *candidate);

static int
penalty(struct Hampath_candidate *candidate);

static double
objective(struct Hampath_candidate *candidate);



struct Hampath *
create_hampath(
        struct Graph *g
) {
    assert(g != NULL);

    int min_bits = (int) ceil(log2(g->size));
    struct Encoding *e = create_encoding(min_bits /* units_per_gene */,
                                         g->size  /* dna_length */);
    struct Hampath *instance = xmalloc(sizeof(struct Hampath));
    graph = g;
    instance->e = e;
    instance->decode = decode;
    instance->print = print;
    instance->penalty = penalty;
    instance->objective = objective;

    return instance;
}
int
destroy_hampath(
        struct Hampath *hampath
) {
    int destroyed = 0;
    if (hampath != NULL) {
        destroy_graph(graph);
        free(hampath);
        destroyed = 1;
    }
    return destroyed;
}

static struct Hampath_candidate *
create_hampath_candidate(
        struct Hampath *hampath
) {
    assert(hampath != NULL);

    int *path = xmalloc(hampath->e->num_genes * sizeof(int));
    struct Hampath_candidate *candidate = xmalloc(sizeof(struct Hampath_candidate));
    candidate->path = path;

    return candidate;
}
int
destroy_hampath_candidate(
        struct Hampath_candidate *candidate
) {
    int destroyed = 0;
    if (candidate != NULL) {
        free(candidate->path);
        free(candidate);
        destroyed = 1;
    }
    return destroyed;
}

static struct Hampath_candidate *
decode(
        struct Individual *cryptic,
        struct Hampath *hampath
) {
    assert(cryptic != NULL);
    assert(hampath != NULL);

    int locus;
    int gene = 0;
    int i = 0;
    int vertex;
    struct Hampath_candidate *candidate = create_hampath_candidate(hampath);
    /*
        DNA's translation:
    */
    do {/*
            from Genotype (extract genetic info from allele)
        */
        locus = gene * hampath->e->units_per_gene;
        vertex = bits2int(cryptic->dna + locus, hampath->e->units_per_gene);
        /*
            to Phenotype
        */
        candidate->path[i] = vertex;
        i += 1;
        gene += 1;
    } while (gene < hampath->e->num_genes);
    return candidate;
}
static void
print(
        struct Hampath_candidate *candidate
) {
    assert(candidate != NULL);
    assert(graph != NULL);

    int i;

    printf("start> ");
    for (i = 0; i < graph->size; i += 1) {
        printf("%i ", candidate->path[i]);
    }
    printf("<end\n");
}

static int *
create_visited(
        void
) {
    assert(graph != NULL);

    int *visited = xmalloc(graph->size * sizeof(int));
    /*
        Should not be initialized to zero, since zero is a valid node.
    */
    memset(visited, -1, graph->size * sizeof(int));

    return visited;
}
static int
was_visited(
        int v,
        int *visited
) {
    assert(visited != NULL);
    assert(graph != NULL);

    int was = 0;
    int i;

    for (i = 0; i < graph->size; i += 1) {
        if (visited[i] == v) {
            was = 1;
            break;
        }
    }
    return was;
}
static int
penalty(
       struct Hampath_candidate *candidate
) {
    assert(candidate != NULL);
    assert(graph != NULL);

    int at = 0;
    int next = 1;
    int illegals = 0;
    int *visited = create_visited();
    visited[0] = candidate->path[at];

    do {
        if (!is_undirected_edge(candidate->path[at], candidate->path[next], graph)
            || was_visited(candidate->path[next], visited)) {
                illegals += 1;
        }
        visited[next] = candidate->path[next];
        at += 1;
        next += 1;
    } while (at < graph->size - 1);
    free(visited);

    return illegals;
}

static double
objective(
        struct Hampath_candidate *candidate
) {
    assert(candidate != NULL);
    assert(graph != NULL);
    /*
        num_path_edges - penalty / num_path_edges
    */
    return ((double) ((graph->size - 1) - penalty(candidate)))
            / (double) (graph->size - 1);
}
