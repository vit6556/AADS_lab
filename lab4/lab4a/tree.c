#include "struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int add(Tree *tree, int key, char *info) {
    if (tree->info == NULL) {
        tree->key = key;
        tree->info = info;
        tree->left = NULL;
        tree->right = NULL;
        return 0;
    }

    Tree *new_node = malloc(sizeof(Tree));
    new_node->key = key;
    new_node->info = info;
    new_node->left = NULL;
    new_node->right = NULL;

    Tree *cur_vertex = tree;
    Tree *prev_vertex = NULL;
    int key_unique = 1, left = 1;
    while (cur_vertex != NULL) {
        if (key > cur_vertex->key) {
            prev_vertex = cur_vertex;
            cur_vertex = cur_vertex->right;
            left = 0;
        } else if (key < cur_vertex->key) {
            prev_vertex = cur_vertex;
            cur_vertex = cur_vertex->left;
            left = 1;
        } else {
            return 1;
        }
    }

    new_node->parent = prev_vertex;
    if (left) {
        prev_vertex->left = new_node;
    } else {
        prev_vertex->right = new_node;
    }

    return 0;
}

Tree *find(Tree *tree, int key) {
    Tree *cur_vertex = tree;
    while (cur_vertex != NULL) {
        if (key > cur_vertex->key) {
            cur_vertex = cur_vertex->right;
        } else if (key < cur_vertex->key) {
            cur_vertex = cur_vertex->left;
        } else {
            return cur_vertex;
        }
    }

    return NULL;
}

Tree *find_max(Tree *tree) {
    if (tree == NULL) return NULL;
    Tree *cur_vertex = tree;
    Tree *prev_vertex = tree;

    while (cur_vertex != NULL) {
        prev_vertex = cur_vertex;
        cur_vertex = cur_vertex->right;
    }

    return prev_vertex;
}

int del(Tree *tree, int key) {
    Tree *to_delete = find(tree, key);
    if (to_delete == NULL) return 1;
    
    Tree *replace_with = find_max(to_delete->left);
    if (replace_with == NULL) {
        Tree *parent = to_delete->parent;
        if (parent->left != NULL && parent->left->key == to_delete->key) {
            parent->left = NULL;
        }

        if (parent->right != NULL && parent->right->key == to_delete->key) {
            parent->right = NULL;
        }
        free(to_delete);
        return 0;
    } else {
        Tree *parent = replace_with->parent;
        parent->right = replace_with->left;

        to_delete->info = replace_with->info;
        to_delete->key = replace_with->key;
        free(replace_with);
    }
}


void traversal(Tree *tree) {
    if (tree == NULL) return;
    printf("(%d, '%s')\n", tree->key, tree->info);
    traversal(tree->left);
    traversal(tree->right);
}

void free_tree(Tree *tree) {
    if (tree == NULL) return;
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
}

void print_tree(Tree *tree, char *filename, FILE *fptr) {
    if (tree == NULL) return;

    int root = 0;
    if (fptr == NULL) {
        fptr = fopen("graph.dot","w");
        fprintf(fptr,"digraph BinaryTree {\n");
        root = 1;
    }

    Tree *left = tree->left;
    Tree *right = tree->right;
    if (left != NULL || right != NULL) {
        if (left != NULL) {
            fprintf(fptr,"\"(%d, '%s')\" -> \"(%d, '%s')\";\n", tree->key, tree->info, left->key, left->info);
        } else {
            fprintf(fptr,"null_%d [shape=point];\n", tree->key);
            fprintf(fptr,"\"(%d, '%s')\" -> null_%d;\n", tree->key, tree->info, tree->key);
        }

        if (right != NULL) {
            fprintf(fptr,"\"(%d, '%s')\" -> \"(%d, '%s')\";\n", tree->key, tree->info, right->key, right->info);
        } else {
            fprintf(fptr,"null_%d [shape=point];\n", tree->key);
            fprintf(fptr,"\"(%d, '%s')\" -> null_%d;\n", tree->key, tree->info, tree->key);
        }
    }
    print_tree(left, filename, fptr);
    print_tree(right, filename, fptr);

    if (root) {
        fprintf(fptr,"}");
        fclose(fptr);
        char command[100] = "dot -Tpng graph.dot > ";
        strcat(command, filename);
        system(command);
    }
}

