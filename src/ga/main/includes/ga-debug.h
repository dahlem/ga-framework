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
 * Declaration of debug methods.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GA_DEBUG_H__
#define __GA_DEBUG_H__



/**
 * This function prints the chromosome of an individual.
 *
 * @param const unsigned short* the individual to be printed
 * @param int the number of bits in the chromosome
 */
void printChromosome(const unsigned short *allele, int bits);


/**
 * Print the population.
 *
 * @param const char* the title of the print out
 * @param population_t* the population to be printed
 */
void printPop(const char *title, population_t *pop);


#endif /* GA_DEBUG_H */
