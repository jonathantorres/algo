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

# Queue
queue_test: queue_test.c queue.o dllist.o
	$(CFLAGS) -Isrc tests/queue_test.c queue.o dllist.o -o queue_test

# Circular linked list
cllist_test: cllist_test.c cllist.o
	$(CFLAGS) -Isrc tests/cllist_test.c cllist.o -o cllist_test

# Array
array_test: array_test.c array.o
	$(CFLAGS) -Isrc tests/array_test.c array.o -o array_test

# Temporary ptr test
ptr_test: ptr_test.c
	$(CFLAGS) -Isrc tests/ptr_test.c -o ptr_test

sllist.o: sllist.c sllist.h
	$(CFLAGS) -c src/sllist.c src/sllist.h

dllist.o: dllist.c dllist.h
	$(CFLAGS) -c src/dllist.c src/dllist.h

cllist.o: cllist.c cllist.h
	$(CFLAGS) -c src/cllist.c src/cllist.h

stack.o: stack.c stack.h
	$(CFLAGS) -c src/stack.c src/stack.h

queue.o: queue.c queue.h
	$(CFLAGS) -c src/queue.c src/queue.h

array.o: array.c array.h
	$(CFLAGS) -c src/array.c src/array.h

.PHONY: test
test: sllist_test dllist_test cllist_test stack_test queue_test array_test ptr_test
	#php tests/run_tests.php
	./sllist_test
	./dllist_test
	./cllist_test
	./stack_test
	./queue_test
	./array_test
	./ptr_test

clean:
	rm ./*.o
	rm src/*.h.gch
	rm ./sllist_test ./dllist_test ./cllist_test
	rm ./stack_test ./queue_test ./array_test ./ptr_test
