CFLAGS = gcc -g -std=gnu11 -Wall -Wextra
PROGS = access                        \
        atexit                        \
        broken_pipe                   \
        byte_order                    \
        conn_recv_buff_mss            \
        date                          \
        date_cli                      \
        date_cli_read_peek            \
        date_cli_recv_buff            \
        date_cli_getsockname          \
        date_serv                     \
        date_serv_print_cli           \
        dup2                          \
        echo_cli                      \
        echo_cli_chargen              \
        echo_cli_connect_timeo        \
        echo_cli_linger               \
        echo_cli_poll                 \
        echo_cli_select               \
        echo_cli_sigpipe              \
        echo_cli_udp                  \
        echo_cli_udp_connect          \
        echo_cli_udp_dns              \
        echo_serv                     \
        echo_serv_stdio               \
        echo_serv_tcp_udp             \
        echo_serv_udp                 \
        f1                            \
        file_lock                     \
        file_traversal                \
        file_type                     \
        gai                           \
        get_host_names                \
        get_host_names_addr           \
        getnameinfo_timeo             \
        http_server                   \
        http_server_image             \
        http_server_multi             \
        http_server_nonblock          \
        iocopy                        \
        ipv4_bind                     \
        ipv6_bind                     \
        inet_pton_loose               \
        local_ip_addrs                \
        mmap                          \
        msg_queue_srv                 \
        msg_queue_cli                 \
        pass                          \
        pipe                          \
        prompt                        \
        prompt_signal                 \
        read_write                    \
        send_recv_buff_sizes          \
        setbuf                        \
        shared_mem_srv                \
        shared_mem_cli                \
        sleep                         \
        system                        \
        umask                         \
        uname                         \
        zombie

.PHONY: all
all: $(PROGS)

$(PROGS):%: %.c
	$(CFLAGS) $< -o ./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
