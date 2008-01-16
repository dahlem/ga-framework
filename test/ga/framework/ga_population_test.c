/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
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

#include "ga.h"
#include "population.h"

#include "ga_population_test.h"
#include "setup.h"



void registerPopulationTests()
{
    if (CU_register_suites(pop_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


int init_pop()
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


int clean_pop()
{
#ifdef HAVE_LIBGSL
    gsl_rng_free(rng_test);
#endif
    
    return 0;
}


void testCpypop()
{
    population_t pop, dest;
    int i, j;

    pop.size = dest.size = 5;
    pop.bits = dest.bits = 10;
    
    pop.individuals = malloc(5 * sizeof(chromosome_t));
    dest.individuals = malloc(5 * sizeof(chromosome_t));

    for (i = 0; i < 5; ++i){
        pop.individuals[i].allele = malloc(10 * sizeof(unsigned short));
        dest.individuals[i].allele = calloc(10, sizeof(unsigned short));
    }

    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 10; ++j) {
            pop.individuals[i].allele[j] = 1;
        }
    }
    
    CU_ASSERT_EQUAL(cpypop(&dest, &pop), 0);
    CU_ASSERT_EQUAL(pop.size, dest.size);
    CU_ASSERT_EQUAL(pop.bits, dest.bits);

    for (i = 0; i < 5; ++i) {
        for (j = 0; j < 10; ++j) {
            CU_ASSERT_TRUE(dest.individuals[i].allele[j] == 1);
        }
    }
    
    for (i = 0; i < 5; ++i){
        free(pop.individuals[i].allele);
        free(dest.individuals[i].allele);
    }

    free(pop.individuals);
    free(dest.individuals);
}


void testCpychrom()
{
    chromosome_t src, dest;
    int i;

    src.fitness = 10;
    src.allele = malloc(10 * sizeof(unsigned short));
    dest.allele = calloc(10, sizeof(unsigned short));

    for (i = 0; i < 10; ++i) {
        src.allele[i] = 1;
    }
    
    CU_ASSERT_EQUAL(cpychrom(&dest, &src, 10), 0);
    CU_ASSERT_TRUE(src.fitness == dest.fitness);

    for (i = 0; i < 10; ++i) {
        CU_ASSERT_EQUAL(dest.allele[i], 1);
    }

    free(src.allele);
    free(dest.allele);
}


void testPopsizeUnspecified()
{
    population_t pop;

    pop.size = 0;
    pop.bits = 0;
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), GA_POPSIZE_UNSPECIFIED);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), GA_POPSIZE_UNSPECIFIED);
#endif
}


void testBitsUnspecified()
{
    population_t pop;

    pop.size = 10;
    pop.bits = 0;
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), GA_BITS_UNSPECIFIED);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), GA_BITS_UNSPECIFIED);
#endif
}


void testInit()
{
    population_t pop;
    int i, j;

    pop.size = 10;
    pop.bits = 10;
    
#ifdef HAVE_LIBGSL
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);
#else
    CU_ASSERT_EQUAL(rallocPopulation(&pop), 0);
#endif

    for (i = 0; i < pop.size; ++i) {
        for (j = 0; j < pop.bits; ++j) {
            CU_ASSERT_TRUE(pop.individuals[i].allele[j] <= 1);
        }
    }
    
    CU_ASSERT_EQUAL(freePopulation(&pop), 0);
}
