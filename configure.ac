# Copyright (C) 2008, 2013 Dominik Dahlem <Dominik.Dahlem@gmail.com>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([HPC Genetic Algorithm Framework],
        [1.0],
        [Dominik Dahlem Dominik.Dahlem@gmail.com], 
        [GA-framework])


AC_CONFIG_AUX_DIR(config)
AC_CONFIG_SRCDIR([config.h.in])

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE([foreign])


# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

CFLAGS="-W -Wall -pedantic ${CFLAGS}"

LF_CONFIGURE_CC
LF_HOST_TYPE
LF_SET_WARNINGS

AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h sys/time.h unistd.h limits.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_HEADER_STDBOOL
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday memset])

# GSL library checks
# enable gsl?
AC_ARG_ENABLE(gsl, AS_HELP_STRING(
		     [--enable-gsl], 
		     [enable test @<:@default=no@:>@]), 
		     [GSLLIB=$enableval], [GSLLIB=no])

if test x$GSLLIB = xyes; then
   AC_CHECK_LIB([m],[cos])
   AC_CHECK_LIB([gslcblas],[cblas_dgemm])
   AC_CHECK_LIB([gsl],[gsl_blas_dgemm])
fi

# enable cunit?
AC_ARG_ENABLE(test, AS_HELP_STRING(
		     [--enable-test], 
		     [enable test @<:@default=no@:>@]), 
		     [TESTING=$enableval], [TESTING=no])

# Check for cunit
if test x$TESTING = xyes; then
   AC_CHECK_LIB(cunit, CU_initialize_registry, HAVE_CUNIT="yes")
   AC_CHECK_FUNCS([pow])

   if test x$HAVE_CUNIT != xyes; then
	AC_MSG_WARN([CUnit not found. Tests cannot be run.])
   fi
fi
AM_CONDITIONAL(HAVE_CUNIT, test "x$HAVE_CUNIT" = xyes)


# optional libraries
AC_GCOV


# Check for MPI
AC_ARG_ENABLE(mpi, AS_HELP_STRING(
		   [--enable-mpi], 
		   [enable MPI @<:@default=no@:>@]), 
		   [USE_MPI=$enableval], [USE_MPI=no])
if test "x$USE_MPI" = xyes; then
   ACX_MPI([], [AC_MSG_ERROR([cannot configure MPI (required for parallel 2D heat equations)])])
else
   MPICC="${CC}"
   AC_SUBST(MPICC)
fi
AM_CONDITIONAL(COMPILE_PARALLEL, test "x$USE_MPI" = xyes)

# Check for debug
AC_ARG_ENABLE(debug, AS_HELP_STRING(
		     [--enable-debug], 
		     [enable debug @<:@default=no@:>@]), 
		     [DEBUGGING=$enableval], [DEBUGGING=no])
if test "x$DEBUGGING" = xyes; then
  AC_DEFINE(NDEBUG, 1, [define debugging, if enabled])
fi


DX_DOXYGEN_FEATURE([ON])
DX_HTML_FEATURE([ON])
DX_CHM_FEATURE([OFF])
DX_CHI_FEATURE([OFF])
DX_MAN_FEATURE([OFF])
DX_RTF_FEATURE([OFF])
DX_XML_FEATURE([OFF])
DX_PDF_FEATURE([OFF])
DX_PS_FEATURE([OFF])
DX_INIT_DOXYGEN([GA-framework], [Doxyfile], [doc/doxygen])


AC_CONFIG_FILES([
   Makefile
   src/Makefile
   src/ga/Makefile
   src/ga/framework/Makefile
   src/ga/main/Makefile
   test/Makefile
   test/ga/Makefile
   test/ga/framework/Makefile
])


AC_OUTPUT

for top_builddir in . .. ../.. $ac_auxdir $ac_auxdir/..; do
  test -f $top_builddir/configure && break
done

AC_MSG_RESULT([

$PACKAGE $VERSION: Automatic configuration OK.

Type 'make' to compile this project.

])
