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

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

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
#ifdef HAVE_LIBGSL
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
#endif
    int i;

#ifdef HAVE_MPI
    MPI_Init(&argc, &argv);
#endif /* HAVE_MPI */

    /* initialise and configure the command line options */
    init();
    process_cl(argc, argv);

#ifdef HAVE_LIBGSL
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);
#else
    srand48(12345);
#endif

    pop.size = selected.size = globalArgs.population_size;
    pop.bits = selected.bits = globalArgs.chromosome_bits;

#ifdef HAVE_LIBGSL
    rallocPopulation(rng, &pop);
#else
    rallocPopulation(&pop);
#endif

    callocPopulation(&selected);
    
    evaluate(&pop, &fitness);

    for (i = 0; i < globalArgs.generations; ++i) {

#ifdef HAVE_LIBGSL
        selection(rng, &pop, &selected);
        recombine(rng, &selected);
        mutate(rng, globalArgs.mutation_rate, &selected);
#else
        selection(&pop, &selected);
        recombine(&selected);
        mutate(globalArgs.mutation_rate, &selected);
#endif
        evaluate(&selected, &fitness);

        survive(&pop, &selected);

#ifdef NDEBUG
        printPop(&pop);
#endif
    }
    
    freePopulation(&pop);
    freePopulation(&selected);

#ifdef HAVE_LIBGSL
    gsl_rng_free(rng);
#endif
    
#ifdef HAVE_MPI
    MPI_Finalize();
#endif /* HAVE_MPI */

    return EXIT_SUCCESS;
}
