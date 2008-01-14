/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdbool.h>
#include <stdlib.h>

#include "population.h"
#include "environment.h"
#include "utils.h"



int selection(const gsl_rng *const rng, population_t *pop, population_t *selected)
{
    return rws(rng, pop, selected);
}


int mutate(const gsl_rng *const rng, double rate, population_t *pop)
{
    unsigned short *gray_code;
    int i, j;
    double u;
    bool isConverted;


    if ((gray_code = calloc(pop->bits, sizeof(unsigned short))) == NULL) {
        return GA_MALLOC_UNSUCCESSFUL;
    }

    for (i = 0; i < pop->size; ++i) {
        isConverted = false;

        for (j = 0; j < pop->bits; ++j) {
            /* mutate a single bit */
            u = gsl_rng_uniform(rng);

            /* if the random number is smaller than the mutation rate */
            if (u <= rate) {
                /* lazy convert the binary chromosome to the gray representation */
                if (!isConverted) {
                    binarytogray((pop->individuals[i].allele + pop->bits - 1),
                                 (gray_code + pop->bits - 1),
                                 pop->bits);
                    isConverted = true;
                }

                /* flip the bit */
                gray_code[j] = gray_code[j] ^ 1;
            }
        }

        /* if the chromosome was converted, convert it back into binary */
        if (isConverted) {
            graytobinary((pop->individuals[i].allele + pop->bits - 1),
                         (gray_code + pop->bits - 1),
                         pop->bits);
        }
    }

    if (gray_code != NULL) {
//        free(gray_code);
    }

    return 0;
}


int recombine(const gsl_rng *const rng, population_t *new)
{
    return onePointCrossover(rng, new);
}


int onePointCrossover(const gsl_rng *const rng, population_t *new)
{
    int i, j;
    int cut_off;
    unsigned short temp;

    for (i = 0; i < (new->size - 1); i += 2) {
        /* the cross-over point has to be between 1 and bits-1,
           otherwise there won't be a cross over at all. */
        cut_off = gsl_rng_uniform_int(rng, new->bits - 2) + 1;

        for (j = cut_off; j < new->bits; ++j) {
            temp = (new->individuals[i]).allele[j];
            (new->individuals[i]).allele[j] = (new->individuals[i + 1]).allele[j];
            (new->individuals[i + 1]).allele[j] = temp;
        }
    }

    return 0;
}


int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int))
{
    int i;

    for (i = 0; i < pop->size; ++i) {
        (pop->individuals[i]).fitness = fitnessFuncPtr(
            (pop->individuals[i]).allele, pop->bits);
    }

    return 0;
}

double cumulativeFitness(population_t *pop)
{
    double cumulative_fitness;
    int i;

    cumulative_fitness = 0.0;

    for (i = 0; i < pop->size; ++i) {
        cumulative_fitness += (pop->individuals[i]).fitness;
    }

    return cumulative_fitness;
}

int rws(const gsl_rng *const rng, population_t *pop, population_t *selected)
{
    double cumulative_fitness;
    double cumulative_probability;
    double *relative_probabilities;
    double *cumulative_probabilities;
    double u;
    int i, k;

    relative_probabilities = calloc(pop->size, sizeof(double));
    cumulative_probabilities = calloc(pop->size, sizeof(double));

    qsort(pop->individuals, pop->size, sizeof(chromosome_t), cmpchromp);

    cumulative_fitness = cumulativeFitness(pop);

    /* calculate the relative propabibilities for each individual */
    for (i = 0; i < pop->size; ++i) {
        relative_probabilities[i] = (pop->individuals[i]).fitness
            / cumulative_fitness;
    }

    cumulative_probability = 0.0;

    /* calculate the cumulative probabilities for each individual */
    for (i = 0; i < pop->size; ++i) {
        cumulative_probability += relative_probabilities[i];
        cumulative_probabilities[i] = cumulative_probability;
    }

    for (k = 0; k < pop->size; ++k) {
        u = gsl_rng_uniform(rng);

        for (i = pop->size - 2; i >= 0; i--) {
            if ((cumulative_probabilities[i] < u)
                && (cumulative_probabilities[i+1] > u)) {

                /* copy the selected individual into the new population */
                cpychrom(&(selected->individuals[k]),
                         &(pop->individuals[i + 1]),
                         pop->bits);
            }
        }
    }

    /* cleanup allocated memory */
    free(cumulative_probabilities);
    free(relative_probabilities);

    return 0;
}
