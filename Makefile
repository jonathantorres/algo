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

clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
