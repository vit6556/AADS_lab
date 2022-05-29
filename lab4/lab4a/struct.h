typedef struct Tree {
    int key;
    struct Tree *left;
    struct Tree *right;
    struct Tree *parent;
    char *info;
} Tree;
