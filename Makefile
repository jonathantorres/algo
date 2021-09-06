CFLAGS = gcc -g -std=gnu11 -Wall -Wextra

all: inet_pton_loose

inet_pton_loose: inet_pton_loose.c
	$(CFLAGS) inet_pton_loose.c -o ./bin/inet_pton_loose

daytime_client_getsockname: daytime_client_getsockname.c
	$(CFLAGS) daytime_client_getsockname.c -o ./bin/daytime_client_getsockname

clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
