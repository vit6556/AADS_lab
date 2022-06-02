all: run

comp: lab5.c struct.h graph.c queue.c
	gcc lab5.c struct.h graph.c queue.c -o lab5.o -std=c99

run: comp
	./lab5.o

val: comp
	valgrind --leak-check=full --track-origins=yes ./lab5.o