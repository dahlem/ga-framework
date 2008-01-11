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
 * Declaration of common structures for the generic algorithm framework.
 *
 * @author Dominik Dahlem (ID: 02175321)
 */
#ifndef __GA_H__
#define __GA_H__


#define POPSIZE_UNSPECIFIED     11
#define BITS_UNSPECIFIED        12



struct chromosome
{
    unsigned short *allele;
    double fitness;
};

typedef struct chromosome chromosome_t;


struct population
{
    chromosome_t *individuals;
    int bits;
    int size;
};

typedef struct population population_t;




#endif /* GA_H */
