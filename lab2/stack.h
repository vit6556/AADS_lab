#ifndef STACK_H
#define STACK_H

typedef struct move Move;
typedef struct stack Stack;
Stack* create_stack();
int check_empty(Stack *s);
void resize(Stack* s);
void push(Stack *s, Move* value);
Move pop(Stack *s);
void delete_stack(Stack *s);
#endif //STACK_H
