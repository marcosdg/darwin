/*  test_parser_subsetsum.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a
    self-adaptative strategy.

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
    Just to play around.
*/
#include <stdio.h>
#include <stdlib.h>
#include "experiment/io/in/parser_subsetsum.h"

int main(int argc, char **argv)
{
    struct Subsetsum *subsetsum = load_subsetsum(argv[1]);
    printf("subsetsum->e->units_per_gene %i\n", subsetsum->e->units_per_gene);
    printf("subsetsum->e->num_genes %i\n", subsetsum->e->num_genes);
    printf("subsetsum->e->dna_length %i\n", subsetsum->e->dna_length);

    return 0;
}
