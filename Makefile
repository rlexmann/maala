SDIR=src
IDIR=include
LDIR=lib
CC=g++
CFLAGS=-I$(IDIR) -Wall

_HEADERS = matrix.hpp
HEADERS = $(patsubst %,$(IDIR)/%,$(_HEADERS))

_SOURCES = matrix.cpp main.cpp
SOURCES = $(patsubst %,$(SDIR)/%,$(_SOURCES))

.PHONY: all
all: main.exe

main.exe: $(SOURCES) $(HEADERS)
	@$(CC) -o $@ $(SOURCES) $(CFLAGS)

.PHONY: clean

clean:
	@rm *.exe
