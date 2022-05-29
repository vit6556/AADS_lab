#ifndef GRAPH_H
#define GRAPH_H

int add_vertex(Graph *graph, char *vertex);
int add_edge(Graph *graph, char* from, char* to, int weight);
void print_graph_list(Graph *graph);
void print_graph_matrix(Graph *graph);

#endif