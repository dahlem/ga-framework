/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include "utils.h"



void graytobinary(unsigned short *bin, unsigned short *gray, int n)
{
    int i;

    /* copy the high-order bit */
    bin[n - 1] = gray[n -1];

    /* XOR the remaining bits */
    for (i = (n - 2); i >= 0; i--) {
        bin[i]= bin[i + 1]^gray[i];   
    }
}


void binarytogray(unsigned short *bin, unsigned short *gray, int n)
{
    int i;

    /* copy the high-order bit */
    gray[n - 1] = bin[n - 1];

    /* XOR the remaining bits */
    for (i = (n - 2); i >= 0; i--) {
        gray[i]= bin[i + 1]^bin[i];   
    }
}
