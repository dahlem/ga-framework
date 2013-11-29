/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
/**
 * Declaration of common structures for the generic algorithm framework.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GA_H__
#define __GA_H__


/**
 * @defgroup Errors
 * @{
 */
/**
 * Error if the population size is not specified
 */
#define GA_POPSIZE_UNSPECIFIED      11

/**
 * Error if the number of bits are not specified
 */
#define GA_BITS_UNSPECIFIED         12

/**
 * Error if memory allocation was not successful
 */
#define GA_MALLOC_UNSUCCESSFUL      13

/** @}*/



/**
 * A structure to capture information about a chromosome.
 */
typedef struct
{
    unsigned short *allele; /* the alleles (bits) of the chromosome */
    double fitness; /* the fitness of the chromosome */
} chromosome_t;


/**
 * A structure to capture information about a population.
 */
typedef struct
{
    chromosome_t *individuals; /* array of chromosomes */
    int bits; /* the number of bits represented within the chromosomes */
    int size; /* the size of the population */
    double cum_fit; /* cumulative fitness of the whole population */
} population_t;


#endif /* GA_H */
