/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include "config.h"

#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "environment.h"
#include "ga.h"
#include "population.h"

#include "ga_environment_test.h"
#include "setup.h"



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


int init_env()
{
#ifdef HAVE_LIBGSL
    rng_type_test = gsl_rng_mt19937;
    rng_test = gsl_rng_alloc(rng_type_test);

    if (rng_test == NULL) {
        return -1;
    } else {
        return 0;
    }
#else
    return 0;
#endif
}


int clean_env()
{
#ifdef HAVE_LIBGSL
    gsl_rng_free(rng_test);
#endif

    return 0;
}


void testEvaluate() 
{
    population_t pop;
    int i;

    pop.size = 10;
    pop.bits = 10;
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
#endif

    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);

    for (i = 0; i < pop.bits; ++i) {
        CU_ASSERT_TRUE(pop.individuals[i].fitness >= 0);
        CU_ASSERT_TRUE(pop.individuals[i].fitness <= 10);
    }

    CU_ASSERT_EQUAL(freePopulation(&pop), 0);
}


void testSelection()
{
    population_t pop, selected;
    int i;

    pop.size = 100;
    pop.bits = 10;

    selected.size = 100;
    selected.bits = 10;

    CU_ASSERT_EQUAL(callocPopulation(&selected), 0);
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
#endif

    pop.individuals[0].fitness = 1.0;
    pop.individuals[1].fitness = 1.0;
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(selection(rng_test, &pop, &selected), 0);
#else
    CU_ASSERT_EQUAL(selection(&pop, &selected), 0);
#endif

    for (i = 0; i < pop.size; ++i) {
        CU_ASSERT_TRUE(
            (cmpchromp(
                &(pop.individuals[pop.size - 2]),
                &(selected.individuals[i])) == 0)
            ||
            (cmpchromp(
                &(pop.individuals[pop.size - 1]),
                &(selected.individuals[i])) == 0)
            );
        CU_ASSERT_EQUAL(selected.individuals[i].fitness, 1);
    }

    freePopulation(&selected);
    freePopulation(&pop);
}


void testOnePointCrossover()
{
    population_t pop, new;

    pop.size = new.size = 100;
    pop.bits = new.bits = 10;

    CU_ASSERT_EQUAL(callocPopulation(&new), 0);

#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
    
    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);
    CU_ASSERT_EQUAL(selection(rng_test, &pop, &new), 0);

    CU_ASSERT_EQUAL(recombine(rng_test, &new), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
    
    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);
    CU_ASSERT_EQUAL(selection(&pop, &new), 0);

    CU_ASSERT_EQUAL(recombine(&new), 0);
#endif

    freePopulation(&new);
    freePopulation(&pop);
}


void testMutation()
{
    population_t pop, copy;
    int i, j;
    long orig, new;

    orig = new = 0;
    pop.size = copy.size = 100;
    pop.bits = copy.bits = 10;

#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
#endif

    CU_ASSERT_EQUAL(callocPopulation(&copy), 0);

    CU_ASSERT_EQUAL(cpypop(&copy, &pop), 0);
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(mutate(rng_test, 1.0, &pop), 0);
#else
    CU_ASSERT_EQUAL(mutate(1.0, &pop), 0);
#endif

    for (i = 0; i < pop.size; ++i) {
        for (j = 0; j < pop.bits; ++j) {
            orig = pop.individuals[i].allele[j] * pow(2, j);
            new = copy.individuals[i].allele[j] * pow(2, j);
        }
        CU_ASSERT_TRUE(orig != new);
    }
    
    freePopulation(&pop);
    freePopulation(&copy);
}


void testSurvive()
{
    population_t pop, new;

    pop.size = new.size = 10;
    pop.bits = new.bits = 100;

#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
    CU_ASSERT_EQUAL(callocPopulation(&new), 0);
    
    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);
    CU_ASSERT_EQUAL(selection(rng_test, &pop, &new), 0);

    CU_ASSERT_EQUAL(recombine(rng_test, &new), 0);
    CU_ASSERT_EQUAL(mutate(rng_test, 0.06, &new), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
    CU_ASSERT_EQUAL(callocPopulation(&new), 0);
    
    CU_ASSERT_EQUAL(evaluate(&pop, &fitness), 0);
    CU_ASSERT_EQUAL(selection(&pop, &new), 0);

    CU_ASSERT_EQUAL(recombine(&new), 0);
    CU_ASSERT_EQUAL(mutate(0.06, &new), 0);
#endif

    CU_ASSERT_EQUAL(evaluate(&new, &fitness), 0);
    CU_ASSERT_EQUAL(survive(&pop, &new), 0);

    freePopulation(&pop);
    freePopulation(&new);
}
