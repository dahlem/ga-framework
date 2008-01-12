/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdlib.h>

#include "population.h"
#include "environment.h"



int selection(const gsl_rng *const rng, population_t *pop, population_t *selected)
{
    return rws(rng, pop, selected);
}


int mutate(population_t *pop)
{
    return 0;
}


int recombine(population_t *selected, population_t *pop)
{
    return crossover(selected, pop);
}


int crossover(population_t *selected, population_t *pop)
{
    return 0;
}


int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int))
{
    int i;

    for (i = 0; i < pop->size; ++i) {
        pop->individuals[i].fitness = fitnessFuncPtr(
            pop->individuals[i].allele, pop->bits);
    }

    return 0;
}

double cumulativeFitness(population_t *pop) 
{
    double cumulative_fitness;
    int i;

    cumulative_fitness = 0.0;
    
    for (i = 0; i < pop->size; ++i) {
        cumulative_fitness += pop->individuals[i].fitness;
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
        relative_probabilities[i] = pop->individuals[i].fitness
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
