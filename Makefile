VPATH = algos arch ds graphs net sorting trees tests
CFLAGS := gcc -g -std=c11 -Wall -Wextra -Wpedantic -Ialgos -Ids -Igraphs -Isorting -Itrees
CPPFLAGS := g++ -std=c++11 -Wall -Wextra -Wpedantic

ALGO_PROGS := binary_search
ALGO_OBJS := $(addsuffix .o,$(ALGO_PROGS))
ALGO_TESTS := $(addsuffix _test,$(ALGO_PROGS))

ARCH_PROGS := b2n n2b h2n h2b binadd           \
              isodd div16 bitcmp endiancheck
ARCH_OBJS := $(addsuffix .o,$(ALGO_PROGS))

DS_PROGS := array c_buffer cl_list dl_list h_table    \
			p_queue queue sl_list stack str
DS_OBJS := $(addsuffix .o,$(DS_PROGS))
DS_TESTS := $(addsuffix _test,$(DS_PROGS))

GRAPH_PROGS := graph
GRAPH_OBJS := $(addsuffix .o,$(GRAPH_PROGS))
GRAPH_TESTS := $(addsuffix _test,$(GRAPH_PROGS))

SORT_PROGS := bubble_sort heap_sort insertion_sort merge_sort  \
			  quick_sort selection_sort
SORT_OBJS := $(addsuffix .o,$(SORT_PROGS))
SORT_TESTS := $(addsuffix _test,$(SORT_PROGS))

TREES_PROGS := bs_tree bs_tree_map rb_tree rb_tree_map trie
TREES_OBJS := $(addsuffix .o,$(TREES_PROGS))
TREES_TESTS := $(addsuffix _test,$(TREES_PROGS))

NET_PROGS := daytime_server                 \
             daytime_client                 \
             stream_server                  \
             stream_client                  \
             multi_http_server              \
             access                         \
             atexit                         \
             broken_pipe                    \
             byte_order                     \
             conn_recv_buff_mss             \
             date                           \
             date_cli                       \
             date_cli_read_peek             \
             date_cli_recv_buff             \
             date_cli_getsockname           \
             date_serv                      \
             date_serv_print_cli            \
             dup2                           \
             echo_cli                       \
             echo_cli_chargen               \
             echo_cli_connect_timeo         \
             echo_cli_linger                \
             echo_cli_poll                  \
             echo_cli_select                \
             echo_cli_sigpipe               \
             echo_cli_udp                   \
             echo_cli_udp_connect           \
             echo_cli_udp_dns               \
             echo_serv                      \
             echo_serv_stdio                \
             echo_serv_tcp_udp              \
             echo_serv_udp                  \
             f1                             \
             file_lock                      \
             file_traversal                 \
             file_type                      \
             gai                            \
             get_host_names                 \
             get_host_names_addr            \
             getnameinfo_timeo              \
             http_server                    \
             http_server_image              \
             http_server_multi              \
             http_server_nonblock           \
             iocopy                         \
             ipv4_bind                      \
             ipv6_bind                      \
             inet_pton_loose                \
             local_ip_addrs                 \
             mmap                           \
             msg_queue_srv                  \
             msg_queue_cli                  \
             pass                           \
             pipe                           \
             prompt                         \
             prompt_signal                  \
             read_write                     \
             send_recv_buff_sizes           \
             setbuf                         \
             shared_mem_srv                 \
             shared_mem_cli                 \
             sleep                          \
             system                         \
             umask                          \
             uname                          \
             zombie

.PHONY: all
all: algo-tests ds-tests graphs-tests sorting-tests trees-tests

# compiling algo objects
$(ALGO_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling ds objects
$(DS_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling graphs objects
$(GRAPH_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling sorting objects
$(SORT_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling tree objects
$(TREES_OBJS):%.o: %.c %.h
	$(CFLAGS) -c $^

# compiling algo tests
$(ALGO_TESTS):%: %.c $(ALGO_OBJS) array.o
	$(CFLAGS) $^ -o bin/$@

# compiling ds tests
$(DS_TESTS):%: %.c $(DS_OBJS) bs_tree.o
	$(CFLAGS) $^ -o bin/$@

# compiling graph tests
$(GRAPH_TESTS):%: %.c $(GRAPH_OBJS) array.o stack.o queue.o dl_list.o
	$(CFLAGS) $^ -o bin/$@

# compiling sorting tests
$(SORT_TESTS):%: %.c $(SORT_OBJS) array.o p_queue.o bs_tree.o
	$(CFLAGS) $^ -o bin/$@

# compiling tree tests
$(TREES_TESTS):%: %.c $(TREES_OBJS) array.o
	$(CFLAGS) $^ -o bin/$@

# hangman program
hangman: other/hangman/hangman.c array.o
	$(CFLAGS) $^ -o bin/$@
	cp other/hangman/words.txt bin/words.txt

# network programs
$(NET_PROGS):%: net/%.c
	$(CFLAGS) $^ -o bin/$@

# arch programs
$(ARCH_PROGS):%: arch/%.c
	$(CFLAGS) $^ -o bin/$@

# Run tests
algo-tests: $(ALGO_TESTS)
	for t in $^; do ./bin/$$t; done

ds-tests: $(DS_TESTS)
	for t in $^; do ./bin/$$t; done

graphs-tests: $(GRAPH_TESTS)
	for t in $^; do ./bin/$$t; done

sorting-tests: $(SORT_TESTS)
	for t in $^; do ./bin/$$t; done

trees-tests: $(TREES_TESTS)
	for t in $^; do ./bin/$$t; done

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch ./*/*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep

