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

#include "ga.h"


int select(population_t *pop, population_t *selected);
int mutate(population_t *pop);
int recombine(population_t *selected, population_t *pop);
int crossover(population_t *selected, population_t *pop);


#endif /* ENVIRONMENT_H */
