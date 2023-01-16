all: client

client: main.o functions.o
	gcc main.o functions.o -lm -o client

functions.o: functions.c header.h
	gcc -std=c99 -Wall -Werror -c functions.c

main.o: main.c header.h
	gcc -std=c99 -Wall -Werror -c main.c
