/*  darwin.c

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with a
    self-adaptative strategy.

    Copyright (C) 2015 Marcos Diez García <marcos.diez.garcia@gmail.com>

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
    darwin.
*/
/*
    #included

    <stdlib.h> free
    "hampath.h" "../../genome.h", load_hampath
    "nqueens.h" load_nqueens
    "subsetsum" load_subsetsum
    "life.h" "experiment/hampath/hampath.h", "experiment/nqueens/nqueens.h",
             "experiment/subsetsum/subsetsum.h", apocalypse, get_evol_state,
             live
    "experiment/hampath/parser_hampath.h" "hampath.h"
    "experiment/nqueens/parser_nqueens.h" "nqueens.h"
    "experiment/subsetsum/parser_subsetsum.h" "subsetsum.h"
    "experiment/parser_evolution.h" "../life.h", load_evolution
    "out/result.h" best_phenotype, write_result_csv
*/
#include <stdlib.h>
#include "experiment/hampath/parser_hampath.h"
#include "experiment/nqueens/parser_nqueens.h"
#include "experiment/subsetsum/parser_subsetsum.h"
#include "experiment/parser_evolution.h"
#include "out/result.h"


#define DARWIN_DEFINE_FUNC_RUN(T, problem)                                  \
void                                                                        \
run(                                                                        \
        char *evolution_filename,                                           \
        char *problem##_filename,                                           \
        char *result_dirname                                                \
) {                                                                         \
    struct Evolution *evol = load_evolution(evolution_filename);            \
    struct T *problem = load_##problem(problem##_filename);                 \
    struct Population *city = live(evol, problem);                          \
                                                                            \
    struct Evolution_state *end_state = get_evol_state();                   \
    char *alpha = best_phenotype(problem, city);                            \
    write_result_csv(end_state, problem##_filename, result_dirname, alpha); \
                                                                            \
    free(alpha);                                                            \
    destroy_##problem(problem);                                             \
    apocalypse(evol, city);                                                 \
}
#include "darwin-generic-defs.h"
#undef DARWIN_DEFINE_FUNC_RUN


int main(int argc, char **argv)
{
    run(argv[1], argv[2], argv[3]);

    return 0;
}
