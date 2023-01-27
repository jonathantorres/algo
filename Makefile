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

NET_PROGS := daytime_server                 \
             daytime_client                 \
             stream_server                  \
             stream_client                  \
             http_server                    \
             http_server_nonblock           \
             http_server_image              \
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

ARCH_PROGS := b2n n2b h2n h2b binadd           \
              isodd div16 bitcmp endiancheck

.PHONY: all
all: test

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
	# rm -fr ./bin
	# mkdir ./bin && touch ./bin/.gitkeep

