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
#include <assert.h>
#include <math.h>       /* exp */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc */
#include <string.h>     /* memcpy */
#include "base/report.h"
#include "base/random.h"
#include "genome.h"
#include "operators.h"

/*
    Individual's default mutation probability. It may be later redefined by the
    user via darwin's Genetic Algorithm configuration file.
*/
static double default_mutation_risk = 0.1;

/*
    SELECTION.
*/
/*
    fitness_proportion:
    How much better is 'one' than 'reference'?

    If some has zero or negative fitness is disregarded to avoid possible
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
/*
    fight:
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
    assert(num_rounds >= 1); /* empty tournaments are pointless */

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
    CROSSOVER.
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
    if (offspring == NULL || son == NULL || daughter == NULL) {
        error("Could not create offspring");
    }
    /* X point: to avoid (offspring == parents), then (locus != 0) */

    long int locus = random_int_inclusive(1, (e->dna_length - 1));
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
    MUTATION.

    A mutagen will cause mutations in an individual's DNA depending on the risk
    factor (mutation probability function).
*/

long int
single_point_mutation(
        struct Individual *victim,
        struct Encoding *e
) {
    assert((victim != NULL) && (e != NULL));

    long int locus = random_int_exclusive(0, e->dna_length);
    invert(victim, locus, e);

    return locus;
}

double
constant_mutation_risk(
        struct Individual *victim /* not used but expected by mutagen function */
) {
    return default_mutation_risk;
}
/*
    adaptative_mutation_risk:

    The mutation probability varies according to victim's fitness and evolvability
    (parents' average fitness):
        · Better fitness or evolvability, decreases risk.
        · Worse fitness or evolvability, increases risk.
*/
double
adaptative_mutation_risk(
        struct Individual *victim
) {
    assert(victim != NULL);

    /* Case 1: best fitness (1.0). No mutation. */

    double risk = 0.0;

    /* Case 2: worst fitness. Mutate. */

    if (victim->fitness <= 0.0) {
        risk = 1.0;

    /* Case 3: victim is equal or better than parents. */

    } else if ((victim->fitness < 1.0) && (victim->evolvability >= 1.0)) {
        risk = exp(-(victim->evolvability) * (victim->fitness)) * 0.1;

    /* Case 4: victim is worse. */

    } else if ((victim->fitness < 1.0) && (victim->evolvability < 1.0)) {
        risk = exp(-(victim->evolvability) * (victim->fitness)) * 0.5;
    }
    return risk;
}

int
mutagen(
        double (*risk)(struct Individual *),
        struct Individual *victim,
        struct Encoding *e
) {
    assert((risk != NULL) && (victim != NULL) && (e != NULL));

    int mutated = 0;
    double luck = random_double_inclusive(0.0, 1.0);

    if (luck < (*risk)(victim)) {
        single_point_mutation(victim, e);
        mutated = 1;
    }
    return mutated;
}

/*
    REPLACEMENT.
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
