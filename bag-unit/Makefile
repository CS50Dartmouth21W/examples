# Makefile for 'bag' module WITH UNIT_TEST
#
# David Kotz, April 2019

PROG = bagtest
OBJS = bagtest.o bag.o readlinep.o memory.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)
CC = gcc
MAKE = make

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(PROG)

unittest: bag.c memory.o 
	$(CC) $(CFLAGS) -DUNIT_TEST bag.c memory.o -o unittest
	./unittest

bagtest.o: bag.h readlinep.h
bag.o: bag.h
readline.o: readlinep.h

.PHONY: test clean

# expects a file `test.names` to exist; it can contain any text.
test: $(PROG) test.names
	./$(PROG) < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: $(PROG) test.names
	valgrind ./$(PROG) < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f unittest

