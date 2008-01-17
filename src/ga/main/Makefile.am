# Copyright (C) 2008 Dominik Dahlem <Dominik.Dahlem@cs.tcd.ie>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = gamain

gamain_SOURCES =                                                      \
	ga-debug.c                                                    \
	ga-cl.c                                                       \
	main.c

gamain_CPPFLAGS =                                                     \
	-I./includes                                                  \
	-I$(top_srcdir)/src/ga/framework/includes


LDADD =                                                               \
	$(top_srcdir)/src/ga/framework/libgaframework.la              \
	$(GSL_LIBS)


include_HEADERS = includes
MAINTAINERCLEANFILES = Makefile.in

# compile with mpi
CC = $(MPICC)
LIBS += $(MPILIBS)
