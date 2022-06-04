#include <stdio.h>

#ifndef TREE_H
#define TREE_H

Tree *add(Tree *tree, int key, int info);
void print_tree(Tree *tree, char *filename, FILE *fptr);
Tree *balance(Tree* p);
int del(Tree *tree, int key);
Tree *find(Tree *tree, int key);
Tree *find_max(Tree *tree);
void traversal(Tree *tree, FILE *fp);
void free_tree(Tree *tree);

#endif