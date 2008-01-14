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
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include <gsl/gsl_rng.h>

#include "ga.h"


int mutate(const gsl_rng *const rng, population_t *pop);

int recombine(const gsl_rng *const rng, population_t *new);
int onePointCrossover(const gsl_rng *const rng, population_t *new);

int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int));
int selection(const gsl_rng *const rng, population_t *pop, population_t *selected);
int rws(const gsl_rng *const rng, population_t *pop, population_t *selected);

#endif /* ENVIRONMENT_H */
