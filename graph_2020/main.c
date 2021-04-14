#include "graph.h"

int
main(int argc, char **argv){
	if (argc == 1){
        return 1;
	}
    GraphulaGraph graph;
    graphula_def_init(&graph);
    graphula_file_init(&graph, argv[1]);
    graphula_print_graph_matrix(graph);
    graphula_print(graph);
    printf("shortest = %d\n",graphula_shortest_root(graph, 1, 2));
    printf("\n deleted edge 1->2 \n");
    graphula_delete_edge(&graph, 1, 2);
    graphula_print(graph);
    graphula_delete_node(&graph,4);
    printf("\n deleted node 4 \n");
    graphula_print(graph);
    print_connect_groups(graph);
    printf("graph length %d\n", graphula_length(graph));
    graphula_free(graph);
    return 0;
}
