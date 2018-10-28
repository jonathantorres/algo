VPATH = src tests
CFLAGS = gcc -Wall -Wextra

all: calc_test

calc_test: calc_test.c calc.o
	$(CFLAGS) -Isrc tests/calc_test.c calc.o -o calc_test

calc.o: calc.c calc.h
	$(CFLAGS) -c src/calc.c src/calc.h

print_numbers.o:
	$(CFLAGS) -c src/print_numbers.c src/print_numbers.h

.PHONY: test
test: calc_test sllist_test
	./sllist_test
	./calc_test

clean:
	rm ./*.o
	rm src/*.h.gch
	rm ./calc_test ./sllist_test
