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


#define GA_POPSIZE_UNSPECIFIED      11
#define GA_BITS_UNSPECIFIED         12
#define GA_MALLOC_UNSUCCESSFUL      13



typedef struct
{
    unsigned short *allele;
    double fitness;
} chromosome_t;

typedef struct
{
    chromosome_t *individuals;
    int bits;
    int size;
} population_t;


#endif /* GA_H */
