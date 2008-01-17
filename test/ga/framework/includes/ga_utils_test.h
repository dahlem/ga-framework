/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GA_UTILS_TEST_H__
#define __GA_UTILS_TEST_H__


#include <CUnit/CUnit.h>


void registerUtilsTests();



void testGrayToBin();
void testBinToGray();
void testBinToGrayToBin();


static CU_TestInfo test_utils[] = {
    { "testGrayToBin", testGrayToBin },
    { "testBinToGray", testBinToGray },
    { "testBinToGrayToBin", testBinToGrayToBin },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo utils_suites[] = {
    { "TestGAUtils", NULL, NULL, test_utils },
    CU_SUITE_INFO_NULL,
};

#endif
