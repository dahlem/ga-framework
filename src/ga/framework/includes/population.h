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
#ifndef __POPULATION_H__
#define __POPULATION_H__

#include <gsl/gsl_rng.h>

#include "ga.h"


int rallocPopulation(const gsl_rng *const rng, population_t *pop);
int callocPopulation(population_t *pop);
int freePopulation(population_t *pop);

int cpypop(population_t *dest, const population_t *src);
int cpychrom(chromosome_t *dest, const chromosome_t *src, int bits);
int cmpchromp(const void *p1, const void *p2);


#endif /* POPULATION_H */
