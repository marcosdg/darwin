/*  result.h

    This is part of the darwin program.

    darwin. A simple genetic algorithm implementation with an adaptative
    strategy.

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
    Writer for darwin's execution results.
*/
/*
    #included

    "experiment/hampath/hampath.h" "../../genome.h"
    "../life.h" struct Evolution_state, "experiment/hampath/hampath.h"
                "experiment/nqueens/nqueens.h", "experiment/subsetsum/subsetsum.h"
*/
#ifndef RESULT_H_INCLUDED
#define RESULT_H_INCLUDED

#include "../life.h"


#define DARWIN_DECLARE_FUNC_BEST_PHENOTYPE(T, problem)  \
extern char *                                           \
best_phenotype(                                         \
        struct T *problem,                              \
        struct Population *city                         \
);
#include "result-generic-protos.h"
#undef DARWIN_DECLARE_FUNC_BEST_PHENOTYPE

extern void
write_result_csv(
        struct Evolution_state *end_state,
        const char *problem_filename,
        const char *result_dirname,
        char *best_phenotype
);
#endif /* RESULT_H_INCLUDED */
