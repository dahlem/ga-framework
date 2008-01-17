/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
/**
 * Declaration of functions for the population for the generic algorithm framework.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __POPULATION_H__
#define __POPULATION_H__

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "ga.h"


/**
 * @defgroup Memory-Allocation Operations for memory allocation and de-allocation
 */

#ifdef HAVE_LIBGSL
/**
 * @name Random bit assignment
 * @{
 */
/**
 * @ingroup Memory-Allocation
 *
 * Allocate memory for a population and randomly assign the bits of
 * the individuals' chromosome.
 *
 * @param const gsl_rng *const the gsl random number generator
 * @param population_t* the population to be allocated
 * @return 0, if success. Otherwise the error code defined in ga.h.
 */
int rallocPopulation(const gsl_rng *const rng, population_t *pop);
#else
int rallocPopulation(population_t *pop);
/** @}*/
#endif

/**
 * @ingroup Allocation
 *
 * Allocate memory for the population and assign 0 to the bits of the
 * individuals' chromosome.
 *
 * @param population_t* the population to be allocated
 * @return 0, if success. Otherwise the error code defined in ga.h.
 */
int callocPopulation(population_t *pop);

/**
 * @ingroup Memory-Allocation
 *
 * De-allocate the memory of the population.
 *
 * @param population_t* the population to be de-allocated
 */
int freePopulation(population_t *pop);

/**
 * Copies the source population into a destination population. The allocated
 * memory for target population has to be the same as the source population.
 *
 * @param population_t* the destination population
 * @param population_t* the source population
 * @return 0, if success. Otherwise the error code defined in ga.h.
 */
int cpypop(population_t *dest, const population_t *src);

/**
 * Copies a source chromosome into a destination chromosome. The allocated
 * memory for target chromosome has to be the same as the source chromosome.
 *
 * @param chromosome_t* the destination chromosome
 * @param chromosome_t* the source chromosome
 * @param int the size of the chromosomes
 * @return 0, if success. Otherwise the error code defined in ga.h.
 */
int cpychrom(chromosome_t *dest, const chromosome_t *src, int bits);

/**
 * Compare two chromosome with each other. The function declares generic
 * void pointers as its parameters, because it is used within the quick sort
 * algorithm to sort the population according to its fitness levels.
 *
 * @param const void* the destination chromosome
 * @param const void* the source chromosome
 * @return -1, if the first chromosome's fitness is lower than the second ones.
 *         1, if the first chromosome's fitness is higher than the second ones.
 *         0, if equal.
 */
int cmpchromp(const void *p1, const void *p2);


#endif /* POPULATION_H */
