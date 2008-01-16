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
 * Mutate a give popuulation with a give mutation rate. The muation is an in-place
 * operation. That means the current population is changed.
 *
 * @param const gsl_rng *const the gsl random number generator
 * @param double the mutation rate
 * @param population_t* the population to be mutated.
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int mutate(const gsl_rng *const rng, double rate, population_t *pop);

/**
 *
 */
int recombine(const gsl_rng *const rng, population_t *new);
int onePointCrossover(const gsl_rng *const rng, population_t *new);
int selection(const gsl_rng *const rng, population_t *pop, population_t *selected);
int rws(const gsl_rng *const rng, population_t *pop, population_t *selected);
#else

/**
 * Mutate a give popuulation with a give mutation rate. The muation is an in-place
 * operation. That means the current population is changed.
 *
 * @param double the mutation rate
 * @param population_t* the population to be mutated.
 * @return 0, if success. Otherwise the error code as declared in ga.h
 */
int mutate(double rate, population_t *pop);
int recombine(population_t *new);
int onePointCrossover(population_t *new);
int selection(population_t *pop, population_t *selected);
int rws(population_t *pop, population_t *selected);
#endif


int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int));

int survive(population_t *pop, population_t *new);

#endif /* ENVIRONMENT_H */
