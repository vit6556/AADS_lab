#include "struct.h"
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

int delete_vertex(Graph *graph, char *name) {
    int vertex_index = -1;
    for (int i = 0; i < graph->vertices_amount; ++i) {
        if (strcmp(vertex, graph->vertices[i].name) == 0) {
            vertex_index = i;
            break;
        }
    }

    if (vertex_index == -1) return -1;
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