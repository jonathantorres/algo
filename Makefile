VPATH = src tests
CFLAGS := gcc -g -std=gnu11 -Wall -Wextra -Isrc
CPPFLAGS := g++ -std=c++11 -Wall -Wextra -Isrc

ALGO_PROGS := sl_list dl_list cl_list stack queue      \
              array c_buffer h_table trie p_queue      \
              bs_tree bs_tree_map rb_tree rb_tree_map  \
              graph bubble_sort insertion_sort         \
              selection_sort merge_sort quick_sort     \
              heap_sort binary_search str

ALGO_OBJS := $(addsuffix .o,$(ALGO_PROGS))
ALGO_TESTS := $(addsuffix _test,$(ALGO_PROGS))

NET_PROGS := daytime_server daytime_client stream_server      \
             stream_client http_server http_server_nonblock   \
             http_server_image multi_http_server

ARCH_PROGS := b2n n2b h2n h2b binadd           \
              isodd div16 bitcmp endiancheck

.PHONY: all
all: test hangman stream_server stream_client http_server

# compiling algo objects
$(ALGO_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling algo tests
$(ALGO_TESTS):%: %.c $(ALGO_OBJS)
	$(CFLAGS) $^ -o bin/$@

# hangman program
hangman: hangman/hangman.c array.o
	$(CFLAGS) $^ -o bin/$@
	cp src/hangman/words.txt bin/words.txt

# network programs
$(NET_PROGS):%: net/%.c
	$(CFLAGS) $^ -o bin/$@

# arch programs
$(ARCH_PROGS):%: arch/%.c
	$(CFLAGS) $^ -o bin/$@

# Run tests
.PHONY: test
test: $(ALGO_TESTS)
	for t in $^; do ./bin/$$t; done

.PHONY: clean
clean:
	rm -f ./*.o src/*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
