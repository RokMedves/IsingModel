# makefile inspired by
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#
# Rok Medves 10. 10. 2020
# Oxford

# special symbols explained:
# sym   example    meaning
# ------------------------
# %     [%.o, %.]  wildcard for file name
# $@    [$@]       contents left  of ':' symbol
# $^    [$^]       contents right of ':' symbol
# $<    [$<]       first item in dependencies list

# the c++ compiler to use
CC=gcc

# flags;
# -I.        ->  included .hh files in ./ dir
# -std=c++11 ->  use c++11
# -Wall      ->  display all warnings
# -g         ->  binaries suitable for gdb debugging
CFLAG= -I. -std=c++11 -Wall -g

# flags for compiling object files
OFLAGS= -g

# the objects
OBJ=lattice.o ising.o main.o

# aditional dependancies
DEPS=

# executable name
EXE=output

# recipe for creating the objects
%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(OFLAGS)

# main program; just combines the binaries
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


# this keeps make from doing anything with a file named 'clean'
.PHONY: clean

# clean function
clean:
	rm *.o
