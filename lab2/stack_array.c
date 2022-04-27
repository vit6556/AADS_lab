#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 16

typedef struct move {
    int x_from, y_from, x_to, y_to;
} Move;

typedef struct stack {
    Move *data;
    int size;
    int top;
} Stack;

Stack* create_stack() {
    Stack* out = NULL;
    out = malloc(sizeof(Stack));
    out->size = INIT_SIZE;
    out->data = malloc(out->size * sizeof(Move));
    out->top = 0;
    return out;
}


void resize(Stack* s) {
    s->size *= 2;
    s->data = realloc(s->data, s->size * sizeof(Move));
}

int check_empty(Stack *s) {
    return s->top == 0;
}

void push(Stack *s, Move* value) {
    if (s->top >= s->size) {
        resize(s);
    }
    s->data[s->top] = *value;
    free(value);
    s->top++;
}

Move pop(Stack *s) {
    s->top--;
    return s->data[s->top];
}

void delete_stack(Stack *s) {
    free(s->data);
    free(s);
}