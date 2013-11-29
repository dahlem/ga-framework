/* Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@gmail.com>                */
/*                                                                             */
/* This file is free software; as a special exception the author gives         */
/* unlimited permission to copy and/or distribute it, with or without          */
/* modifications, as long as this notice is preserved.                         */
/*                                                                             */
/* This program is distributed in the hope that it will be useful, but         */
/* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the      */
/* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    */

#ifndef __GA_SETUP_H__
#define __GA_SETUP_H__


#ifdef HAVE_LIBGSL

#include <gsl/gsl_rng.h>


static gsl_rng_type *rng_type_test = NULL;
static gsl_rng *rng_test = NULL;

#endif /* HAVE_LIBGSL */


#endif
