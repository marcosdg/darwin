/*  result.c

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
    Writer for darwin's execution results.
*/
/*
    #included

    <stdio.h> fprintf, fclose, fopen, NULL
    <stdlib.h> free
    <string.h> strcpy, strlen
    "../base/report.h" <stdio.h>, <stdlib>
    "../base/xmem.h" xmalloc
    "result.h" "../life.h"
*/
#include <assert.h>
#include <string.h>
#include "../base/report.h"
#include "../base/xmem.h"
#include "result.h"

static const char *default_result_basename = "results.csv";


#define DARWIN_DEFINE_FUNC_BEST_PHENOTYPE(T, problem)                   \
char *                                                                  \
best_phenotype(                                                         \
        struct T *problem,                                              \
        struct Population *city                                         \
) {                                                                     \
    assert(problem != NULL);                                            \
    assert(city != NULL);                                               \
                                                                        \
    char *best_phenotype;                                               \
    struct Individual *alpha;                                           \
    struct T##_candidate *candidate_alpha;                              \
    int next;                                                           \
                                                                        \
    alpha = city->people[0];                                            \
    for (next = 1; next < city->current_size; next += 1) {              \
        if (city->people[next]->fitness > alpha->fitness) {             \
            alpha = city->people[next];                                 \
        }                                                               \
    }                                                                   \
    candidate_alpha = (*problem->decode)(alpha, problem);               \
    best_phenotype = (*problem->candidate_to_string)(candidate_alpha);  \
    destroy_##problem##_candidate(candidate_alpha);                     \
                                                                        \
    return best_phenotype;                                              \
}
#include "result-generic-defs.h"
#undef DARWIN_DEFINE_FUNC_BEST_PHENOTYPE

void
write_result_csv(
        struct Evolution_state *end_state,
        const char *problem_filename,
        const char *result_dirname,
        char *best_phenotype
) {
    FILE *file;
    char *result_filename;

    if (result_dirname == NULL) {
        DARWIN_ERROR("Bad result directory");
    }
    result_filename = xmalloc(strlen(result_dirname)
                                + strlen(default_result_basename) + 1);
    strcpy(result_filename, result_dirname);
    strcat(result_filename, default_result_basename);
    file = fopen(result_filename, "w+");
    if (file == NULL) {
        free(result_filename);
        DARWIN_ERROR("Could not create results file");
    }

    fprintf(file, "PROBLEM INSTANCE; %s\n", problem_filename);
    fprintf(file, "GENERATIONS ELAPSED; %i\n", end_state->generation);
    fprintf(file, "AVERAGE FITNESS; %lf\n", end_state->avg_fitness);
    fprintf(file, "BEST FITNESS EVER (at generation); %lf (%i)\n",
            end_state->best_fitness_ever, end_state->best_fitness_generation);
    fprintf(file, "WORST FITNESS EVER (at generation); %lf (%i)\n",
            end_state->worst_fitness_ever, end_state->worst_fitness_generation);
    if (best_phenotype != NULL) {
        fprintf(file, "BEST INDIVIDUAL; %s\n", best_phenotype);
    }
    free(result_filename);
    fclose(file);
}
