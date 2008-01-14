/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
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
    *bin = *gray;               

    /* XOR the remaining bits */
    for (i = 0; i < n; ++i) {
        bin--;
        gray--;
        *bin= *(bin + 1)^*gray;   
    }
}


void binarytogray(unsigned short *bin, unsigned short *gray, int n)
{
    int i;

    /* copy the high-order bit */
    *gray = *bin;

    /* XOR the remaining bits */
    for (i = 0; i < n; ++i) {
        gray--;
        bin--;
        *gray= *(bin + 1)^*bin;
    }
}
