/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
/**
 * Declaration of the environmental forces for the generic algorithm framework.
 * The environment can be set up using GSL for the random number generation.
 * For that the configure has to be invoked with the <code>--enable-gsl</code>
 * parameter. Otherwise the default is to use <code>drand48</code>.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "ga.h"



/**
 * Calculate the cumulative fitness of the whole population.
 *
 * @param population_t* the population
 * @return the cumulative fitness value
 */
double cumulativeFitness(population_t *pop);


#ifdef HAVE_LIBGSL
/**
 * @defgroup Mutation operation
 * @{
 */
/**
 * Mutate a give popuulation with a give mutation rate. The muation is an in-place
 * operation. That means the current population is changed.
 *
 * @param const gsl_rng *const the gsl random number generator
 * @param double the mutation rate
 * @param population_t* the population to be mutated.
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int mutate(const gsl_rng *const rng, double rate, population_t *pop);
#else
int mutate(double rate, population_t *pop);
/** @}*/
#endif


#ifdef HAVE_LIBGSL
/**
 * @defgroup Recombination operations
 * @{
 */

/**
 * Recombine a selected parent population. This function is a wrapper around the
 * different cross-over techniques. At the moment the call is only delegated to
 * the one-point crossover function. The recombination function results in an
 * offspring population which is put in-lace of the selected population.
 *
 * @param const gsl_rng *const the random number generator
 * @param population_t* the population to be recombined.
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int recombine(const gsl_rng *const rng, population_t *new);
int onePointCrossover(const gsl_rng *const rng, population_t *new);
#else
int recombine(population_t *new);
int onePointCrossover(population_t *new);
/** @}*/
#endif


#ifdef HAVE_LIBGSL
/**
 * @defgroup Selection operations
 * @{
 */

/**
 * The selection operation is responsible for selecting the fittest individuals
 * for reproduction. The top-level selection operation delegates to more specialised
 * functions that implement a particular algorithm for selection. Here the algorithm
 * of choice is the roulette-wheel sampling, whereby each individual is allocated a
 * section on a roulette wheel incorporating the relative fitness compared to the
 * whole population. The roulette wheel is sampled N times to select the parents
 * to produce the offspring of the next generation.
 *
 * @param const gsl_rng *const the gsl random number generator
 * @param population_t* the current population
 * @param population_t* the selected population
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int selection(const gsl_rng *const rng, population_t *pop, population_t *selected);
int rws(const gsl_rng *const rng, population_t *pop, population_t *selected);
#else
int selection(population_t *pop, population_t *selected);
int rws(population_t *pop, population_t *selected);

/** @}*/
#endif

/**
 * Evaluate the fitness of each individual in the population given a fitness
 * function. This function can be parallelised by enabling MPI using the configure
 * script. The parallel version assigns the job of calculating the fitness for
 * an individual to an available slave process. The master process is responsible
 * for assigning the jobs and accumulating the results.
 *
 * @param population_t* the population to be evaluated
 * @param double (*fitnessFuncPtr)(unsigned short*, int) the pointer to a fitness function
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int));


/**
 * The survive function implements the survival of the fittest, where the fittest
 * individuals from the parent generation and the offspring generation are selected.
 *
 * @param population_t* the parent population
 * @param population_t* the offspring population
 */
int survive(population_t *pop, population_t *new);

#endif /* ENVIRONMENT_H */
