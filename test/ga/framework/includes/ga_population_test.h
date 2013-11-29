/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GA_POPULATION_TEST_H__
#define __GA_POPULATION_TEST_H__


#include <CUnit/CUnit.h>

#include "setup.h"


int init_pop();
int clean_pop();

void registerPopulationTests();

void testCpypop();
void testCpychrom();
void testPopsizeUnspecified();
void testBitsUnspecified();
void testInit();


static CU_TestInfo test_pop[] = {
    { "testCpychrom", testCpychrom },
    { "testCpypop", testCpypop },
    { "testPopsizeUnspecified", testPopsizeUnspecified },
    { "testBitsUnspecified", testBitsUnspecified },
    { "testInit", testInit },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo pop_suites[] = {
    { "TestGAPop", init_pop, clean_pop, test_pop },
    CU_SUITE_INFO_NULL,
};

#endif
