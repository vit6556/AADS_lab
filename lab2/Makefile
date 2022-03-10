all: comp_list

comp_list: lab2.c stack_list.c board.c
	gcc lab2.c stack_list.c board.c -o lab2.o -std=c99

comp_array: lab2.c stack_array.c board.c
	gcc lab2.c stack_array.c board.c -o lab2.o -std=c99

run_list: comp_list
	./lab2.o

run_array: comp_array
	./lab2.o

val: lab2.0
	valgrind ./lab2.o