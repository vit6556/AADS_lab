#include "struct.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    Graph *graph = malloc(sizeof(graph));

    add_vertex(graph, "asf");
    add_vertex(graph, "asfd");
    add_edge(graph, "asfd", "asf", 5);
    add_edge(graph, "asf", "asf", 5);

    printf("\nList of edges:\n");
    print_graph_list(graph);

    printf("\nMatrix:\n");
    print_graph_matrix(graph);
}
