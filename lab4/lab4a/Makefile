all: run

comp: lab4.c struct.h tree.c
	gcc lab4.c struct.h tree.c -o lab4.o -std=c99

run: comp
	./lab4.o

val: comp
	valgrind --leak-check=full --track-origins=yes ./lab4.o