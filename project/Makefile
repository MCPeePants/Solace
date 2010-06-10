#SOLACE HAND-WRITTEN MAKEFILE

SHELL = /bin/sh
CC = gcc
CFLAGS =
CPP = gcc -E
CPPFLAGS = -I.
CXX = g++
CXXFLAGS = -g -pedantic -Wall -O2
LD = ld
LDFLAGS = -lsfml-system -lsfml-window -lsfml-graphics
MAKE = make
INSTALL = install

srcdir = src
bindir = bin
objdir = obj
outfile = $(bindir)/solace

# ALL subfolders of src here. Also subfolders of these, if any.
obj_subdirs = core logic math

f_find = $(wildcard obj/($(dir)/*.o))
out_depends = $(foreach dir,$(obj_subdirs),$(f_find)) $(wildcard obj/*.o)
# out_depends contains all object files if obj_subdirs contains all
# directories that contain object files!

all: $(outfile)

$(outfile):	$(out_depends)
	$(CXX) -o $(outfile) $(out_depends) $(CXXFLAGS) $(LDFLAGS)

$(objdir)/%.o:	$(srcdir)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) $(objdir)/*.o
	$(RM) $(bindir)/*

.PHONY: clean
