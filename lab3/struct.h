#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node {
    char *info;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;

typedef struct KeySpace1 {
    int key;
    char *info;
    struct KeySpace1 *next;
} KeySpace1;

typedef struct KeySpace2 {
    int busy;
    int key;
    char *info;
} KeySpace2;

typedef struct Table {
    KeySpace1 *ks1;
    KeySpace2 *ks2;
    int msize2;
} Table;

#endif
