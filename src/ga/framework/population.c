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



int initPopulation(const gsl_rng *const rng, population_t *pop)
{
    int i, j;
    
    if (pop->size <= 0) {
        return POPSIZE_UNSPECIFIED;
    }

    if (pop->bits <= 0) {
        return BITS_UNSPECIFIED;
    }

    /* allocate the memory for the individuals */
    pop->individuals = malloc(sizeof(chromosome_t) * pop->size);

    /* allocate the bits for each individual and set to a random bit */
    for (i = 0; i < pop->size; ++i) {
        pop->individuals[i].allele = calloc(pop->bits, sizeof(unsigned short));
        pop->individuals[i].fitness = 0.0;

        for (j = 0; j < pop->size; ++j) {
            /* generate a random integer [0, 1] */
            pop->individuals[i].allele[j] = gsl_rng_uniform_int (rng, 2);
        }
    }
    
    return 0;
}


int freePopulation(population_t *pop)
{
    int i, j;
    
    if (pop->size <= 0) {
        return 0;
    }

    if (pop->bits <= 0) {
        return 0;
    }

    /* free memory for the allele */
    for (i = 0; i < pop->size; ++i) {
        free(pop->individuals[i].allele);
    }

    /* free the memory of the individuals */
    free(pop->individuals);

    return 0;
}
