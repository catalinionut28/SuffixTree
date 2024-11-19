CFLAGS=-Wall -Werror
.PHONY: clean build

build: build
build: main.c
		gcc $(CFLAGS) main.c SuffixTree.c Cerinte.c -o tema2
clean:
		rm -f tema2