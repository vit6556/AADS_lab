#include <stdio.h>

#ifndef TREE_H
#define TREE_H

int add(Tree *tree, int key, char *info);
void print_tree(Tree *tree, char *filename, FILE *fptr);
int del(Tree *tree, int key);
Tree *find(Tree *tree, int key);
Tree *find_max(Tree *tree);
void traversal(Tree *tree);
void free_tree(Tree *tree);

#endif