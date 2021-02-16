#include "graph.h"

int
main(int argc, char **argv){
	//program has input of users which use social network. There is
	//such thing as theorem of handshakes - you know anyone through
	//some number of friends. Program tells you length of "friends chain"
	//between user 1 and user 2 which you input
    GraphulaGraph graph;
    graphula_def_init(&graph);
    graphula_add_node(&graph, 1);
    graphula_add_node(&graph, 2);
    graphula_add_node(&graph, 3);
    graphula_add_node(&graph, 4);
    graphula_add_node(&graph, 5);
    graphula_add_node(&graph, 6);
    graphula_add_node(&graph, 7);
    graphula_add_edge(&graph, 1, 2, 1);
    graphula_add_edge(&graph, 2, 3, 1);
    graphula_add_edge(&graph, 3, 4, 1);
    graphula_add_edge(&graph, 4, 5, 1);
    graphula_add_edge(&graph, 5, 6, 1);
    graphula_add_edge(&graph, 6, 7, 1);
    graphula_add_edge(&graph, 7, 1, 1);
    int u1, u2;
    scanf("%d", &u1);
    scanf("%d", &u2);
    if (graphula_shortest_root(graph, u1, u2) >=0){
        printf("they are separated by minimum %d users", graphula_shortest_root(graph, u1, u2));
    } else {
	    printf("theorem of handshakes is broken");	
    }
    graphula_delete_edge(&graph, 1, 2);
    //now user 1 and user two are not friends anymore
    printf("after user 1 and user 2 stopped being friends:\n");
    if (graphula_shortest_root(graph, u1, u2) >=0){
        printf("they are separated by minimum %d users", graphula_shortest_root(graph, u1, u2));
    } else {
	    printf("theorem of handshakes is broken");	
    }
    graphula_free(graph);
    return 0;
}
