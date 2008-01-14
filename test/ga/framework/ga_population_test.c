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
    rng_type_test = gsl_rng_mt19937;
    rng_test = gsl_rng_alloc(rng_type_test);

    if (rng_test == NULL) {
        return -1;
    } else {
        return 0;
    }
}


int clean_pop()
{
    gsl_rng_free(rng_test);
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
    
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), GA_POPSIZE_UNSPECIFIED);
}


void testBitsUnspecified()
{
    population_t pop;

    pop.size = 10;
    pop.bits = 0;
    
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), GA_BITS_UNSPECIFIED);
}


void testInit()
{
    population_t pop;
    int i, j;

    pop.size = 10;
    pop.bits = 10;
    
    CU_ASSERT_EQUAL(rallocPopulation(rng_test, &pop), 0);

    for (i = 0; i < pop.size; ++i) {
        for (j = 0; j < pop.bits; ++j) {
            CU_ASSERT_TRUE(pop.individuals[i].allele[j] <= 1);
            CU_ASSERT_TRUE(pop.individuals[i].allele[j] >= 0);
        }
    }
    
    CU_ASSERT_EQUAL(freePopulation(&pop), 0);
}
