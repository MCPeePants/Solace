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

srcdir = ../src
bindir = ../bin
objdir = ../obj
outfile = $(bindir)/solace

all: $(outfile)

$(outfile):	$(objdir)/main.o
	$(CXX) -o $(outfile) $(srcdir)/*.o $(CXXFLAGS) $(LDFLAGS)

$(objdir)/%.o:	$(srcdir)/%.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $^ -o $@

clean:
	$(RM) $(srcdir)/*.o

.PHONY: clean
