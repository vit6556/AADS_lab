#include "struct.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Tree *tree;
    FILE *fp = fopen("dop2.o", "rb");
    char c;
    int status = fscanf(fp, "%c", &c); 
    do {
        if (c >= 48 && c <= 57) tree = add(tree, c, 1);
        status = fscanf(fp, "%c", &c); 
    } while (status == 1);
    fclose(fp);

    fp = fopen("dop2.txt", "w");
    traversal(tree, fp);
    fclose(fp);
}