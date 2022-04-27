#ifndef BOARD_H
#define BOARD_H

typedef struct move Move;
void allocate_board(int n, int *board[]);
int generate_board(int n, int*board[]);
void print_board(int n, int *board[]);
int check_board(int n, int *board[]);
int get_zero(int n, int *board[]);
void turn(int *board[], Move m);
void free_board(int n, int *matrix[]);
#endif //BOARD_H
