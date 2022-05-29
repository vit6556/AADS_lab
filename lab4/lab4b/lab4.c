#include "struct.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Tree *tree;
    tree = add(tree, 20, "turtle");
    tree = add(tree, 16, "mouse");
    tree = add(tree, 14, "fish");
    tree = add(tree, 13, "fly");
    tree = add(tree, 12, "cat");
    tree = add(tree, 9, "rat");
    tree = add(tree, 8, "lion");
    tree = add(tree, 5, "dog");
    tree = add(tree, 2, "sheep");

    print_tree(tree, "graph.png", NULL);

    free_tree(tree);
}