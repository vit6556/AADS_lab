all: run

comp: lab3.c struct.h table.c
	gcc lab3.c struct.h table.c -o lab3.o -std=c99

run: comp
	./lab3.o

val: comp
	valgrind --leak-check=full ./lab3.o