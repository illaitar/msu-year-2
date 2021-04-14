                                                                           Alutis Nikita group 207

                           ═══════════════█████══════████═══════════════
                           ════════════███▒██═════════███████═══════════
                           ═════════███▒▒▒██═══════════██▒▒▒████════════
                           ══════████▒▒▒▒███════════════███▒▒▒▒███══════
                           ═════███▒▒▒▒████═════════════████▒▒▒▒▒███════
                           ═══███▒▒█▒█▒████═══██════██══█████▒█▒█▒███═══
                           ══███▒▒█▒█▒▒█████══████████══█████▒█▒██▒▒██══
                           ═███▒▒██▒█▒▒██████══██████═███████▒██▒██▒███═
                           ████▒██▒▒██▒██████████████████████▒██▒███▒███
                           ███▒▒██▒▒██▒█████████████████████▒███▒███▒███
                           ███▒████▒███▒███████████████████▒▒███▒███▒▒██
                           ═██▒▒███▒████▒██████████████████▒███▒████▒███
                           ═███▒████▒██████████████████████████▒████▒██═
                           ══██▒████████══███████████████══████████▒███═
                           ═══██▒███═██═══════████████══════██████████══
                           ════████════════════██████═══════════████════
                           ══════███══════════███══███══════════██══════
                           ═══════███═════════█══════█═════════███══════

/--------------------------------------------------------------------------------------------------\
|                                                                                                  |
|                                          Graphula Lib                                            |     
|                                                                                                  |
\--------------------------------------------------------------------------------------------------/

----------------------------------------------------------------------------------------------------
                                            Introduction
----------------------------------------------------------------------------------------------------
This library is written by second year student of CMC MSU - Nikita Alutis

It allows user to work with bidirectional weighted graph without edges from node to same node: 
create them and destroy. 
Also lib includes the implementation of Floyd algorithm and printing of connection groups.

Graph vertexes later called nodes have keys as int variable, they must be > 0 for correct results. 

Graph edges must have weight > 0 and < 10000 for correct functioning of Floyd algorithm and 
other functions

ATTENTION!!! Before working with graph it must be initialized using graphula_def_init function
Example:
    GraphulaGraph my_graph;
    graphula_def_init(&my_graph); 
----------------------------------------------------------------------------------------------------
                                           Implementation
----------------------------------------------------------------------------------------------------

Graph is list of nodes, each node has list of edges. Main type for user usage is GraphulaGraph

----------------------------------------------------------------------------------------------------
                                            Graph's type
----------------------------------------------------------------------------------------------------

Main Type (for user)
    typedef GraphulaNode *GraphulaGraph;

----------------------------------------------------------------------------------------------------
                                          Additional types
----------------------------------------------------------------------------------------------------
Additional types
    typedef struct GraphulaEdge{
        int lead;
        int weight;
        struct GraphulaEdge *prev;
        struct GraphulaEdge *next;
    } GraphulaEdge;

    typedef struct GraphulaNode{
        int index;
        struct GraphulaNode *prev;
        struct GraphulaNode *next;
        GraphulaEdge *edges;
    } GraphulaNode;
----------------------------------------------------------------------------------------------------
                                     Base functions (for user)
----------------------------------------------------------------------------------------------------
graphula_def_init:
    Synopsis:
        void 
        graphula_def_init(GraphulaGraph *graph)
    Description:
        Initializes graph. Should only be used once after declaration a variable of 
        type GraphulaGraph
    Input: 
        The address of variable of type GraphulaGraph

graphula_add_node:
    Synopsis:
        int 
        graphula_add_node(GraphulaGraph *gr, int index)
    Description:
        Creates a node in graph
    Input: 
        The address of variable of type GraphulaGraph
        int variable - node key
    Output: error code
        0 - OK
        1 - node already exists
        6 - not enough memory

graphula_add_edge:
    Synopsis:
        int 
        graphula_add_edge(GraphulaGraph *gr, int index, int lead, int weight)
    Description:
        Creates an edge in the graph
    Input: 
        The address of variable of type GraphulaGraph 
        int variable - first node key
        int variable - second node key
        int variable - weight of edge
    Output: error code
        0 - OK
        1 - graph is empty
        2 - there is no node 1 in graph
        3 - there is no node 2 in graph
        4 - there is already same edge
        5 - weight in input < 0
        6 - not enough memory
        7 - index and lead are the same

graphula_delete_edge:
    Synopsis:
        int 
        graphula_delete_edge(GraphulaGraph *gr, int index, int lead)
    Description:
        Deletes an edge from graph
    Input:
        The address of variable of type GraphulaGraph
        int variable - first node key
        int variable - second node key
    Output: error code
        0 - did't found one of nodes or the required edge
        1 - OK

graphula_delete_node:
    Synopsis:
        int 
        graphula_delete_node(GraphulaGraph *gr, int index)
    Description:
        Deletes node from graph
    Input: 
        The address of variable of type GraphulaGraph 
        int variable - node key
    Output: error code
        0 - OK
        1 - no node with this key in graph

graphula_free:
    Synopsis:
        void 
        graphula_free(GraphulaGraph graph)
    Description:
        Frees graph memory
    Input: 
        variable of type GraphulaGraph


graphula_length:
    Synopsis:
        int 
        graphula_length(GraphulaGraph graph)
    Description:
        Returns amount of nodes in graph
    Input:
        variable of type GraphulaGraph


graphula_print:
    Synopsis:
        void 
        graphula_print(GraphulaGraph graph)
    Description:
        Prints graph
    Input:
        variable of type GraphulaGraph
----------------------------------------------------------------------------------------------------
                                     Additional init functions
----------------------------------------------------------------------------------------------------
You should stick to the special input format for this functions to work correctly:

1)node
    n key

2)edges
    e key1 key2 weight

Пример:
    n 1
    n 2
    n 3
    e 1 2 5
    e 1 3 100

creates graph with nodes 1, 2, 3 and edges 1->{5}->2 и 1->{100}->3

Functions:

graphula_init:
    Synopsis:
        int 
        graphula_init(GraphulaGraph *graph)
    Description:
        Reads graph from stdin
    Input:
        variable of type GraphulaGraph

graphula_file_init:
    Synopsis:
        int 
        graphula_file_init(GraphulaGraph *graph, char *name)
    Description:
        Reads graph from file 
    Input:
        variable of type GraphulaGraph
        File name string
    Output:
        0 - OK
        1 - no such file
        2 - input ended not with eof, but with string not starting from e или c
            (Not correct format)
----------------------------------------------------------------------------------------------------
                                      Special Functions
----------------------------------------------------------------------------------------------------
graphula_shortest_root:
    Synopsis:
        int 
        graphula_shortest_root(GraphulaGraph graph, int start, int end
    Description:
        Finds the shortest route length from one node to another. If there is no route 
        it will return -1.
        Attention! For correct functioning all weights in graph must be >0 and <10000
        (
    Input:
        variable of type GraphulaGraph 
        int variable - first node key
        int variable - second node key
    Output: error code
         >0 - OK, route length
        -1 - no route
        -2 - both nodes missing
        -3 - first node missing
        -4 - second node missing

print_connect_groups:
    Synopsis:
	void 
	print_connect_groups(GraphulaGraph graph)
    Description:
        Prints graph connected groups
    Input:
        variable of type GraphulaGraph

graphula_print_graph_matrix:
    Synopsis:
        void 
        graphula_print_graph_matrix(GraphulaGraph graph)
    Description:
        Prints matrix of graph
    Input:
        variable of type GraphulaGraph
----------------------------------------------------------------------------------------------------
                                     Additional functions
----------------------------------------------------------------------------------------------------
Not included in header

graphula_blank_node:
    Synopsis:
        GraphulaNode 
        *graphula_blank_node(int index){
    Description:
        Allocates memory and creates template of node
    Input: 
        int variable - node key
    Output:
        *GraphulaNode

graphula_blank_edge:
    Synopsis:
        GraphulaEdge 
        *graphula_blank_edge(int lead, int weight)
    Description:
        Allocates memory and creates template of edge
    Input: 
        int variable - node key (key of node in which edge leads)
        int variable - weight of edge
    Output:
        *GraphulaEdge

graphula_node_exists:
    Synopsis:
        GraphulaNode 
        *graphula_node_exists(GraphulaGraph graph, int index)
    Description:
        Checks if there is node with this index in graph
    Input: 
        variable of type GraphulaGraph
        int variable - weight of edge
    Output:
        *GraphulaNode - if one exists
        NULL - not found node

graphula_edge_exists:
    Synopsis:
        int 
        graphula_edge_exists(GraphulaEdge *edge, int lead)
    Description:
        Checks if there is such edge in edge list
    Input:
        First element of list typeof *GraphulaEdge
        int variable - node key (key of node in which edge leads)
    Output:
        1 if edge exists
        0 if it doesn't

graphula_find_last_edge:
    Synopsis:
        GraphulaEdge 
        *graphula_find_last_edge(GraphulaEdge *edge)
    Description:
        Finds last edge in edge list
    Input:
        First element of list typeof *GraphulaEdge
    Output:
        Last edge typeof *GraphulaEdge if list is not empty
        NULL if list is empty

graphula_delete_edge_in:
    Synopsis:
        GraphulaEdge 
        *graphula_delete_edge_in(GraphulaEdge *edge, int lead)
    Description:
        Deletes edge from edge list
    Input:
        First element of list typeof *GraphulaEdge
    Output:
        First element of list typeof *GraphulaEdge
        NULL if new list is now empty

graphula_print_edges:
    Synopsis:
        void 
        graphula_print_edges(GraphulaEdge *edge, int index)
    Description:
        Prints edge list
    Input:
        First element of list typeof *GraphulaEdge

graphula_free_edges:
    Synopsis:
        void 
        graphula_free_edges(GraphulaEdge *edge)
    Description:
        Frees memory of edge list
    Input:
        First element of list typeof *GraphulaEdge

graphula_find_node:
    Synopsis:
        GraphulaNode 
        *graphula_find_node(GraphulaNode *graph, int num)
    Description:
        Returns node with required order number
    Input:
        variable of type GraphulaGraph
        int variable - node order number
    Output:
        *GraphulaNode - if one exists
        NULL - no such node
        

graphula_pos_by_index:
    Synopsis:
        int
        graphula_index(GraphulaGraph graph, int key)
    Description:
        Helps find the order number of node in nodes list by it's index
    Input:
        variable of type GraphulaGraph
        int variable - node key
    Output:
        Node's order number if it exists
        -1 - if node doesn't exist

graphula_init_matrix:
    Synopsis:
        void 
        graphula_init_matrix(GraphulaGraph graph, int len, int matrix[][len])
    Description:
        Creates matrix of graph
    Input:
        variable of type GraphulaGraph
        Amount of nodes in graph
        Matrix of int

graphula_print_matrix:
    Synopsis:
        void 
        graphula_print_matrix(int len, int matrix[][len])
    Description:
        Prints graph's matrix
    Input:
        Amount of nodes in graph
        Matrix of int

graphula_is_there:
    Synopsis:
        int 
        graphula_is_there(int *mas, int len, int what)
    Description:
        Checks if there is number in array
    Input:
        Int array
        Array length
        Variable int - what to look for

str_in:
    Synopsis:
        char 
        *str_in(FILE *stream)
    Description:
        Input of "infinite" (limited by memory) string from stream
    Input:
        Variable of type *FILE
    Output:
        string