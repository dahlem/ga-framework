/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>
#include <gsl/gsl_rng.h>

#include "environment.h"
#include "ga.h"
#include "population.h"

#include "ga_environment_test.h"


double fitness(unsigned short *allele, int bits) 
{
    int i;
    double result;

    result = 0.0;
    
    for (i = 0; i < bits; ++i) {
        if (allele[i]) {
            result += 1.0;
        }
    }

    return result;
}


void registerEnvironmentTests()
{
    if (CU_register_suites(env_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testEvaluate() 
{
    population_t pop;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
    int i;

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    pop.size = 10;
    pop.bits = 10;
    
    CU_ASSERT_EQUAL(rallocPopulation(rng, &pop), 0);

    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);

    for (i = 0; i < pop.bits; ++i) {
        CU_ASSERT_TRUE(pop.individuals[i].fitness >= 0);
        CU_ASSERT_TRUE(pop.individuals[i].fitness <= 10);
    }

    CU_ASSERT_EQUAL(freePopulation(&pop), 0);
    gsl_rng_free(rng);
}

void testSelection()
{
    population_t pop, selected;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
    int i;

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    pop.size = 100;
    pop.bits = 10;

    selected.size = 100;
    selected.bits = 10;

    CU_ASSERT_EQUAL(rallocPopulation(rng, &pop), 0);
    CU_ASSERT_EQUAL(callocPopulation(&selected), 0);

    pop.individuals[0].fitness = 1.0;
    pop.individuals[1].fitness = 1.0;
    
    CU_ASSERT_EQUAL(selection(rng, &pop, &selected), 0);

    for (i = 0; i < pop.size; ++i) {
        CU_ASSERT_TRUE(
            (cmpchromp(
                pop.individuals[pop.size - 2].allele,
                selected.individuals[i].allele) == 0)
            ||
            (cmpchromp(
                pop.individuals[pop.size - 1].allele,
                selected.individuals[i].allele) == 0)
            );
        CU_ASSERT_EQUAL(selected.individuals[i].fitness, 1);
    }
}
