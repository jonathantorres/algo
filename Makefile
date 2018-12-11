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

# Circular Buffer
cbuffer_test: cbuffer_test.c cbuffer.o
	$(CFLAGS) -Isrc tests/cbuffer_test.c cbuffer.o -o cbuffer_test

# Bubble Sort
bubble_sort_test: bubble_sort_test.c bubble_sort.o array.o
	$(CFLAGS) -Isrc tests/bubble_sort_test.c bubble_sort.o array.o -o bubble_sort_test

# Insertion Sort
insertion_sort_test: insertion_sort_test.c insertion_sort.o array.o
	$(CFLAGS) -Isrc tests/insertion_sort_test.c insertion_sort.o array.o -o insertion_sort_test

# Selection Sort
selection_sort_test: selection_sort_test.c selection_sort.o array.o
	$(CFLAGS) -Isrc tests/selection_sort_test.c selection_sort.o array.o -o selection_sort_test

# Merge Sort
merge_sort_test: merge_sort_test.c merge_sort.o array.o
	$(CFLAGS) -Isrc tests/merge_sort_test.c merge_sort.o array.o -o merge_sort_test

# Quick Sort
quick_sort_test: quick_sort_test.c quick_sort.o array.o
	$(CFLAGS) -Isrc tests/quick_sort_test.c quick_sort.o array.o -o quick_sort_test

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

cbuffer.o: cbuffer.c cbuffer.h
	$(CFLAGS) -c src/cbuffer.c src/cbuffer.h

bubble_sort.o: bubble_sort.c bubble_sort.h
	$(CFLAGS) -c src/bubble_sort.c src/bubble_sort.h

insertion_sort.o: insertion_sort.c insertion_sort.h
	$(CFLAGS) -c src/insertion_sort.c src/insertion_sort.h

selection_sort.o: selection_sort.c selection_sort.h
	$(CFLAGS) -c src/selection_sort.c src/selection_sort.h

merge_sort.o: merge_sort.c merge_sort.h
	$(CFLAGS) -c src/merge_sort.c src/merge_sort.h

quick_sort.o: quick_sort.c quick_sort.h
	$(CFLAGS) -c src/quick_sort.c src/quick_sort.h

.PHONY: test
test: sllist_test dllist_test cllist_test stack_test queue_test array_test bubble_sort_test insertion_sort_test selection_sort_test merge_sort_test quick_sort_test cbuffer_test
	#php tests/run_tests.php
	./sllist_test
	./dllist_test
	./cllist_test
	./stack_test
	./queue_test
	./array_test
	./bubble_sort_test
	./insertion_sort_test
	./selection_sort_test
	./merge_sort_test
	./quick_sort_test
	./cbuffer_test

clean:
	rm ./*.o
	rm src/*.h.gch
	rm ./sllist_test ./dllist_test ./cllist_test
	rm ./stack_test ./queue_test ./array_test
	rm ./bubble_sort_test ./insertion_sort_test ./selection_sort_test
	rm ./merge_sort_test ./quick_sort_test ./cbuffer_test
