/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include "environment.h"



int select(population_t *pop, population_t *selected)
{
    return 0;
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
