VPATH = src tests bin
CFLAGS = gcc -g -std=gnu11 -Wall -Wextra -Isrc
CPPFLAGS = g++ -std=c++11 -Wall -Wextra -Isrc
SOURCES = $(wildcard src/*.c)
OBJECTS = $(subst .c,.o, $(SOURCES))
HEADERS = $(subst .c,.h, $(SOURCES))
TESTS = $(wildcard tests/*_test.c)
TESTFILES := $(subst .c, , $(TESTS))
TESTFILES := $(subst tests/, , $(TESTFILES))

all: test hangman stream_server stream_client http_server

# Compiling executables
hangman: hangman/hangman.c array.o
	$(CFLAGS) src/hangman/hangman.c array.o -o bin/hangman
	cp src/hangman/words.txt bin/words.txt
daytime_server: net/daytime_server.c
	$(CFLAGS) src/net/daytime_server.c -o bin/daytime_server
daytime_client: net/daytime_client.c
	$(CFLAGS) src/net/daytime_client.c -o bin/daytime_client
stream_server: net/stream_server.c
	$(CFLAGS) src/net/stream_server.c -o bin/stream_server
stream_client: net/stream_client.c
	$(CFLAGS) src/net/stream_client.c -o bin/stream_client
http_server: net/http_server.c
	$(CFLAGS) src/net/http_server.c -o bin/http_server
http_server_nonblock: net/http_server_nonblock.c
	$(CFLAGS) src/net/http_server_nonblock.c -o bin/http_server_nonblock
http_server_image: net/http_server_image.c
	$(CFLAGS) src/net/http_server_image.c -o bin/http_server_image
sl_list_test: sl_list_test.c sl_list.o
	$(CFLAGS) tests/sl_list_test.c sl_list.o -o bin/sl_list_test
dl_list_test: dl_list_test.c dl_list.o
	$(CFLAGS) tests/dl_list_test.c dl_list.o -o bin/dl_list_test
cl_list_test: cl_list_test.c cl_list.o
	$(CFLAGS) tests/cl_list_test.c cl_list.o -o bin/cl_list_test
stack_test: stack_test.c stack.o dl_list.o
	$(CFLAGS) tests/stack_test.c stack.o dl_list.o -o bin/stack_test
queue_test: queue_test.c queue.o dl_list.o
	$(CFLAGS) tests/queue_test.c queue.o dl_list.o -o bin/queue_test
array_test: array_test.c array.o
	$(CFLAGS) tests/array_test.c array.o -o bin/array_test
c_buffer_test: c_buffer_test.c c_buffer.o
	$(CFLAGS) tests/c_buffer_test.c c_buffer.o -o bin/c_buffer_test
h_table_test: h_table_test.c h_table.o array.o
	$(CFLAGS) tests/h_table_test.c h_table.o array.o -o bin/h_table_test
trie_test: trie_test.c trie.o array.o
	$(CFLAGS) tests/trie_test.c trie.o array.o -o bin/trie_test
bs_tree_test: bs_tree_test.c bs_tree.o
	$(CFLAGS) tests/bs_tree_test.c bs_tree.o -o bin/bs_tree_test
bs_tree_map_test: bs_tree_map_test.c bs_tree_map.o
	$(CFLAGS) tests/bs_tree_map_test.c bs_tree_map.o -o bin/bs_tree_map_test
rb_tree_test: rb_tree_test.c rb_tree.o
	$(CFLAGS) tests/rb_tree_test.c rb_tree.o -o bin/rb_tree_test
rb_tree_map_test: rb_tree_map_test.c rb_tree_map.o
	$(CFLAGS) tests/rb_tree_map_test.c rb_tree_map.o -o bin/rb_tree_map_test
graph_test: graph_test.c graph.o queue.o stack.o dl_list.o array.o
	$(CFLAGS) tests/graph_test.c graph.o dl_list.o queue.o stack.o array.o -o bin/graph_test
p_queue_test: p_queue_test.c p_queue.o bs_tree.o
	$(CFLAGS) tests/p_queue_test.c p_queue.o bs_tree.o -o bin/p_queue_test
bubble_sort_test: bubble_sort_test.c bubble_sort.o array.o
	$(CFLAGS) tests/bubble_sort_test.c bubble_sort.o array.o -o bin/bubble_sort_test
insertion_sort_test: insertion_sort_test.c insertion_sort.o array.o
	$(CFLAGS) tests/insertion_sort_test.c insertion_sort.o array.o -o bin/insertion_sort_test
selection_sort_test: selection_sort_test.c selection_sort.o array.o
	$(CFLAGS) tests/selection_sort_test.c selection_sort.o array.o -o bin/selection_sort_test
merge_sort_test: merge_sort_test.c merge_sort.o array.o
	$(CFLAGS) tests/merge_sort_test.c merge_sort.o array.o -o bin/merge_sort_test
quick_sort_test: quick_sort_test.c quick_sort.o array.o
	$(CFLAGS) tests/quick_sort_test.c quick_sort.o array.o -o bin/quick_sort_test
heap_sort_test: heap_sort_test.c heap_sort.o array.o p_queue.o bs_tree.o
	$(CFLAGS) tests/heap_sort_test.c heap_sort.o array.o p_queue.o bs_tree.o -o bin/heap_sort_test
binary_search_test: binary_search_test.c binary_search.o array.o
	$(CFLAGS) tests/binary_search_test.c binary_search.o array.o -o bin/binary_search_test

# Compiling objects
sl_list.o: sl_list.c sl_list.h
	$(CFLAGS) -c src/sl_list.c src/sl_list.h
dl_list.o: dl_list.c dl_list.h
	$(CFLAGS) -c src/dl_list.c src/dl_list.h
cl_list.o: cl_list.c cl_list.h
	$(CFLAGS) -c src/cl_list.c src/cl_list.h
stack.o: stack.c stack.h
	$(CFLAGS) -c src/stack.c src/stack.h
queue.o: queue.c queue.h
	$(CFLAGS) -c src/queue.c src/queue.h
array.o: array.c array.h
	$(CFLAGS) -c src/array.c src/array.h
c_buffer.o: c_buffer.c c_buffer.h
	$(CFLAGS) -c src/c_buffer.c src/c_buffer.h
h_table.o: h_table.c h_table.h
	$(CFLAGS) -c src/h_table.c src/h_table.h
trie.o: trie.c trie.h
	$(CFLAGS) -c src/trie.c src/trie.h
p_queue.o: p_queue.c p_queue.h
	$(CFLAGS) -c src/p_queue.c src/p_queue.h
bs_tree.o: bs_tree.c bs_tree.h
	$(CFLAGS) -c src/bs_tree.c src/bs_tree.h
bs_tree_map.o: bs_tree_map.c bs_tree_map.h
	$(CFLAGS) -c src/bs_tree_map.c src/bs_tree_map.h
rb_tree.o: rb_tree.c rb_tree.h
	$(CFLAGS) -c src/rb_tree.c src/rb_tree.h
rb_tree_map.o: rb_tree_map.c rb_tree_map.h
	$(CFLAGS) -c src/rb_tree_map.c src/rb_tree_map.h
graph.o: graph.c graph.h
	$(CFLAGS) -c src/graph.c src/graph.h
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
heap_sort.o: heap_sort.c heap_sort.h
	$(CFLAGS) -c src/heap_sort.c src/heap_sort.h
binary_search.o: binary_search.c binary_search.h
	$(CFLAGS) -c src/binary_search.c src/binary_search.h

# Run tests
.PHONY: test
test: sl_list_test dl_list_test cl_list_test stack_test queue_test array_test \
bubble_sort_test insertion_sort_test selection_sort_test merge_sort_test \
quick_sort_test c_buffer_test h_table_test trie_test bs_tree_test \
bs_tree_map_test rb_tree_map_test binary_search_test p_queue_test heap_sort_test graph_test
	./bin/sl_list_test
	./bin/dl_list_test
	./bin/cl_list_test
	./bin/stack_test
	./bin/queue_test
	./bin/array_test
	./bin/bubble_sort_test
	./bin/insertion_sort_test
	./bin/selection_sort_test
	./bin/merge_sort_test
	./bin/quick_sort_test
	./bin/heap_sort_test
	./bin/binary_search_test
	./bin/c_buffer_test
	./bin/h_table_test
	./bin/trie_test
	./bin/bs_tree_test
	./bin/bs_tree_map_test
	./bin/rb_tree_test
	./bin/rb_tree_map_test
	./bin/p_queue_test
# 	./bin/graph_test

clean:
	rm -f ./*.o src/*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
