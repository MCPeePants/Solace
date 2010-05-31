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
outfile = $(bindir)/solace

all: $(outfile)

$(outfile):	$(srcdir)/main.o
	$(CXX) -o $(outfile) $(srcdir)/*.o $(CXXFLAGS) $(LDFLAGS)

clean:
	$(RM) $(srcdir)/*.o

.PHONY: clean
