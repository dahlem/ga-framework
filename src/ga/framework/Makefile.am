# Copyright (C) 2007 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

noinst_LTLIBRARIES = libgaframework.la

libgaframework_la_SOURCES =                                           \
	utils.c                                                       \
	environment.c                                                 \
	population.c

libgaframework_la_CPPFLAGS = -I./includes

libgaframework_la_LIBADD =                                            \
	$(GSL_LIBS)

include_HEADERS = includes

# compile with mpi
CC = $(MPICC)
LIBS += $(MPILIBS)
