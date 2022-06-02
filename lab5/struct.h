typedef struct Edge {
    char *from;
    char *to;
    int weight;
} Edge;

typedef struct Vertex {
    char *name;
} Vertex;

typedef struct Graph {
    int vertices_amount;
    int edges_amount;
    Vertex *vertices;
    Edge *edges;
} Graph;

typedef struct Node {
    char *info;
    struct Node *next;
} Node;

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

