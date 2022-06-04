all: run

comp: lab4.c struct.h tree.c
	gcc lab4.c struct.h tree.c -o lab4.o -std=c99

comp_dop2: dop2.c struct.h tree.c
	gcc dop2.c struct.h tree.c -o dop2.o -std=c99

run_dop2: comp_dop2
	./dop2.o

run: comp
	./lab4.o

val: comp
	valgrind --leak-check=full --track-origins=yes ./lab4.o