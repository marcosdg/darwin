/*  operators.c

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
    operators.{h,c} implement the 4 basic evolutional operations of Genetic
    Algorithms:
        1. Selection: which individuals will produce new individuals?
            (Fitness-proportioned Tournament Selection)
        2. Crossover: maiting between selected individuals.
            (Single Point Crossover)
        3. Mutation: individuals' DNA alterations.
            (Single Point Mutation)
        4. Replacement: which individuals persist between generations.
            (Replace Worst Individual)
*/
#include "operators.h"


/*
    Selection.
*/

/*  fitness_proportion:
    How much better is 'one' than 'reference'?

    If one has zero or negative fitness is disregarded to avoid possible
    divisions by zero or misleading results. In which case, tournament
    selection will behave 'determinalistically', as this function decides
    who is likely to be selected.
*/
static double
fitness_proportion(
        struct Individual *one,
        struct Individual *reference
) {
    assert((one != NULL) && (reference != NULL));

    if (one->fitness <= 0.0) { /* reference is the best */
        return 0.0;
    } else if (reference->fitness <= 0.0) { /* one is the best */
        return 1.0;
    }
    return one->fitness / (one->fitness + reference->fitness);
}
/*  fight:
    Returns 'one' if rival wins, 'zero' if aspirant wins.

    It is represented by a Bernoulli probability distribution, being 'goodness'
    the aspirant's probability of winning and (1 - goodness) the probability of
    loosing. The higher the goodness, the harder to loose.
*/
static int
fight(
        struct Individual *aspirant,
        struct Individual *rival
) {
    assert((aspirant != NULL) && (rival != NULL));

    double goodness = fitness_proportion(aspirant, rival);
    double bad_luck = random_double_inclusive(0.0, 1.0);

    return bad_luck > goodness? 1 : 0;
}

struct Individual *
tournament_selection(
        struct Population *city,
        int num_rounds
) {
    assert(city != NULL);
    assert(num_rounds >= 1); /* zero rounds means zero rivals */

    struct Individual *best = pick_random_individual(city);
    struct Individual *rival;
    int round;

    for (round = 1; round <= num_rounds; round += 1) {
        rival = pick_random_individual(city);

        /* rival wins ? */
        if(fight(best, rival)) {
            best = rival;
        }
    }
    return best;
}

/*
    Crossver.
*/

struct Individual **
single_point_crossover(
        struct Individual *dad,
        struct Individual *mom,
        struct Encoding *e
) {
    assert((dad != NULL) && (mom != NULL) && (e != NULL));

    struct Individual **offspring = (struct Individual **)
                                    malloc(2 * sizeof(struct Individual *));
    struct Individual *son = create_individual(e);
    struct Individual *daughter = create_individual(e);
    if (!offspring || !son || !daughter) {
        ERROR_VERBOSE("Could not create offspring");
    }
    /* X point: to avoid (offspring == parents), then (locus != 0) */

    long int locus = random_in_range_inclusive(1, (e->dna_length - 1));
    int fst_half = locus * UNIT_BYTE_SIZE;
    int snd_half = e->dna_byte_size - fst_half;

    /* Transfer genetic material. */

    memcpy(son->dna, dad->dna, fst_half);
    memcpy((son->dna + locus), (mom->dna + locus), snd_half);
    memcpy(daughter->dna, mom->dna, fst_half);
    memcpy((daughter->dna + locus), (dad->dna + locus), snd_half);

    offspring[0] = son;
    offspring[1] = daughter;
    return offspring;
}

/*
    Mutation.
*/

long int
single_point_mutation(
        struct Individual *victim,
        struct Encoding *e
) {
    assert ((victim != NULL) && (e != NULL));

    long int locus = random_in_range_exclusive(0, e->dna_length);
    invert(victim, locus, e);

    return locus;
}
/*
int
adaptative_mutation(
        struct population *pop,
        double (*mutation_probability_function)(struct *individual)
) {
    int i, r;

    for (i = 0; i < pop->current_size; i += 1) {
        r = random_in_range(0, 10);
        if (r < (*mutation_probability_function)(pop->individuals[i]) * 10) {
            single_point_mutation(pop->individuals[i]);
        }
    }
}
*/

/*
    Replacement.
*/

int
replace_worst(
        struct Individual *incomer,
        struct Population *city
) {
    assert((incomer != NULL) && (city != NULL));
    assert(city->current_size > 0);

    int replaced = 0;
    int worst = 0;
    int next;

    for (next = 1; next <= (city->current_size - 1); next += 1) {
        if (city->people[next]->fitness
            < city->people[worst]->fitness) {
            worst = next;
        }
    }
    if (incomer->fitness > city->people[worst]->fitness) {
        city->people[worst] = incomer;
        replaced = 1;
    }
    return replaced;
}

