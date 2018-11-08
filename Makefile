VPATH = src tests
CFLAGS = gcc -Wall -Wextra

all: sllist_test dllist_test

# Singly linked list
sllist_test: sllist_test.c sllist.o
	$(CFLAGS) -Isrc tests/sllist_test.c sllist.o -o sllist_test

# Doubly linked list
dllist_test: dllist_test.c dllist.o
	$(CFLAGS) -Isrc tests/dllist_test.c dllist.o -o dllist_test

sllist.o: sllist.c sllist.h
	$(CFLAGS) -c src/sllist.c src/sllist.h

dllist.o: dllist.c dllist.h
	$(CFLAGS) -c src/dllist.c src/dllist.h

.PHONY: test
test: sllist_test
	./sllist_test

clean:
	rm ./*.o
	rm src/*.h.gch
	rm ./sllist_test ./dllist_test
