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
#include <unistd.h>

#include "ga-cl.h"


/**
 * getopt configuration of the command-line parameters.
 * All command-line arguments are optional.
 * Arguments p, e, and m are passed in by the MPI environment, we ignore
 * those, but the have to be specified.
 */
static const char *cl_arguments = "uh?r:g:s:c:p:e:m:d:";



void displayHelp()
{
    printf("gamain - run a simple ga algorithm goal is to maximise the fitness function\n");
    printf("         which counts the 1s in the chromosomes.\n");
    printf(" -r : Mutation rate.\n");
    printf(" -g : The number of generations.\n");
    printf(" -s : The size of the population.\n");
    printf(" -c : The number of bits in the chromosomes.\n");
    printf(" -d : The random number seed for the srand48 function.\n");
    printf(" -? : This help message.\n");
    printf(" -h : This help message.\n");

    exit(EXIT_SUCCESS);
}


void init()
{
    globalArgs.mutation_rate = DEFAULT_MUTATION;
    globalArgs.generations = DEFAULT_GENERATIONS;
    globalArgs.population_size = DEFAULT_POPULATION_SIZE;
    globalArgs.chromosome_bits = DEFAULT_CHROMOSOME_BITS;
    globalArgs.seed = DEFAULT_SEED;
}


/**
 * Verify the command line arguments and check that they are consistent with each
 * other.
 */
void verify_cl() 
{
    if ((globalArgs.mutation_rate < 0)
        ||(globalArgs.mutation_rate > 1)) {
        fprintf(stderr, "Error: The mutation rate has to be in the range [0;1].\n\n");
        displayHelp();
    }
    if (globalArgs.generations < 1) {
        fprintf(stderr, "Error: The number of generations has to be >= 1.\n\n");
        displayHelp();
    }
    if (globalArgs.population_size < 1) {
        fprintf(stderr, "Error: The size of the population has to >= 1.\n\n");
        displayHelp();
    }
    if (globalArgs.chromosome_bits < 1) {
        fprintf(stderr, "Error: The size of the population has to be >= 1.\n\n");
        displayHelp();
    }
    if (globalArgs.seed < 1) {
        fprintf(stderr, "Error: The random number seed has to be >= 1.\n\n");
        displayHelp();
    }
}


void process_cl(int argc, char **argv)
{
    int opt = 0;

    opt = getopt(argc, argv, cl_arguments);

    while (opt != -1) {
        switch (opt) {
            case 'r':
                globalArgs.mutation_rate = atof(optarg);
                break;
            case 'g':
                globalArgs.generations = atoi(optarg);
                break;
            case 's':
                globalArgs.population_size = atoi(optarg);
                break;
            case 'c':
                globalArgs.chromosome_bits = atoi(optarg);
                break;
            case 'd':
                globalArgs.seed = atol(optarg);
                break;
            case 'p':
                break;
            case 'e':
                break;
            case 'm':
                break;
            case 'h':
            case '?':
                 displayHelp();
                 break;
            default:
                 break;
        }
        opt = getopt(argc, argv, cl_arguments);
    }

    verify_cl();
}
