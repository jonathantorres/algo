CFLAGS = gcc -g -std=gnu11 -Wall -Wextra

all: inet_pton_loose

inet_pton_loose: inet_pton_loose.c
	$(CFLAGS) inet_pton_loose.c -o ./bin/inet_pton_loose

clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
