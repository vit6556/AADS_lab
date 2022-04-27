#include <stdio.h>
#include <stdlib.h>

typedef struct move {
    int x_from, y_from, x_to, y_to;
} Move;

void allocate_board(int n, int *board[]) {
    for (int i = 0; i < n; ++i) {
        board[i] = calloc(n, sizeof(int));
    }
}

int get_zero(int n, int *board[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 0) return n * i + j;
        }
    }
}

int generate_board(int n, int *board[]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = 0;
        }
    }

    // int x, y;
    // for (int i = 1; i < n * n; ++i) {
    //     do {
    //         x = rand() % n;
    //         y = rand() % n;
    //     } while(!(board[x][y] == 0));
    //     board[x][y] = i;
    // }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = i * n + j + 1;
        }
    }
    board[n - 1][n - 1] = 0;
    
    return get_zero(n, board);
}

int check_board(int n, int *board[]) {
    int num;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            num = (i * n + j + 1) % (n * n);
            if (board[i][j] != num) return 0;
        }
    }
    return 1;
}

void turn(int *board[], Move m) {
    int temp = board[m.x_to][m.y_to];
    board[m.x_to][m.y_to] = board[m.x_from][m.y_from];
    board[m.x_from][m.y_from] = temp;
}

void print_board(int n, int *board[]) {
    printf("\nBoard:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] < 10) printf(" ");
            if (board[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    } 
}

void free_board(int n, int *board[]) {
    for (int i = 0; i < n; ++i) {
        free(board[i]);
    }
}