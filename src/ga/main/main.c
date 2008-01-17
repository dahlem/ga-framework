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
# include <limits.h>
# define KILL_PILL USHRT_MAX
#endif /* HAVE_MPI */

#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif /* HAVE_LIBGSL */

#include "environment.h"
#include "ga.h"
#include "ga-cl.h"
#include "ga-debug.h"
#include "population.h"



/**
 * Calculates the fitness of an individual. This function merely counts the
 * bits set to one within the chromosome.
 *
 * @param unsigned short* the chromosome representation
 * @param int the size of the chromsome
 * @return the fitness value of the chromosome
 */
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


void stats(population_t *pop)
{
    printf("\n\nResults   :\n");
    printf("Generations   : %d\n", globalArgs.generations);
    printf("Population    : %d\n", globalArgs.population_size);
    printf("Chrom. length : %d\n", globalArgs.chromosome_bits);
    printf("Acc. fitness  : %f\n", pop->cum_fit);
}


void master() 
{
    population_t pop, selected;
#ifdef HAVE_LIBGSL
    const gsl_rng_type *rng_type = gsl_rng_mt19937;
    gsl_rng *rng;
#endif /* HAVE_LIBGSL */
    char buf[128];
    int i;

#ifdef HAVE_MPI    
    int size;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
#endif /* HAVE_MPI */

    
    /* initialise the random number generator */
#ifdef HAVE_LIBGSL
    gsl_rng_env_setup();
    rng = gsl_rng_alloc(rng_type);
#else /* HAVE_LIBGSL */
    srand48(globalArgs.seed);
#endif /* HAVE_LIBGSL */

    /* initialise and allocate the population */
    pop.size = selected.size = globalArgs.population_size;
    pop.bits = selected.bits = globalArgs.chromosome_bits;

#ifdef HAVE_LIBGSL
    rallocPopulation(rng, &pop);
#else
    rallocPopulation(&pop);
#endif /* HAVE_LIBGSL */

    callocPopulation(&selected);

    /* evaluate the initial fitness */
    evaluate(&pop, &fitness);

    /* run for N generations */
    for (i = 0; i < globalArgs.generations; ++i) {

#ifdef HAVE_LIBGSL
        selection(rng, &pop, &selected);
        recombine(rng, &selected);
        mutate(rng, globalArgs.mutation_rate, &selected);
#else
        selection(&pop, &selected);
        recombine(&selected);
        mutate(globalArgs.mutation_rate, &selected);
#endif /* HAVE_LIBGSL */
        evaluate(&selected, &fitness);

        /* we print the intermediate results of the parent generation. */
#ifdef NDEBUG
        sprintf(buf, "Intermediate result of generation %d", i);
        
        printPop(buf, &selected);
#endif /* NDEBUG */
        survive(&pop, &selected);
    }

    /* Evaluate and print stats */
    evaluate(&pop, &fitness);

#ifdef HAVE_MPI    
    for(i = 1; i < size; ++i) {
        /* Send no more jobs */
#ifdef NDEBUG
        printf("Send kill pill.\n");
        fflush(stdout);
#endif
        MPI_Send(0, 0, MPI_UNSIGNED_SHORT, i, KILL_PILL, MPI_COMM_WORLD);
#ifdef NDEBUG
        printf("Kill pill sent.\n");
        fflush(stdout);
#endif /* NDEBUG */
    }
#endif /* HAVE_MPI */
    
#ifdef NDEBUG
    printPop("Result of the last generation", &pop);
#endif  /* NDEBUG */

    cumulativeFitness(&pop);
    stats(&pop);
    
    /* free memory */
    freePopulation(&pop);
    freePopulation(&selected);

#ifdef HAVE_LIBGSL
    gsl_rng_free(rng);
#endif /* HAVE_LIBGSL */
}


#ifdef HAVE_MPI
void slave(double (*fitnessFuncPtr)(unsigned short*, int))
{
    int rank;
    
    unsigned short *individual;
    MPI_Status status;
    double fit;

    individual = calloc(globalArgs.chromosome_bits, sizeof(unsigned short));

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while(1) {
#ifdef NDEBUG
        printf("Receive job from the master process.\n");
        fflush(stdout);
#endif /* NDEBUG */
        MPI_Recv(individual, MPI_UNSIGNED_SHORT, globalArgs.chromosome_bits,
                 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
#ifdef NDEBUG
        printf("Received job %d from the master process.\n", status.MPI_TAG);
        printChromosome(individual, globalArgs.chromosome_bits);
        fflush(stdout);
#endif /* NDEBUG */

        if (status.MPI_TAG == KILL_PILL) {
            break;
        }

        /* calculate the fitness */
        fit = fitnessFuncPtr(individual, globalArgs.chromosome_bits);
            
        /* Send fitness value back */
#ifdef NDEBUG
        printf("Send result %f of job %d to the master process.\n", fit, status.MPI_TAG);
        fflush(stdout);
#endif /* NDEBUG */
        MPI_Send(&fit, MPI_DOUBLE, 1, 0, status.MPI_TAG, MPI_COMM_WORLD);
#ifdef NDEBUG
        printf("Result %f of job %d to the master process sent.\n", fit, status.MPI_TAG);
        fflush(stdout);
#endif /* NDEBUG */
    }

    free(individual);
}
#endif /* HAVE_MPI */


int main(int argc, char *argv[])
{
#ifdef HAVE_MPI
    int rank;

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#endif /* HAVE_MPI */

    /* initialise and configure the command line options */
    init();
    process_cl(argc, argv);

#ifdef HAVE_MPI

    switch (rank) {
      case 0:
          master();
          break;
      default:
          slave(&fitness);
          break;
    }

    MPI_Finalize();
#ifdef NDEBUG
    printf("Goodbye process %d.\n", rank);
    fflush(stdout);
#endif /* NDEBUG */
#else
    master();
#endif /* HAVE_MPI */

    return EXIT_SUCCESS;
}
