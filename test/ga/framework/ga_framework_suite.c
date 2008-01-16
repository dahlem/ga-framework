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

#include <CUnit/Basic.h>

#ifdef HAVE_LIBGSL
# include <gsl/gsl_rng.h>
#endif

#include "ga_environment_test.h"
#include "ga_population_test.h"
#include "ga_utils_test.h"


int main(int argc, char* argv[])
{
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

#ifdef HAVE_LIBGSL
    gsl_rng_env_setup();
#endif

    registerUtilsTests();
    registerPopulationTests();
    registerEnvironmentTests();
    
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
   
    return CU_get_error();
}
