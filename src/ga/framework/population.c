/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include "config.h"

#include <stdlib.h>

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "population.h"


int cpypop(population_t *dest, const population_t *src)
{
    int i, j;
    
    dest->size = src->size;
    dest->bits = src->bits;
    dest->cum_fit = src->cum_fit;

    for (i = 0; i < src->size; ++i) {
        for (j = 0; j < src->bits; ++j) {
            (dest->individuals[i]).allele[j] = (src->individuals[i]).allele[j];
        }

        (dest->individuals[i]).fitness = (src->individuals[i]).fitness;
    }
    
    return 0;
}


int cpychrom(chromosome_t *dest, const chromosome_t *src, int bits)
{
    int i;
    
    for (i = 0; i < bits; ++i) {
        dest->allele[i] = src->allele[i];
        dest->fitness = src->fitness;
    }
    
    return 0;
}


int cmpchromp(const void *p1, const void *p2)
{
    chromosome_t chrom1, chrom2;

    chrom1 = *((chromosome_t *) p1);
    chrom2 = *((chromosome_t *) p2);

    if (chrom1.fitness < chrom2.fitness) {
        return -1;
    }
    if (chrom1.fitness > chrom2.fitness) {
        return 1;
    }
    
    return 0;
}


#ifdef HAVE_LIBGSL
int rallocPopulation(const gsl_rng *const rng, population_t *pop)
#else
int rallocPopulation(population_t *pop)
#endif
{
    int i, j;

    if (pop->size <= 0) {
        return GA_POPSIZE_UNSPECIFIED;
    }

    if (pop->bits <= 0) {
        return GA_BITS_UNSPECIFIED;
    }

    /* allocate the memory for the individuals */
    if ((pop->individuals = malloc(sizeof(chromosome_t) * pop->size)) == NULL) {
        return GA_MALLOC_UNSUCCESSFUL;
    }

    /* allocate the bits for each individual and set to a random bit */
    for (i = 0; i < pop->size; ++i) {
        if (((pop->individuals[i]).allele
             = calloc(pop->bits, sizeof(unsigned short))) == NULL) {
            return GA_MALLOC_UNSUCCESSFUL;
        }
        
        (pop->individuals[i]).fitness = 0.0;

        for (j = 0; j < pop->bits; ++j) {
            /* generate a random integer [0, 1] */
#ifdef HAVE_LIBGSL
            (pop->individuals[i]).allele[j] =
                (unsigned short) gsl_rng_uniform_int(rng, 2);
#else
            (pop->individuals[i]).allele[j] =
                (unsigned short) (lrand48() % 2);
#endif
        }
    }
    
    return 0;
}


int callocPopulation(population_t *pop)
{
    int i;
    
    if (pop->size <= 0) {
        return GA_POPSIZE_UNSPECIFIED;
    }

    if (pop->bits <= 0) {
        return GA_BITS_UNSPECIFIED;
    }

    /* allocate the memory for the individuals */
    if ((pop->individuals = malloc(sizeof(chromosome_t) * pop->size)) == NULL) {
        return GA_MALLOC_UNSUCCESSFUL;
    }

    /* allocate the bits for each individual and set the bits to 0 */
    for (i = 0; i < pop->size; ++i) {
        if (((pop->individuals[i]).allele
             = calloc(pop->bits, sizeof(unsigned short))) == NULL) {
            return GA_MALLOC_UNSUCCESSFUL;
        }
        (pop->individuals[i]).fitness = 0.0;
    }
    
    return 0;
}


int freePopulation(population_t *pop)
{
    int i;
    
    if (pop->size <= 0) {
        return 0;
    }

    if (pop->bits <= 0) {
        return 0;
    }

    /* free memory for the allele */
    for (i = 0; i < pop->size; i++) {
        if ((pop->individuals[i]).allele != NULL) {
            free((pop->individuals[i]).allele);
        }
    }

    /* free the memory of the individuals */
    free(pop->individuals);

    return 0;
}
