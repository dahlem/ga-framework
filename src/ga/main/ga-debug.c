/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdio.h>

#include "ga.h"
#include "ga-debug.h"


void printChromosome(const unsigned short *allele, int bits)
{
    int i;

    for (i = 0; i < bits; ++i) {
        printf("%d", allele[i]);
    }
    printf("\n");
}


void printPop(const char *title, population_t *pop)
{
    int i;

    printf("%s:\n", title);

    for (i = 0; i < pop->size; ++i) {
        printChromosome(pop->individuals[i].allele, pop->bits);
    }

    printf("%s done\n", title);
}
