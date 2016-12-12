# Copyright 1995 JAIST Thanaruk Theeramunkong
#
# Top-level Makefile for Chart Parser in C.
# Date of Confuguration: Wed Nov  1 23:49:08 JST 1995
# Configured by: Thanaruk Theeramunkong (ping@jaist.ac.jp)

########################################
# Program Name
########################################

# Include file directory
CHART     = chart
CHARTILL  = chartill
CHARTTH     = chart-th
CHARTILLTH  = chartill-th
CHARTPURE = chartpure
GRAMNAME  = gram
GRAMHEAD  = gram.h

# Thai grammar
GRAMNAMETH  = gram.th
GRAMHEADTH  = gram-th.h
##############

GRAMCOMP  = gcompile

GRAMPURENAME = grampure
GRAMPUREHEAD = grampure.h

########################################
# Directory Names
########################################

# source file directory
SRCDIR = src

# gram file directory
GRAMDIR = gram

# gram compiler directory
COMPDIR  = gcompile


#####################################
# System-dependent switches
########################################

# LN: link command to use for system compilation.
LN = ln -s

# KL1CMP: KL1 to C compiler used for compiling the self compiler.
# Only for system developers and not for normal users.
KL1CMP = false

# C compiler
CC = gcc

# LD link editor
LD = gcc 

# Optimization flags for compiling the runtime system by CC.
OPTLEVEL = 2
OPTFLAGS = -O2 -fomit-frame-pointer
KLICOPT = -O2 -g
DEBUGFLAGS = -g

# Additional CC flags for optimized compilation of KL1 programs.
UOPTFLAGS = -fomit-frame-pointer

# Library search flags
LIBSWITCHES = -L/usr/local/lib -L/usr/lib -L/lib   -lm
LDFLAGS=$(LIBSWITCHES)

# Library archive indexer
RANLIB = ranlib

# Make program
MAKE = make

# Installer
INSTALL = /bin/cp -p
INSTDIR = /bin/mkdir -p
INSTALLHDR = /bin/cp -p

# Maximum parallelism in compilation
PARALLEL = 0
 
# Copyright 1995 JAIST Thanaruk Theeramunkong
#
# = Main Script =
#
# Site-specific definitions will be prepended to this
# by the configuration script

CFLAGS=$(OPTFLAGS) $(DEBUGFLAGS)
LDFLAGS=$(LIBSWITCHES)

OBJS1 = $(SRCDIR)/chart.o $(SRCDIR)/io.o $(SRCDIR)/mem.o $(SRCDIR)/trancat.o
OBJS2 = $(SRCDIR)/chartill.o $(SRCDIR)/io.o $(SRCDIR)/memill.o \
	$(SRCDIR)/trancat.o
OBJS3 = $(SRCDIR)/chartpure.o $(SRCDIR)/io.o $(SRCDIR)/mem.o \
        $(SRCDIR)/trancatpure.o
# Additional for Thai language
OBJS4 = $(SRCDIR)/chart-th.o $(SRCDIR)/io.o $(SRCDIR)/mem.o $(SRCDIR)/trancat-th.o
OBJS5 = $(SRCDIR)/chartill-th.o $(SRCDIR)/io.o $(SRCDIR)/memill.o \
	$(SRCDIR)/trancat-th.o

all	  : $(CHART) $(CHARTILL) $(CHARTPURE) $(CHARTTH) $(CHARTILLTH)

$(CHART): $(OBJS1)
	$(CC) -o $@ $(OBJS1)

$(CHARTILL): $(OBJS2)
	$(CC) -o $@ $(OBJS2)

$(CHARTPURE): $(OBJS3)
	$(CC) -o $@ $(OBJS3)

$(CHARTTH): $(OBJS4)
	$(CC) -o $@ $(OBJS4)

$(CHARTILLTH): $(OBJS5)
	$(CC) -o $@ $(OBJS5)

$(SRCDIR)/$(GRAMHEAD): $(GRAMDIR)/$(GRAMNAME) $(COMPDIR)/$(GRAMCOMP)
	/bin/rm -f $(SRCDIR)/$(GRAMHEAD)
	$(COMPDIR)/$(GRAMCOMP) < '$(GRAMDIR)/$(GRAMNAME)' > \
					'$(SRCDIR)/$(GRAMHEAD)'

# Thai grammar
$(SRCDIR)/$(GRAMHEADTH): $(GRAMDIR)/$(GRAMNAMETH) $(COMPDIR)/$(GRAMCOMP)
	/bin/rm -f $(SRCDIR)/$(GRAMHEADTH)
	$(COMPDIR)/$(GRAMCOMP) < '$(GRAMDIR)/$(GRAMNAMETH)' > \
					'$(SRCDIR)/$(GRAMHEADTH)'

$(SRCDIR)/$(GRAMPUREHEAD): $(GRAMDIR)/$(GRAMPURENAME) $(COMPDIR)/$(GRAMCOMP)
	/bin/rm -f $(SRCDIR)/$(GRAMPUREHEAD)
	$(COMPDIR)/$(GRAMCOMP) < '$(GRAMDIR)/$(GRAMPURENAME)' > \
					'$(SRCDIR)/$(GRAMPUREHEAD)'

$(COMPDIR)/$(GRAMCOMP): $(COMPDIR)/$(GRAMCOMP).c
	$(CC) -o $(COMPDIR)/$(GRAMCOMP) $(CFLAGS) $(COMPDIR)/$(GRAMCOMP).c

$(SRCDIR)/chart.o: $(SRCDIR)/chart.c $(SRCDIR)/chart.h \
		   $(SRCDIR)/def.h $(SRCDIR)/$(GRAMHEAD)
	$(CC) -c -o $(SRCDIR)/chart.o $(CFLAGS) $(SRCDIR)/chart.c

$(SRCDIR)/chartill.o: $(SRCDIR)/chartill.c $(SRCDIR)/chart.h \
		      $(SRCDIR)/def.h $(SRCDIR)/$(GRAMHEAD)
	$(CC) -c -o $(SRCDIR)/chartill.o $(CFLAGS) $(SRCDIR)/chartill.c

# Chart Thai
$(SRCDIR)/chart-th.o: $(SRCDIR)/chart-th.c $(SRCDIR)/chart-th.h \
		   $(SRCDIR)/def.h $(SRCDIR)/$(GRAMHEADTH)
	$(CC) -c -o $(SRCDIR)/chart-th.o $(CFLAGS) $(SRCDIR)/chart-th.c

# Chartill Thai
$(SRCDIR)/chartill-th.o: $(SRCDIR)/chartill-th.c $(SRCDIR)/chart-th.h \
		      $(SRCDIR)/def.h $(SRCDIR)/$(GRAMHEADTH)
	$(CC) -c -o $(SRCDIR)/chartill-th.o $(CFLAGS) $(SRCDIR)/chartill-th.c

$(SRCDIR)/chartpure.o: $(SRCDIR)/chartpure.c $(SRCDIR)/chart.h \
		   $(SRCDIR)/def.h $(SRCDIR)/$(GRAMPUREHEAD)
	$(CC) -c -o $(SRCDIR)/chartpure.o $(CFLAGS) $(SRCDIR)/chartpure.c

$(SRCDIR)/io.o: $(SRCDIR)/io.c
	$(CC) -c -o $(SRCDIR)/io.o $(CFLAGS) $(SRCDIR)/io.c

$(SRCDIR)/mem.o: $(SRCDIR)/mem.c $(SRCDIR)/def.h $(SRCDIR)/chart.h 
	$(CC) -c -o $(SRCDIR)/mem.o $(CFLAGS) $(SRCDIR)/mem.c

$(SRCDIR)/memill.o: $(SRCDIR)/memill.c  $(SRCDIR)/def.h $(SRCDIR)/chart.h 
	$(CC) -c -o $(SRCDIR)/memill.o $(CFLAGS) $(SRCDIR)/memill.c

$(SRCDIR)/trancat.o: $(SRCDIR)/trancat.c $(SRCDIR)/$(GRAMHEAD) $(SRCDIR)/def.h 
	$(CC) -c -o $(SRCDIR)/trancat.o $(CFLAGS) $(SRCDIR)/trancat.c

# Thai
$(SRCDIR)/trancat-th.o: $(SRCDIR)/trancat-th.c $(SRCDIR)/$(GRAMHEADTH) $(SRCDIR)/def.h 
	$(CC) -c -o $(SRCDIR)/trancat-th.o $(CFLAGS) $(SRCDIR)/trancat-th.c

$(SRCDIR)/trancatpure.o: $(SRCDIR)/trancatpure.c $(SRCDIR)/$(GRAMPUREHEAD) \
	$(SRCDIR)/def.h 
	$(CC) -c -o $(SRCDIR)/trancatpure.o $(CFLAGS) $(SRCDIR)/trancatpure.c

# Delete useless files

clean :
	rm -f *.o
	cd $(SRCDIR) ; rm -f *.o
	cd $(COMPDIR) ; rm -f *.o
