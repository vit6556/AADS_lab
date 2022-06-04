#include "struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void fix_height(Tree *tree) {
    int lheight, rheight;

    if (tree->left != NULL)  lheight = tree->left->height;
    else lheight = 0;

    if (tree->right != NULL)  rheight = tree->right->height;
    else rheight = 0;

    if (lheight > rheight) tree->height = lheight + 1;
    else tree->height = rheight + 1;
}

Tree* rotate_right(Tree* tree)
{
	Tree* p = tree->left;
	tree->left = p->right;
	p->right = tree;
    p->parent = NULL;
    p->right->parent = p;
    if (p->right->left != NULL) {
        p->right->left->parent = p->right;
    }
	fix_height(tree);
	fix_height(p);
	return p;
}

Tree* rotate_left(Tree* tree)
{
	Tree* p = tree->right;
	tree->right = tree->left;
	p->left = tree;
    p->parent = NULL;
    p->left->parent = p;
    if (p->left->right != NULL) {
        p->left->right->parent = p->left;
    }
	fix_height(tree);
	fix_height(p);
	return p;
}

int balance_factor(Tree* p) {
    int lheight, rheight;

    if (p->left != NULL)  lheight = p->left->height;
    else lheight = 0;

    if (p->right != NULL)  rheight = p->right->height;
    else rheight = 0;

	return rheight - lheight;
}

Tree *balance(Tree* p) {
    fix_height(p);
	if (balance_factor(p) == 2) {
		if (balance_factor(p->right) < 0) {
			p->right = rotate_right(p->right);
        }
		p = rotate_left(p);
        return p;
	}

	if (balance_factor(p) == -2) {
		if (balance_factor(p->left) > 0 ) {
			p->left = rotate_left(p->left);
        }
		p = rotate_right(p);
        return p;
	}
    return p;
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
            fprintf(fptr,"\"(%d, '%s', %d)\" -> \"(%d, '%s', %d)\";\n", tree->key, tree->info, tree->height, left->key, left->info, left->height);
        } else {
            fprintf(fptr,"null_%d [shape=point];\n", tree->key);
            fprintf(fptr,"\"(%d, '%s', %d)\" -> null_%d;\n", tree->key, tree->info, tree->height, tree->key);
        }

        if (right != NULL) {
            fprintf(fptr,"\"(%d, '%s', %d)\" -> \"(%d, '%s', %d)\";\n", tree->key, tree->info, tree->height, right->key, right->info, right->height);
        } else {
            fprintf(fptr,"null_%d [shape=point];\n", tree->key);
            fprintf(fptr,"\"(%d, '%s', %d)\" -> null_%d;\n", tree->key, tree->info, tree->height, tree->key);
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

Tree* add(Tree* tree, int key, char *info) {
	if (!tree) {
        Tree *new_node = malloc(sizeof(Tree));
        new_node->key = key;
        new_node->info = info;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->height = 1;
        return new_node;
    }
	if (key < tree->key)
		tree->left = add(tree->left, key, info);
	else
		tree->right = add(tree->right, key, info);

	return balance(tree);
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
    Tree *parent = NULL;
    if (replace_with == NULL) {
        parent = to_delete->parent;
        if (parent->left != NULL && parent->left->key == to_delete->key) {
            parent->left = NULL;
        }

        if (parent->right != NULL && parent->right->key == to_delete->key) {
            parent->right = NULL;
        }
        free(to_delete);
    } else {
        parent = replace_with->parent;
        parent->right = replace_with->left;

        to_delete->info = replace_with->info;
        to_delete->key = replace_with->key;
        free(replace_with);
    }

    parent = balance(parent);

    return 0;
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

