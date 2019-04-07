VPATH = src tests bin
CFLAGS = gcc -std=c11 -Wall -Wextra -Isrc
CPPFLAGS = g++ -std=c++11 -Wall -Wextra -Isrc
SOURCES = $(wildcard src/*.c)
OBJECTS = $(subst .c,.o, $(SOURCES))
HEADERS = $(subst .c,.h, $(SOURCES))
TESTS = $(wildcard tests/*_test.c)
TESTFILES := $(subst .c, , $(TESTS))
TESTFILES := $(subst tests/, , $(TESTFILES))

all: hangman stream_server stream_client http_server test

# Compile objects
$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CFLAGS) -c $(SOURCES) $(HEADERS)

# Hangman game
hangman: hangman/hangman.cpp
	$(CPPFLAGS) src/hangman/hangman.cpp -o bin/hangman
	cp src/hangman/words.txt bin/words.txt

# Daytime server/client
daytime_server: net/daytime_server.c
	$(CFLAGS) src/net/daytime_server.c -o bin/daytime_server

daytime_client: net/daytime_client.c
	$(CFLAGS) src/net/daytime_client.c -o bin/daytime_client

# Stream server/client
stream_server: net/stream_server.c
	$(CFLAGS) src/net/stream_server.c -o bin/stream_server

stream_client: net/stream_client.c
	$(CFLAGS) src/net/stream_client.c -o bin/stream_client

# Http server
http_server: net/http_server.c
	$(CFLAGS) src/net/http_server.c -o bin/http_server

# Singly linked list
sllist_test: sllist_test.c sllist.o
	$(CFLAGS) tests/sllist_test.c sllist.o -o bin/sllist_test

# Doubly linked list
dllist_test: dllist_test.c dllist.o
	$(CFLAGS) tests/dllist_test.c dllist.o -o bin/dllist_test

# Stack
stack_test: stack_test.c stack.o dllist.o
	$(CFLAGS) tests/stack_test.c stack.o dllist.o -o bin/stack_test

# Queue
queue_test: queue_test.c queue.o dllist.o
	$(CFLAGS) tests/queue_test.c queue.o dllist.o -o bin/queue_test

# Circular linked list
cllist_test: cllist_test.c cllist.o
	$(CFLAGS) tests/cllist_test.c cllist.o -o bin/cllist_test

# Array
array_test: array_test.c array.o
	$(CFLAGS) tests/array_test.c array.o -o bin/array_test

# Circular Buffer
cbuffer_test: cbuffer_test.c cbuffer.o
	$(CFLAGS) tests/cbuffer_test.c cbuffer.o -o bin/cbuffer_test

# Hash Table
htable_test: htable_test.c htable.o array.o
	$(CFLAGS) tests/htable_test.c htable.o array.o -o bin/htable_test

# Trie
trie_test: trie_test.c trie.o array.o
	$(CFLAGS) tests/trie_test.c trie.o array.o -o bin/trie_test

# Bubble Sort
bubble_sort_test: bubble_sort_test.c bubble_sort.o array.o
	$(CFLAGS) tests/bubble_sort_test.c bubble_sort.o array.o -o bin/bubble_sort_test

# Insertion Sort
insertion_sort_test: insertion_sort_test.c insertion_sort.o array.o
	$(CFLAGS) tests/insertion_sort_test.c insertion_sort.o array.o -o bin/insertion_sort_test

# Selection Sort
selection_sort_test: selection_sort_test.c selection_sort.o array.o
	$(CFLAGS) tests/selection_sort_test.c selection_sort.o array.o -o bin/selection_sort_test

# Merge Sort
merge_sort_test: merge_sort_test.c merge_sort.o array.o
	$(CFLAGS) tests/merge_sort_test.c merge_sort.o array.o -o bin/merge_sort_test

# Quick Sort
quick_sort_test: quick_sort_test.c quick_sort.o array.o
	$(CFLAGS) tests/quick_sort_test.c quick_sort.o array.o -o bin/quick_sort_test

# Binary Search
binary_search_test: binary_search_test.c binary_search.o array.o
	$(CFLAGS) tests/binary_search_test.c binary_search.o array.o -o bin/binary_search_test

# Run tests
.PHONY: test
test: $(TESTFILES)
	./bin/sllist_test
	./bin/dllist_test
	./bin/cllist_test
	./bin/stack_test
	./bin/queue_test
	./bin/array_test
	./bin/bubble_sort_test
	./bin/insertion_sort_test
	./bin/selection_sort_test
	./bin/merge_sort_test
	./bin/quick_sort_test
	./bin/binary_search_test
	./bin/cbuffer_test
	./bin/htable_test
	./bin/trie_test

clean:
	rm -f ./*.o src/*.h.gch ./bin/*
