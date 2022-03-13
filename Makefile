CFLAGS = gcc -g -std=gnu11 -Wall -Wextra
PROGS = access                        \
        broken_pipe                   \
        byte_order                    \
        date_cli                      \
        date_cli_read_peek            \
        date_cli_recv_buff            \
        date_cli_getsockname          \
        date_serv                     \
        date_serv_print_cli           \
        echo_cli                      \
        echo_cli_connect_timeo        \
        echo_cli_linger               \
        echo_cli_poll                 \
        echo_cli_select               \
        echo_cli_sigpipe              \
        echo_cli_udp                  \
        echo_cli_udp_dns              \
        echo_serv                     \
        echo_serv_stdio               \
        echo_serv_udp                 \
        file_lock                     \
        gai                           \
        get_host_names                \
        get_host_names_addr           \
        getnameinfo_timeo             \
        http_server                   \
        http_server_image             \
        http_server_multi             \
        http_server_nonblock          \
        ipv4_bind                     \
        ipv6_bind                     \
        inet_pton_loose               \
        local_ip_addrs                \
        msg_queue_srv                 \
        msg_queue_cli                 \
        pipe                          \
        send_recv_buff_sizes          \
        sleep                         \
        shared_mem_srv                \
        shared_mem_cli                \
        system

.PHONY: all
all: $(PROGS)

$(PROGS):%: %.c
	$(CFLAGS) $< -o ./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
