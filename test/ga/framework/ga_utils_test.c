/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */
#include <stdio.h>
#include <stdlib.h>

#include <CUnit/CUnit.h>

#include "utils.h"

#include "ga_utils_test.h"


void registerUtilsTests()
{
    if (CU_register_suites(utils_suites) != CUE_SUCCESS) {
        fprintf(stderr, "Suite registration failed - %s\n", CU_get_error_msg());
        exit(CU_get_error());
    }
}


void testBinToGray()
{
    unsigned short seven_gray[] = {
        0, 0, 0
    };
    unsigned short seven_bin[] = {
        1, 1, 1
    };

    binarytogray((seven_bin + 2), (seven_gray + 2), 3);

    CU_ASSERT_TRUE(seven_gray[2] == 1);
    CU_ASSERT_TRUE(seven_gray[1] == 0);
    CU_ASSERT_TRUE(seven_gray[0] == 0);
}


void testGrayToBin()
{
    unsigned short seven_gray[] = {
        0, 0, 1
    };
    unsigned short seven_bin[] = {
        0, 0, 0
    };

    graytobinary((seven_bin + 2), (seven_gray + 2), 3);

    CU_ASSERT_TRUE(seven_bin[2] == 1);
    CU_ASSERT_TRUE(seven_bin[1] == 1);
    CU_ASSERT_TRUE(seven_bin[0] == 1);
}

void testBinToGrayToBin()
{
    unsigned short seven_gray[] = {
        0, 0, 0
    };
    unsigned short seven_bin[] = {
        1, 1, 1
    };

    binarytogray((seven_bin + 2), (seven_gray + 2), 3);
    seven_gray[1] = 1;
    graytobinary((seven_bin + 2), (seven_gray + 2), 3);

    CU_ASSERT_TRUE(seven_bin[2] == 1);
    CU_ASSERT_TRUE(seven_bin[1] == 0);
    CU_ASSERT_TRUE(seven_bin[0] == 0);
}
