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
# include <string.h>
# include <limits.h>
# define KILL_PILL USHRT_MAX
#endif /* HAVE_MPI */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "population.h"
#include "environment.h"
#include "utils.h"


#ifdef HAVE_MPI

typedef struct 
{
    unsigned short *allele;
    double fitness;
    int number;
} individual_t;

#endif



#ifdef HAVE_LIBGSL
int selection(const gsl_rng *const rng, population_t *pop, population_t *selected)
#else
int selection(population_t *pop, population_t *selected)
#endif
{
#ifdef HAVE_LIBGSL
    return rws(rng, pop, selected);
#else
    return rws(pop, selected);
#endif
}


#ifdef HAVE_LIBGSL
int mutate(const gsl_rng *const rng, double rate, population_t *pop)
#else
int mutate(double rate, population_t *pop)
#endif
{
    unsigned short *gray_code;
    int i, j;
    double u;
    bool isConverted;


    if ((gray_code = calloc(pop->bits, sizeof(unsigned short))) == NULL) {
        return GA_MALLOC_UNSUCCESSFUL;
    }

    for (i = 0; i < pop->size; ++i) {
        isConverted = false;

        for (j = 0; j < pop->bits; ++j) {
            
            /* mutate a single bit */
#ifdef HAVE_LIBGSL
            u = gsl_rng_uniform(rng);
#else
            u = drand48();
#endif
            
            /* if the random number is smaller than the mutation rate */
            if (u <= rate) {
                /* lazy convert the binary chromosome to the gray representation */
                if (!isConverted) {
                    binarytogray(pop->individuals[i].allele,
                                 gray_code,
                                 pop->bits);
                    isConverted = true;
                }

                /* flip the bit */
                gray_code[j] = gray_code[j] ^ 1;
            }
        }

        /* if the chromosome was converted, convert it back into binary */
        if (isConverted) {
            graytobinary(pop->individuals[i].allele,
                         gray_code,
                         pop->bits);
        }
    }

    if (gray_code != NULL) {
        free(gray_code);
    }

    return 0;
}


#ifdef HAVE_LIBGSL
int recombine(const gsl_rng *const rng, population_t *new)
#else
int recombine(population_t *new)
#endif
{
#ifdef HAVE_LIBGSL
    return onePointCrossover(rng, new);
#else
    return onePointCrossover(new);
#endif
}


#ifdef HAVE_LIBGSL
int onePointCrossover(const gsl_rng *const rng, population_t *new)
#else
int onePointCrossover(population_t *new)
#endif
{
    int i, j;
    int cut_off;
    unsigned short temp;

    for (i = 0; i < (new->size - 1); i += 2) {
        /* the cross-over point has to be between 1 and bits-1,
           otherwise there won't be a cross over at all. */
#ifdef HAVE_LIBGSL
        cut_off = gsl_rng_uniform_int(rng, new->bits - 2) + 1;
#else
        cut_off = (lrand48() % (new->bits - 2)) + 1;
#endif

        for (j = cut_off; j < new->bits; ++j) {
            temp = (new->individuals[i]).allele[j];
            (new->individuals[i]).allele[j] = (new->individuals[i + 1]).allele[j];
            (new->individuals[i + 1]).allele[j] = temp;
        }
    }

    return 0;
}


#ifdef HAVE_MPI
void master(population_t *pop) 
{
    int i;
    int size;
    int jobs;
    unsigned short *individual;
    MPI_Status status;
    double result;

    individual = calloc(pop->bits, sizeof(unsigned short));

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    jobs = 0;
        
    for (i = 1; i < size; ++i) {
        /* Initial jobs */
        memcpy(individual, pop->individuals[jobs].allele,
               pop->bits * sizeof(unsigned short));

        MPI_Send(individual, MPI_UNSIGNED_SHORT, pop->bits, i, jobs, MPI_COMM_WORLD);
        jobs++;
    }

    while (jobs < pop->size) {
        MPI_Recv(&result, MPI_DOUBLE, 1, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);

        pop->individuals[status.MPI_TAG].fitness = result;
        
        memcpy(individual, pop->individuals[jobs].allele,
               pop->bits * sizeof(unsigned short));

        MPI_Send(individual, MPI_UNSIGNED_SHORT, pop->bits, status.MPI_SOURCE,
                 jobs, MPI_COMM_WORLD);

        jobs++;
    }

    for(i = 1; i < size; ++i) {
        MPI_Recv(&result, MPI_DOUBLE, 1, MPI_ANY_SOURCE, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);

        pop->individuals[status.MPI_TAG].fitness = result;        

        /* Send no more jobs */
        MPI_Send(0, 0, MPI_UNSIGNED_SHORT, i, KILL_PILL, MPI_COMM_WORLD);
    }

    free(individual);
}


void slave(double (*fitnessFuncPtr)(unsigned short*, int), int bits)
{
    int rank;
    
    unsigned short *individual;
    MPI_Status status;
    double fit;

    individual = calloc(bits, sizeof(unsigned short));

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    while(1) {
        MPI_Recv(individual, MPI_UNSIGNED_SHORT, bits, 0, MPI_ANY_TAG,
                 MPI_COMM_WORLD, &status);

        if (status.MPI_TAG == KILL_PILL) {
            break;
        }

        /* calculate the fitness */
        fit = fitnessFuncPtr(individual, bits);
            
        /* Send fitness value back */
        MPI_Send(&fit, MPI_DOUBLE, 1, 0, status.MPI_TAG, MPI_COMM_WORLD);
    }

    free(individual);
}
#endif /* HAVE_MPI */


int evaluate(population_t *pop, double (*fitnessFuncPtr)(unsigned short*, int))
{
#ifdef HAVE_MPI
    int rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    switch (rank) {
      case 0:
          master(pop);
          break;
      default:
          slave(fitnessFuncPtr, pop->bits);
          break;
    }
#else
    int i;

    for (i = 0; i < pop->size; ++i) {
        (pop->individuals[i]).fitness = fitnessFuncPtr(
            (pop->individuals[i]).allele, pop->bits);
    }
#endif
    
    return 0;
}

double cumulativeFitness(population_t *pop)
{
    double cumulative_fitness;
    int i;

    cumulative_fitness = 0.0;

    for (i = 0; i < pop->size; ++i) {
        cumulative_fitness += (pop->individuals[i]).fitness;
    }

    pop->cum_fit = cumulative_fitness;
    
    return cumulative_fitness;
}

#ifdef HAVE_LIBGSL
int rws(const gsl_rng *const rng, population_t *pop, population_t *selected)
#else
int rws(population_t *pop, population_t *selected)
#endif
{
    double cumulative_fitness;
    double cumulative_probability;
    double *relative_probabilities;
    double *cumulative_probabilities;
    double u;
    int i, k;

    relative_probabilities = calloc(pop->size, sizeof(double));
    cumulative_probabilities = calloc(pop->size, sizeof(double));

    qsort(pop->individuals, pop->size, sizeof(chromosome_t), cmpchromp);

    cumulative_fitness = cumulativeFitness(pop);

    /* calculate the relative propabibilities for each individual */
    for (i = 0; i < pop->size; ++i) {
        relative_probabilities[i] = (pop->individuals[i]).fitness
            / cumulative_fitness;
    }

    cumulative_probability = 0.0;

    /* calculate the cumulative probabilities for each individual */
    for (i = 0; i < pop->size; ++i) {
        cumulative_probability += relative_probabilities[i];
        cumulative_probabilities[i] = cumulative_probability;
    }

    for (k = 0; k < pop->size; ++k) {

#ifdef HAVE_LIBGSL
        u = gsl_rng_uniform(rng);
#else
        u = drand48();
#endif

        for (i = pop->size - 2; i >= 0; i--) {
            if ((cumulative_probabilities[i] < u)
                && (cumulative_probabilities[i+1] > u)) {

                /* copy the selected individual into the new population */
                cpychrom(&(selected->individuals[k]),
                         &(pop->individuals[i + 1]),
                         pop->bits);
            }
        }
    }

    /* cleanup allocated memory */
    free(cumulative_probabilities);
    free(relative_probabilities);

    return 0;
}

int survive(population_t *pop, population_t *new)
{
    int i;
    
    qsort(new->individuals, new->size, sizeof(chromosome_t), cmpchromp);

    for (i = (pop->size - 1); i >= 0; i--) {
        if (pop->individuals[pop->size - i - 1].fitness < new->individuals[i].fitness) {
            cpychrom(&(pop->individuals[pop->size - i - 1]),
                     &(new->individuals[i]),
                     pop->bits);
        } else {
            return 0;
        }
    }

    return 0;
}
