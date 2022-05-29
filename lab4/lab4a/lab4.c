#include "struct.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Tree *tree = malloc(sizeof(Tree));
    tree->info = NULL;
    tree->left = NULL;
    tree->right = NULL;
    tree->parent = NULL;

    add(tree, 12, "cat");
    add(tree, 5, "dog");
    add(tree, 16, "mouse");
    add(tree, 14, "fish");
    add(tree, 2, "sheep");
    add(tree, 1, "cow");
    add(tree, 13, "fly");
    add(tree, 20, "turtle");
    add(tree, 9, "rat");
    add(tree, 7, "butterfly");
    add(tree, 6, "bull");
    add(tree, 8, "lion");

    printf("Inorder traversal:\n");
    traversal(tree);

    int key = 7;
    printf("\nFind by key %d:\n", key);
    Tree *t = find(tree, key);
    if (t != NULL) printf("%s\n", t->info);
    else printf("No such key\n");

    key = 21;
    printf("\nFind by key %d:\n", key);
    t = find(tree, key);
    if (t != NULL) printf("%s\n", t->info);
    else printf("No such key\n");

    printf("\nFind max:\n", key);
    t = find_max(tree);
    printf("(%d, %s)\n", t->key, t->info);

    print_tree(tree, "graph.png", NULL);
    key = 12;
    del(tree, key);
    print_tree(tree, "graph_after_del.png", NULL);

    free_tree(tree);
}