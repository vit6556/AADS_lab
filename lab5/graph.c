#include "struct.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int add_vertex(Graph *graph, char *vertex) {
    for (int i = 0; i < graph->vertices_amount; ++i) {
        if (strcmp(vertex, graph->vertices[i].name) == 0) {
            return 1;
        }
    }

    Vertex v;
    v.name = vertex;

    graph->vertices_amount += 1;
    graph->vertices = realloc(graph->vertices, sizeof(Vertex) * (graph->vertices_amount));
    graph->vertices[graph->vertices_amount - 1] = v;

    return 0;
}

int add_edge(Graph *graph, char* from, char* to, int weight) {
    int found_from = 0, found_to = 0;
    for (int i = 0; i < graph->vertices_amount; ++i) {
        if (strcmp(from, graph->vertices[i].name) == 0) {
            found_from = 1;
        }

        if (strcmp(to, graph->vertices[i].name) == 0) {
            found_to = 1;
        }
    }

    if (!found_from || !found_to) {
        return 1;
    }

    for (int i = 0; i < graph->edges_amount; ++i) {
        if ((strcmp(from, graph->edges[i].from) == 0 && strcmp(to, graph->edges[i].to) == 0) || (strcmp(from, graph->edges[i].to) == 0 && strcmp(to, graph->edges[i].from) == 0)) {
            return 2;
        }
    }

    Edge e;
    e.from = from;
    e.to = to;
    e.weight = weight;

    graph->edges_amount += 1;
    graph->edges = realloc(graph->edges, sizeof(Edge) * (graph->edges_amount));
    graph->edges[graph->edges_amount - 1] = e;

    return 0;
}

int delete_vertex(Graph *graph, char *vertex) {
    int vertex_index = -1;
    for (int i = 0; i < graph->vertices_amount; ++i) {
        if (strcmp(vertex, graph->vertices[i].name) == 0) {
            vertex_index = i;
            break;
        }
    }

    if (vertex_index == -1) return -1;

    int elements_to_move;
    char *name = graph->vertices[vertex_index].name;
    for (int i = 0; i < graph->edges_amount; ++i) {
        if ((strcmp(name, graph->edges[i].from) == 0) || (strcmp(name, graph->edges[i].to) == 0)) {
            elements_to_move = graph->edges_amount - i - 1;
            memmove(&graph->edges[i], &graph->edges[i + 1], elements_to_move * sizeof(Edge));
            graph->edges_amount -= 1;
            graph->edges = realloc(graph->edges, sizeof(Edge) * (graph->edges_amount));
            i -= 1;
        }
    }

    elements_to_move = graph->vertices_amount - vertex_index - 1;
    memmove(&graph->vertices[vertex_index], &graph->vertices[vertex_index + 1], elements_to_move * sizeof(Vertex));
    graph->vertices_amount -= 1;

    return 0;
}

int delete_edge(Graph *graph, char *from, char *to) {
    for (int i = 0; i < graph->edges_amount; ++i) {
        if ((strcmp(from, graph->edges[i].from) == 0 && strcmp(to, graph->edges[i].to) == 0) || (strcmp(from, graph->edges[i].to) == 0 && strcmp(to, graph->edges[i].from) == 0)) {
            int elements_to_move = graph->edges_amount - i - 1;
            memmove(&graph->edges[i], &graph->edges[i + 1], elements_to_move * sizeof(Edge));
            graph->edges_amount -= 1;
            graph->edges = realloc(graph->edges, sizeof(Edge) * (graph->edges_amount));
            return 0;
        }
    }

    return 1;
}

void print_graph_list(Graph *graph) {
    for (int i = 0; i < graph->edges_amount; ++i) {
        Edge e = graph->edges[i];
        printf("('%s', '%s') %d\n", e.from, e.to, e.weight);
    }
}

int vertex_index(Graph *graph, char *name) {
    for (int i = 0; i < graph->vertices_amount; ++i) {
        if (strcmp(name, graph->vertices[i].name) == 0) {
            return i;
        }
    }

    return -1;
}

void print_graph_matrix(Graph *graph) {
    int matrix[graph->vertices_amount][graph->vertices_amount]; 

    for (int i = 0; i < graph->vertices_amount; ++i) {
        for (int j = 0; j < graph->vertices_amount; ++j) {
            matrix[i][j] = -1;
        }
    }

    for (int i = 0; i < graph->edges_amount; ++i) {
        Edge e = graph->edges[i];
        int from = vertex_index(graph, e.from);
        int to = vertex_index(graph, e.to);
        matrix[from][to] = e.weight;
        matrix[to][from] = e.weight;
    }

    for (int i = 0; i < graph->vertices_amount; ++i) {
        printf("%s ", graph->vertices[i]);
    }
    printf("\n");

    for (int i = 0; i < graph->vertices_amount; ++i) {
        for (int j = 0; j < graph->vertices_amount; ++j) {
            if (matrix[i][j] == -1) {
                printf(". ");
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int bellman_ford(Graph *graph, char* from, char *to) {
    int from_index = vertex_index(graph, from);
    int to_index = vertex_index(graph, to);
    if (from_index == -1 || to_index == -1) return -1;

    int *d = malloc(graph->vertices_amount * sizeof(int));
    int *pred = malloc(graph->vertices_amount * sizeof(int));

    int INF = 2 * 1e9;
    for (int i = 0; i < graph->vertices_amount; ++i) {
        d[i] = INF;
        pred[i] = -1;
    }

    d[from_index] = 0;

    for (int i = 0; i < graph->vertices_amount; ++i) {
        for (int j = 0; j < graph->edges_amount; ++j) {
            Edge e = graph->edges[j];
            int f_index = vertex_index(graph, e.from);
            int t_index = vertex_index(graph, e.to);
            if (d[t_index] > d[f_index] + e.weight) {
                d[t_index] = d[f_index] + e.weight;
                pred[t_index] = f_index;
            } else if (d[f_index] > d[t_index] + e.weight) {
                d[f_index] = d[t_index] + e.weight;
                pred[f_index] = t_index;
            }


        }
    }

    Node *lst = NULL;

    int cur_index = to_index;
    while (cur_index != from_index) {
        if (cur_index == -1) {
            printf("Path doesn't exists\n");
            Node *cur_node = lst;
            while (cur_node != NULL) {
                Node *tmp = cur_node;
                cur_node = cur_node->next;
                free(tmp);
            }
            free(d);
            free(pred);
            return 1;
        }
        Node *new_node = malloc(sizeof(Node));
        new_node->info = graph->vertices[cur_index].name;
        new_node->next = NULL;
        
        if (lst == NULL) new_node->next = NULL;
        else new_node->next = lst;
    
        lst = new_node;
        cur_index = pred[cur_index];
    }

    printf("Path length: %d\n", d[to_index]);
    printf("Path: %s ", from);
    Node *cur_node = lst;
    while (cur_node != NULL) {
        printf("%s ", cur_node->info);
        Node *tmp = cur_node;
        cur_node = cur_node->next;
        free(tmp);
    }
    printf("\n");

    free(d);
    free(pred);
    return 0;
}

int bfs(Graph *graph, char *from, char *to) {
    int from_index = vertex_index(graph, from);
    int to_index = vertex_index(graph, to);
    if (from_index == -1 || to_index == -1) return -1;

    int *d = malloc(graph->vertices_amount * sizeof(int));
    int *pred = malloc(graph->vertices_amount * sizeof(int));
    int *color = malloc(graph->vertices_amount * sizeof(int));

    int INF = 2 * 1e9;
    for (int i = 0; i < graph->vertices_amount; ++i) {
        d[i] = INF;
        pred[i] = -1;
        color[i] = 0;
    }

    d[from_index] = 0;
    color[from_index] = 1;
    Queue *q = createQueue(graph->vertices_amount);
    enqueue(q, from_index);

    while (!isEmpty(q)) {
        int v = dequeue(q);
        for (int i = 0; i < graph->edges_amount; ++i) {
            if (strcmp(graph->vertices[v].name, graph->edges[i].from) == 0) {
                int f_index = vertex_index(graph, graph->edges[i].to);
                if (color[f_index] == 0 || color[f_index] == 1) {
                    color[f_index] = 1;
                    d[f_index] = d[v] + graph->edges[i].weight;
                    pred[f_index] = v;
                    enqueue(q, f_index);
                }
            } else if (strcmp(graph->vertices[v].name, graph->edges[i].to) == 0) {
                int t_index = vertex_index(graph, graph->edges[i].from);
                if (color[t_index] == 0 || color[t_index] == 1) {
                    color[t_index] = 1;
                    d[t_index] = d[v] + graph->edges[i].weight;
                    pred[t_index] = v;
                    enqueue(q, t_index);
                }
            }
        }
        color[v] = 2;
    }


    Node *lst = NULL;

    int cur_index = to_index;
    while (cur_index != from_index) {
        if (cur_index == -1) {
            printf("Path doesn't exists\n");
            Node *cur_node = lst;
            while (cur_node != NULL) {
                Node *tmp = cur_node;
                cur_node = cur_node->next;
                free(tmp);
            }
            free(d);
            free(pred);
            free(color);
            free(q->array);
            free(q);
            return 1;
        }
        Node *new_node = malloc(sizeof(Node));
        new_node->info = graph->vertices[cur_index].name;
        new_node->next = NULL;
        
        if (lst == NULL) new_node->next = NULL;
        else new_node->next = lst;
    
        lst = new_node;
        cur_index = pred[cur_index];
    }

    printf("Path length: %d\n", d[to_index]);
    printf("Path: %s ", from);
    Node *cur_node = lst;
    while (cur_node != NULL) {
        printf("%s ", cur_node->info);
        Node *tmp = cur_node;
        cur_node = cur_node->next;
        free(tmp);
    }
    printf("\n");

    free(d);
    free(pred);
    free(color);
    free(q->array);
    free(q);
    return 0;
}

void clear_memory(Graph *graph) {
    free(graph->vertices);
    free(graph->edges);
    free(graph);
}

void print_graph(Graph *graph, char *filename) {
    FILE *fptr = fopen("graph.dot","w");
    fprintf(fptr,"digraph GraphViz {\n");

    for (int i = 0; i < graph->edges_amount; ++i) {
        fprintf(fptr,"\"%s\" -> \"%s\" [label=\"%d\", arrowhead=none];\n", graph->edges[i].from, graph->edges[i].to, graph->edges[i].weight);
    }

    fprintf(fptr,"}");
    fclose(fptr);
    char command[100] = "dot -Tpng graph.dot > ";
    strcat(command, filename);
    system(command);
}