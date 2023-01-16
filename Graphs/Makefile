all: client

client: main.o graph.o
	gcc main.o graph.o -lm -o client

graph.o: graph.c header.h
	gcc -std=c99 -Wall -Werror -c graph.c

main.o: main.c header.h
	gcc -std=c99 -Wall -Werror -c main.c
