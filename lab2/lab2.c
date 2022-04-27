#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "stack.h"

typedef struct move {
    int x_from, y_from, x_to, y_to;
} Move;

typedef struct node {
    Move *data;
    struct node *next;
} Node;

typedef struct stack {
    Node *head;
} Stack;

Move create_move(int x_to, int y_to, int x_from, int y_from) {
    Move m;
    m.x_from = x_from;
    m.y_from = y_from;
    m.x_to = x_to;
    m.y_to = y_to;
    return m;
}

int main() {
    srand(time(NULL));

    int n = 3, cur_pos, x, y;
    int* board[n];
    char c;

    Stack *history = create_stack();

    allocate_board(n, board);
    cur_pos = generate_board(n, board);
    x = cur_pos / n;
    y = cur_pos - x * n;
    do {
        print_board(n, board);
        printf("Your turn(u,d,l,r,b): ");
        scanf(" %c", &c);
        switch (c) {
            case 'd': 
                if (x != n - 1) {
                    Move m = create_move(x + 1, y, x, y);
                    turn(board, m);
                    push(history, m);
                    x += 1;
                    break;
                }
            case 'u':
                if (x != 0) {
                    Move m = create_move(x - 1, y, x, y);
                    turn(board, m);
                    push(history, m);
                    x -= 1;
                    break;
                }
            case 'r':
                if (y != n - 1) {
                    Move m = create_move(x, y + 1, x, y);
                    turn(board, m);
                    push(history, m);
                    y += 1;
                    break;
                }
            case 'l':
                if (y != 0) {
                    Move m = create_move(x, y - 1, x, y);
                    turn(board, m);
                    push(history, m);
                    Move* m1 = pop(history);
                    printf("%d %d %d %d", m1->x_from, m1->y_from, m1->x_to, m1->y_to);
                    y -= 1;
                    break;
                }
            case 'b': ;
                //if (!check_empty(history)) {
                Move* m1 = pop(history);
                printf("%d %d %d %d", m1->x_from, m1->y_from, m1->x_to, m1->y_to);
                //turn(board, m);
                // cur_pos = get_zero(n, board);
                // x = cur_pos / n;
                // y = cur_pos - x * n;
                break;
                //}
            default:
                printf("\nWrong turn");
                break;
        }
    } while (!check_board(n, board));

    print_board(n, board);
    printf("You did it!\n");
    free_board(n, board);
    delete_stack(&history); 
}