all: client

client: main.o stack.o queue.o
	gcc main.o stack.o queue.o -lm -o client

main.o: main.c stackHeader.h queueHeader.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c main.c

stack.o: stack.c stackHeader.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c stack.c

queue.o: queue.c queueHeader.h
	gcc -std=c99 -Wall -Werror -Werror=vla -g -c queue.c
