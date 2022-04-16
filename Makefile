CFLAGS = gcc -g -std=gnu11 -Wall -Wextra
PROGS = read_write                  \
        prompt                      \
        prompt_signal

.PHONY: all
all: $(PROGS)

$(PROGS):%: %.c
	$(CFLAGS) $< -o ./bin/$@

.PHONY: clean
clean:
	rm -f ./*.o ./*.h.gch
	rm -fr ./bin
	mkdir ./bin && touch ./bin/.gitkeep
