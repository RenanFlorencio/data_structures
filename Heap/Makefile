all: client

client: main.o heap.o
	gcc main.o heap.o -lm -o client

heap.o: heap.c header.h
	gcc -std=c99 -Wall -Werror -c heap.c

main.o: main.c header.h
	gcc -std=c99 -Wall -Werror -c main.c
