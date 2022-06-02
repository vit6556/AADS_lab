#ifndef GRAPH_H
#define GRAPH_H

int add_vertex(Graph *graph, char *vertex);
int add_edge(Graph *graph, char* from, char* to, int weight);
int delete_edge(Graph *graph, char *from, char *to);
int delete_vertex(Graph *graph, char *vertex);
int bellman_ford(Graph *graph, char* from, char *to);
void print_graph(Graph *graph, char *filename);
int bfs(Graph *graph, char *from, char *to);
void print_graph_list(Graph *graph);
void print_graph_matrix(Graph *graph);
void clear_memory(Graph *graph);

#endif