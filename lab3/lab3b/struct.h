#include <stdlib.h>
#include <stdio.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef struct finfo {
    FILE *f;
    int first_free_pos;
} finfo;

typedef struct Data {
    int pos, size;
} Data;

typedef struct Node {
    char *info;
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
} List;;

typedef struct KeySpace1 {
    int key;
    Data info; //char*
    Data next;
} KeySpace1;

typedef struct KeySpace2 {
    int busy;
    int key;
    Data info; //char*
} KeySpace2;

typedef struct Table {
    Data ks1;
    Data ks2;
    int msize2;
} Table;

#endif
