/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

/**
 * Declaration of some command-line arguments and a <code>struct</code> for
 * the command-line option values.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GA_CL_H__
#define __GA_CL_H__


/**
 * @defgroup Application Definition of default application settings
 * @{
 */
/**
 * Default mutation rate
 */
#define DEFAULT_MUTATION 0.01

/**
 * Default number of generations
 */
#define DEFAULT_GENERATIONS 100

/**
 * Default population size
 */
#define DEFAULT_POPULATION_SIZE 100

/**
 * Default number of bits
 */
#define DEFAULT_CHROMOSOME_BITS 50

/**
 * Default seed
 */
#define DEFAULT_SEED 2389438

/** @}*/


/**
 * A structure to capture the global arguments passed into application on the
 * command-line.
 */
struct globalArgs_t {
    double mutation_rate; /* mutation rate */
    int generations; /* number of iterations */
    int population_size; /* population size */
    int chromosome_bits; /* number of bits for the chromosomes */
    long seed; /* seed of the random number generator */
} globalArgs;


/**
 * Display the help message for this application.
 */
void displayHelp();

/**
 * Initialise the global parameters.
 */
void init();

/**
 * Process the command-line arguments passed into the application.
 *
 * @param int number of arguments
 * @param char** pointer to the character array representing the command-line
 *               parameters
 */
void process_cl(int argc, char **argv);



#endif
