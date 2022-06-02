#include "struct.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = malloc(sizeof(Vertex));
    graph->edges = malloc(sizeof(Edge));
    graph->vertices_amount = 0;
    graph->edges_amount = 0;

    add_vertex(graph, "a");
    add_vertex(graph, "b");
    add_vertex(graph, "c");
    add_vertex(graph, "d");
    add_vertex(graph, "f");
    add_edge(graph, "a", "b", 5);
    add_edge(graph, "c", "b", 1);
    add_edge(graph, "a", "c", 7);
    add_edge(graph, "a", "d", 3);

    printf("\nList of edges:\n");
    print_graph_list(graph);

    printf("\nMatrix:\n");
    print_graph_matrix(graph);

    char *from = "c";
    char *to = "d";
    printf("\nFind shortest path with bellman_ford between %s and %s:\n", from , to);
    bellman_ford(graph, from, to);


    from = "c";
    to = "d";
    printf("\nFind shortest path with bfs between %s and %s:\n", from , to);
    bfs(graph, from, to);

    from = "a";
    to = "d";
    printf("\nDelete (%s, %s) edge:\n", from, to);
    delete_edge(graph, from, to);
    printf("%d\n", graph->edges_amount);
    print_graph_matrix(graph);

    printf("\nDelete vertex %s:\n", from);
    delete_vertex(graph, "a");
    print_graph_matrix(graph);

    clear_memory(graph);
}
