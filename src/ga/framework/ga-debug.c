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

#include "ga-debug.h"



void printChromosome(const char *title, double **lattice, int r, int c) 
{
#ifdef NDEBUG
    int i, j;
    
    printf("%s\n", title);
    for (i = 0; i < r; ++i) {
        for (j = 0; j < c; ++j) {
            printf("%2.0f  ", lattice[i][j]);
        }
        printf("\n");
    }
    printf("\n");
#endif /* NDEBUG */
}
