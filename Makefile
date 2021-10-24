CFLAGS = gcc -g -std=gnu11 -Wall -Wextra
PROGS = inet_pton_loose               \
        daytime_client_getsockname    \
        broken_pipe                   \
        date_serv                     \
        date_cli                      \
        date_cli_read_peek            \
        echo_serv                     \
        echo_serv_udp                 \
        echo_serv_stdio               \
        echo_cli                      \
        echo_cli_udp                  \
        echo_cli_select               \
        echo_cli_poll                 \
        echo_cli_linger               \
        echo_cli_connect_timeo        \
        send_recv_buff_sizes          \
        date_cli_recv_buff            \
        get_host_names                \
        get_host_names_addr           \
        local_ip_addrs                \
        echo_cli_udp_dns              \
        ipv4_bind                     \
        ipv6_bind                     \
        gai                           \
        getnameinfo_timeo

.PHONY: all
all: $(PROGS)

$(PROGS):%: %.c
	$(CFLAGS) $< -o ./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
