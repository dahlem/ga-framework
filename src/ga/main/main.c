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

#ifdef HAVE_MPI
# include <mpi.h>
#endif /* HAVE_MPI */

#include <stdlib.h>
#include <stdio.h>

#include <gsl/gsl_rng.h>

#include "environment.h"
#include "ga.h"
#include "ga-cl.h"
#include "population.h"



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


int main(int argc, char *argv[])
{
    population_t pop, selected;
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
    int i;

    /* initialise and configure the command line options */
    init();
    process_cl(argc, argv);
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);


    pop.size = selected.size = globalArgs.population_size;
    pop.bits = selected.bits = globalArgs.chromosome_bits;

    rallocPopulation(rng, &pop);
    callocPopulation(&selected);
    
    evaluate(&pop, &fitness);

    for (i = 0; i < globalArgs.generations; ++i) {
        selection(rng, &pop, &selected);

        recombine(rng, &selected);
        mutate(rng, globalArgs.mutation_rate, &selected);
        evaluate(&selected, &fitness);

        survive(&pop, &selected);

#ifdef NDEBUG
        printPop(&pop);
#endif
    }
    
    freePopulation(&pop);
    freePopulation(&selected);

    gsl_rng_free(rng);
    
    return EXIT_SUCCESS;
}
