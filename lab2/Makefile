all: comp

comp: lab1.c
	gcc lab1.c -o lab1.o -std=c99

run: all
	./lab1.o

val: all
	valgrind ./lab1.o