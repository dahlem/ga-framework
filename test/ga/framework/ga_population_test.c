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

#include "ga.h"
#include "population.h"

#include "ga_population_test.h"



void registerPopulationTests()
{
    if (CU_register_suites(pop_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testPopsizeUnspecified()
{
    population_t pop;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    pop.size = 0;
    pop.bits = 0;
    
    CU_ASSERT_EQUAL(initPopulation(rng, &pop), POPSIZE_UNSPECIFIED);
    
    gsl_rng_free(rng);
}


void testBitsUnspecified()
{
    population_t pop;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    pop.size = 10;
    pop.bits = 0;
    
    CU_ASSERT_EQUAL(initPopulation(rng, &pop), BITS_UNSPECIFIED);

    gsl_rng_free(rng);
}


void testInit()
{
    population_t pop;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
    int i, j;

    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);

    pop.size = 10;
    pop.bits = 10;
    
    CU_ASSERT_EQUAL(initPopulation(rng, &pop), 0);

    for (i = 0; i < pop.size; ++i) {
        for (j = 0; j < pop.bits; ++j) {
            CU_ASSERT_TRUE(pop.individuals[i].allele[j] <= 1);
            CU_ASSERT_TRUE(pop.individuals[i].allele[j] >= 0);
        }
    }
    
    gsl_rng_free(rng);
}
