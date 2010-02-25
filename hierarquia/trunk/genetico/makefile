# -*- Mode: makefile -*-
# Copyright (c) 1999 Matthew Wall, all rights reserved
# -----------------------------------------------------------------------------
#   To make all of the examples, do 'make'.  You can compile any one of
# the examples by typing 'make exN' where N is the number of the example you
# want to compile.  See the README for a description of what each example does.
# -----------------------------------------------------------------------------
GALIB_DIR= /home/fabio/mestrado/codigos/galib247

include $(GALIB_DIR)/makevars
# Set these paths to the location of the GA library and headers.
#GA_INC_DIR= /usr/local/include
#GA_LIB_DIR= /usr/local/lib
GA_INC_DIR= $(GALIB_DIR)
GA_LIB_DIR= $(GALIB_DIR)/ga

INC_DIRS= -I$(GA_INC_DIR)
LIB_DIRS= -L$(GA_LIB_DIR)

SHELL= /bin/sh

BIN= hierarquia
FFLAGS= -c
LFLAGS= -lga -lm -lc -O2 -static -lglpk -lgmp -lz
# -lg2c # for mixed fortran codes... I think! (Toddy)

OBJ= matrix.o ram.o instancia.o hierarquia.o hierarquiaGA.o rede.o hierarquiaOOMain.o

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $(BIN) $(LIB_DIRS) $(CXX_LIBS) $(LFLAGS)

.SUFFIXES: .C .f .c .o

.C.o:
	$(CXX) $(CXXFLAGS) $(INC_DIRS) -c $< 

.f.o:
	$(GFF) -c $<

.c.o:
	gcc -c $<

all: $(BIN)

clean:
	$(RM) *.o *~ *.aux	

end: 
	$(RM) $(BIN) *.o *~

	