#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct GraphulaEdge GraphulaEdge;

typedef struct GraphulaNode GraphulaNode;

typedef GraphulaNode *GraphulaGraph;

int graphula_add_node(GraphulaGraph *gr, int index);

int graphula_add_edge(GraphulaGraph *gr, int index, int lead, int weight);

void graphula_print(GraphulaGraph graph);

int graphula_delete_edge(GraphulaGraph *gr, int index, int lead);

void graphula_free(GraphulaGraph graph);

int graphula_delete_node(GraphulaGraph *gr, int index);

int graphula_length(GraphulaGraph graph);

void graphula_print_graph_matrix(GraphulaGraph graph);

int graphula_shortest_root(GraphulaGraph graph, int start, int end);

void print_connect_groups(GraphulaGraph graph);

void graphula_def_init(GraphulaGraph *graph);

int graphula_init(GraphulaGraph *graph);

int graphula_file_init(GraphulaGraph *graph, char *name);
