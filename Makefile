VPATH = src tests
CFLAGS = gcc -Wall -Wextra

all: test

# Singly linked list
sllist_test: sllist_test.c sllist.o
	$(CFLAGS) -Isrc tests/sllist_test.c sllist.o -o sllist_test

# Doubly linked list
dllist_test: dllist_test.c dllist.o
	$(CFLAGS) -Isrc tests/dllist_test.c dllist.o -o dllist_test

# Stack
stack_test: stack_test.c stack.o dllist.o
	$(CFLAGS) -Isrc tests/stack_test.c stack.o dllist.o -o stack_test

# Circular linked list
cllist_test: cllist_test.c cllist.o
	$(CFLAGS) -Isrc tests/cllist_test.c cllist.o -o cllist_test

sllist.o: sllist.c sllist.h
	$(CFLAGS) -c src/sllist.c src/sllist.h

dllist.o: dllist.c dllist.h
	$(CFLAGS) -c src/dllist.c src/dllist.h

cllist.o: cllist.c cllist.h
	$(CFLAGS) -c src/cllist.c src/cllist.h

stack.o: stack.c stack.h
	$(CFLAGS) -c src/stack.c src/stack.h

.PHONY: test
test: sllist_test dllist_test cllist_test stack_test
	php tests/run_tests.php

clean:
	rm ./*.o
	rm src/*.h.gch
	rm ./sllist_test ./dllist_test ./cllist_test ./stack_test
