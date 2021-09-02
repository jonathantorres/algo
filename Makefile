CFLAGS = gcc -g -std=gnu11 -Wall -Wextra

all: main

main: main.c inet_pton_loose.o
	$(CFLAGS) main.c inet_pton_loose.o -o main
inet_pton_loose.o: inet_pton_loose.c inet_pton_loose.h
	$(CFLAGS) -c inet_pton_loose.c inet_pton_loose.h
