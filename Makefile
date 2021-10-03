CFLAGS = gcc -g -std=gnu11 -Wall -Wextra

all: inet_pton_loose

inet_pton_loose: inet_pton_loose.c
	$(CFLAGS) inet_pton_loose.c -o ./bin/inet_pton_loose

daytime_client_getsockname: daytime_client_getsockname.c
	$(CFLAGS) daytime_client_getsockname.c -o ./bin/daytime_client_getsockname

broken_pipe: broken_pipe.c
	$(CFLAGS) broken_pipe.c -o ./bin/broken_pipe

date_serv: date_serv.c
	$(CFLAGS) date_serv.c -o ./bin/date_serv

date_cli: date_cli.c
	$(CFLAGS) date_cli.c -o ./bin/date_cli

echo_serv: echo_serv.c
	$(CFLAGS) echo_serv.c -o ./bin/echo_serv

echo_serv_udp: echo_serv_udp.c
	$(CFLAGS) echo_serv_udp.c -o ./bin/echo_serv_udp

echo_cli: echo_cli.c
	$(CFLAGS) echo_cli.c -o ./bin/echo_cli

echo_cli_udp: echo_cli_udp.c
	$(CFLAGS) echo_cli_udp.c -o ./bin/echo_cli_udp

echo_cli_select: echo_cli_select.c
	$(CFLAGS) echo_cli_select.c -o ./bin/echo_cli_select

echo_cli_poll: echo_cli_poll.c
	$(CFLAGS) echo_cli_poll.c -o ./bin/echo_cli_poll

echo_cli_linger: echo_cli_linger.c
	$(CFLAGS) echo_cli_linger.c -o ./bin/echo_cli_linger

send_recv_buff_sizes: send_recv_buff_sizes.c
	$(CFLAGS) send_recv_buff_sizes.c -o ./bin/send_recv_buff_sizes

date_cli_recv_buff: date_cli_recv_buff.c
	$(CFLAGS) date_cli_recv_buff.c -o ./bin/date_cli_recv_buff

get_host_names: get_host_names.c
	$(CFLAGS) get_host_names.c -o ./bin/get_host_names

get_host_names_addr: get_host_names_addr.c
	$(CFLAGS) get_host_names_addr.c -o ./bin/get_host_names_addr

local_ip_addrs: local_ip_addrs.c
	$(CFLAGS) local_ip_addrs.c -o ./bin/local_ip_addrs

echo_cli_udp_dns: echo_cli_udp_dns.c
	$(CFLAGS) echo_cli_udp_dns.c -o ./bin/echo_cli_udp_dns

clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
