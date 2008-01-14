/* Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GA_ENVIRONMENT_TEST_H__
#define __GA_ENVIRONMENT_TEST_H__


#include <CUnit/CUnit.h>


void registerEnvironmentTests();



void testEvaluate();
void testSelection();
void testOnePointCrossover();
void testMutation();


static CU_TestInfo test_env[] = {
    { "testEvaluate", testEvaluate },
    { "testSelection", testSelection },
    { "testOnePointCrossover", testOnePointCrossover },
    { "testMutation", testMutation },
    CU_TEST_INFO_NULL,
};

static CU_SuiteInfo env_suites[] = {
    { "TestGAEnv", NULL, NULL, test_env },
    CU_SUITE_INFO_NULL,
};

#endif
