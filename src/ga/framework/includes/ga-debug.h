/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
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
 * This function prints the lattice into the console.
 *
 * @param const char* the title of the output 
 * @param double** the 2D lattice
 * @param int the number of rows
 * @param int the number of columns
 */
void printChromosome(const char *title, double **lattice, int r, int c);


#endif /* GA_DEBUG_H */
