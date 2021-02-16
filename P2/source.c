#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

typedef GraphulaNode *GraphulaGraph;

GraphulaNode *graphula_blank_node(int index){
    GraphulaNode *graph = malloc(sizeof(GraphulaNode));
    if (graph == NULL){
		return NULL;
	}
    graph->index = index;
    graph->prev = NULL;
    graph->next = NULL;
    graph->edges = NULL;
    return graph;
}

GraphulaEdge *graphula_blank_edge(int lead, int weight){
    GraphulaEdge *edge = malloc(sizeof(GraphulaEdge));
    if (edge == NULL){
		return NULL;
	}
    edge->lead = lead;
    edge->weight = weight;
    edge->prev = NULL;
    edge->next = NULL;
    return edge;
}

int graphula_edge_exists(GraphulaEdge *edge, int lead){
    int ans = 0;
    GraphulaEdge *cycle = edge;
    if (edge != NULL){
        while (cycle->next != NULL){
            ans += (lead == cycle->lead);
            if (ans == 1){
                break;
            }
            cycle = cycle->next;
        }
        ans += (lead == cycle->lead) && (ans == 0);
        if (ans == 1){
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

GraphulaNode *graphula_node_exists(GraphulaGraph graph, int index){
    int ans = 0;
    GraphulaNode *cycle = graph;
    if (graph != NULL){
        while (cycle->next != NULL){
            ans += (index == cycle->index);
            if (ans == 1){
                break;
            }
            cycle = cycle->next;
        }
        ans += (index == cycle->index) && (ans == 0);
        if (ans == 1){
            return cycle;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

int graphula_add_node(GraphulaGraph *gr, int index){
    GraphulaGraph graph = *gr;
    if (graph == NULL){
        graph = graphula_blank_node(index);
        if (graph == NULL){
			return 6;
		}
        *gr = graph;
        return 0;
    }
    GraphulaNode *cycle = graph;
    if (graphula_node_exists(graph, index)){
        return 1;
    } else {
        while (cycle->next != NULL){
            cycle = cycle->next;
        }
        GraphulaNode *new = graphula_blank_node(index);
        if (new == NULL){
		    return 6;	
		}
        new->prev = cycle;
        cycle->next = new;
    }
    *gr = graph;
    return 0;
}

GraphulaEdge *graphula_find_last_edge(GraphulaEdge *edge){
    if (edge == NULL){
        return NULL;
    }
    GraphulaEdge *cycle = edge;
    while (cycle->next != NULL){
        cycle = cycle->next;
    }
    return cycle;
}

int graphula_add_edge(GraphulaGraph *gr, int index, int lead, int weight){
	if (weight < 0){
	    return 5;	
	}
	if (lead == index){
	    return 7;	
	}
    GraphulaGraph graph = *gr;
    if (graph == NULL){
        return 1;
    }
    GraphulaNode *graph_node = graphula_node_exists(graph, index);
    GraphulaNode *graph_lead = graphula_node_exists(graph, lead);
    if (graph_node == NULL){
        return 2;
    }
    if (graph_lead == NULL){
        return 3;
    }
    GraphulaEdge *edge1 = graph_node->edges;
    GraphulaEdge *edge2 = graph_lead->edges;
    if (graphula_edge_exists(edge1, lead) == 1){
        return 4;
    }
    edge1 = graphula_find_last_edge(edge1);
    edge2 = graphula_find_last_edge(edge2);
    GraphulaEdge *new = graphula_blank_edge(lead, weight);
    if (new == NULL){
	    return 6;	
	}
    if (edge1 == NULL){
        graph_node->edges = new;
    } else {
        edge1->next = new;
        new->prev = edge1;
    }
    new = graphula_blank_edge(index, weight);
    if (new == NULL){
	    return 6;	
	}
    if (edge2 == NULL){
        graph_lead->edges = new;
    } else {
        edge2->next = new;
        new->prev = edge2;   
    }   
    *gr = graph;
    return 0;
}

GraphulaEdge *graphula_delete_edge_in(GraphulaEdge *edge, int lead){
    if (edge == NULL){
        return NULL;
    }
    GraphulaEdge *cycle = edge;
    while (cycle->lead != lead){
        cycle = cycle->next;
    }
    if ((cycle ->prev == NULL) && ( cycle->next == NULL)){
        free(cycle);
        return NULL;
    }
    if (cycle->prev == NULL){
        cycle = cycle->next;
        free(cycle->prev);
        cycle->prev = NULL;
        return cycle;
    }
    if (cycle->next == NULL){
        cycle = cycle->prev;
        free(cycle->next);
        cycle->next = NULL;
        while (cycle->prev != NULL){
            cycle = cycle->prev;
        }
        return cycle;
    }
    GraphulaEdge *p, *n;
    p = cycle->prev;
    n = cycle->next;
    free(p->next);
    p->next = n;
    n->prev = p;
    return edge;
}

void graphula_print_edges(GraphulaEdge *edge, int index){
    if (edge == NULL){
        return;
    }
    while (edge->next != NULL){
        printf("  %d->{%d}->%d\n", index, edge->weight, edge->lead);
        edge = edge->next;
    }
    if (edge != NULL){
        printf("  %d->{%d}->%d\n", index, edge->weight, edge->lead);
    }
}

int graphula_print(GraphulaGraph graph){
	if (graph == NULL){
		return -1;
	}
    while (graph->next != NULL){
        printf("%d:\n", graph->index);
        graphula_print_edges(graph->edges, graph->index);
        graph = graph->next;
    }
    if (graph != NULL){
        printf("%d:\n", graph->index);
        graphula_print_edges(graph->edges, graph->index);
    }
    return 0;
}

int graphula_delete_edge(GraphulaGraph *gr, int index, int lead){
	if (gr == NULL){
	    return -1;
	}
    GraphulaGraph graph = *gr;
    GraphulaGraph cycle = graph;
    int flag = 0;
    while (cycle != NULL){
        if ((graphula_edge_exists(cycle->edges, lead)) && (cycle->index == index)){
            cycle->edges = graphula_delete_edge_in(cycle->edges, lead);
            flag = 1;
        }
        if ((graphula_edge_exists(cycle->edges, index)) && (cycle->index == lead)){
            cycle->edges =  graphula_delete_edge_in(cycle->edges, index);
            flag = 1;
        }
        cycle = cycle->next;
    }
    *gr = graph;
    return flag;
}

int graphula_free_edges(GraphulaEdge *edge){
	if (edge == NULL){
		return 1;
	}
    while (edge->next != NULL){
        if (edge->prev != NULL){
            free(edge->prev);
        }
        edge = edge->next;
    }
    if (edge->prev != NULL){
        free(edge->prev);
    }
    free(edge);
    return 0;
}

void graphula_free(GraphulaGraph graph){
	if (graph == NULL){
	    return;
	}
    while (graph->next != NULL){
        if (graph->edges != NULL){
            graphula_free_edges(graph->edges);
        }
        if (graph->prev != NULL){
            free(graph->prev);
        }
        graph = graph->next;
    }
    if (graph->prev != NULL){
        free(graph->prev);
    }
    if (graph->edges != NULL){
        graphula_free_edges(graph->edges);
    }
    free(graph);
}

int graphula_delete_node(GraphulaGraph *gr, int index){
    GraphulaGraph graph = *gr;
    if (gr == NULL){
	    return -1;
	}
    GraphulaGraph cycle = graph;
    int flag = 0;
    while (cycle != NULL){
        if (cycle->index == index){
            flag = 1;
            graphula_free_edges(cycle->edges);
            if ((cycle->next == NULL) && (cycle->prev == NULL)){
                free(cycle);
                *gr = NULL;
                return 0;
            }
            if (cycle->next == NULL){
                cycle = cycle->prev;
                free(cycle->next);
                cycle->next = NULL;
                break;
            } else {
                if (cycle->prev == NULL){
                    graph = cycle->next;
                    cycle = cycle->next;
                    free(cycle->prev);
                    cycle->prev = NULL;
                    break;
                } else {
                    GraphulaGraph p,n;
                    p = cycle->prev;
                    n = cycle->next;
                    cycle = cycle->next;
                    free(cycle->prev);
                    p->next = n;
                    n->prev = p;
                    break;
                }
            }
        }
        cycle = cycle->next;
    }
    if (flag == 0){
	    return 1;	
	}
    cycle = graph;
    while (cycle != NULL){
        if (graphula_edge_exists(cycle->edges, index)){
            cycle->edges = graphula_delete_edge_in(cycle->edges, index);
        }
        cycle = cycle->next;
    }
    *gr = graph;
    return 0;
}




int graphula_length(GraphulaGraph graph){
    int ans = 0;
    if (graph == NULL){
        return ans;
    }
    while (graph->next != NULL){
        ans ++;
        graph = graph->next;
    }
    ans++;
    return ans;
}

int graphula_pos_by_index(GraphulaGraph graph, int index){
    int count = 0;
    while (graph != NULL){
        if (graph->index == index){
            return count;
        }
        graph = graph->next;
        count ++;
    }
    return -1;
}

GraphulaNode *graphula_find_node(GraphulaGraph graph, int num){
    int flag = 1;
    GraphulaNode *cycle = graph;
    for (int i = 0; i < num; ++i){
        if (cycle == NULL){
            flag = 0;
            break;
        } else {
            cycle = cycle -> next;
        }
    }
    if (flag == 0){
        return NULL;
    } else {
        return cycle;
    }
}

void graphula_init_matrix(GraphulaGraph graph, int len, int matrix[][len]){
    for (int i = 0; i < len; ++i){
        GraphulaNode *node = graphula_find_node(graph, i);
        for (int j = 0; j < len; ++j){
            matrix[i][j] = 10005;
        }
        if (node == NULL){
            continue;
        }
        GraphulaEdge *edge = node->edges;
        if (edge == NULL){
            continue;
        }
        while (edge != NULL){
            matrix[i][graphula_pos_by_index(graph, edge->lead)] = edge->weight;
            edge = edge->next;
        }
            matrix[i][i] = 0;
    }   
}

void graphula_print_matrix(int len, int matrix[][len]){
    for (int i = 0; i < len; ++i){
        for (int j = 0; j < len; ++j){
			if (i == j){
				printf("%*d ", 7, 0);
			} else {
			    if (matrix[i][j] < 10000){
                    printf("%*d ", 7, matrix[i][j]);
		        } else {
				    printf("%*d ", 7, -1);
			    }
		    }
        }
        printf("\n");
    }
}

void graphula_print_graph_matrix(GraphulaGraph graph){
	int len = graphula_length(graph);
	if (len == 0){
	    return;	
	}
    int shortest_path[len][len];
    graphula_init_matrix(graph, len, shortest_path);
    graphula_print_matrix(len, shortest_path);
}


int graphula_shortest_root(GraphulaGraph graph, int start, int end){
    int len = graphula_length(graph);
    if (graph == NULL){
		return -5;
	}
    int shortest_path[len][len];
    graphula_init_matrix(graph, len, shortest_path);
    //graphula_print_matrix(len, shortest_path);
    int ans = 0;
    GraphulaNode *graph_start = graphula_node_exists(graph, start);
    GraphulaNode *graph_end = graphula_node_exists(graph, end);
    if ((graph_start == NULL) && (graph_end == NULL)){
        ans = -2;
        return ans;
    }
    if (graph_start == NULL){
        ans = -3;
        return ans;
    }
        if (graph_end == NULL){
        ans = -4;
        return ans;
    }
    int i, j, k;
    int max_sum = 0;
    for ( i = 0 ; i < len ; i++ ){
		for ( j = 0 ; j < len ; j++ ){
			max_sum += shortest_path[i][j];
		}
	}
	for ( i = 0 ; i < len ; i++ ){
		for ( j = 0 ; j < len ; j++ ){
			if ( shortest_path[i][j] == 0 && i != j ){
				shortest_path[i][j] = max_sum;
			}
		}
	}
	for ( k = 0 ; k < len; k++ ){
		for ( i = 0 ; i < len; i++ ){
			for ( j = 0 ; j < len ; j++ ){
				if ((shortest_path[i][k] + shortest_path[k][j]) < shortest_path[i][j]){
					shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j];
				}
			}
		}
	}

    int t1 = graphula_pos_by_index(graph, start);
    int t2 = graphula_pos_by_index(graph, end);
    ans = shortest_path[t1][t2];
    if (ans >= 10000){
        return -1;
    }
    return ans;
}

int graphula_is_there(int *mas, int len, int what){
    int flag = 0;
    for (int i = 0; i < len; ++i){
        if (mas[i] == what){
            flag = 1;
            break;
        }
    }
    return flag;
}

void print_connect_groups(GraphulaGraph graph){
    int len = graphula_length(graph);
    int *a = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i){
        a[i] = 0;
    }
    GraphulaGraph cycle;
    while (graphula_is_there(a, len, 0)){
        int count = 0;
        cycle = graph;
        while (a[count] != 0){
            count++;
            cycle = cycle->next;
        }
        a[count] = 2;
        GraphulaEdge *edge = cycle->edges;
        printf("%d ", cycle->index);
        while (edge != NULL){
            int where = graphula_pos_by_index(graph, edge->lead);
            if (a[where] != 2){
                a[where] = 1;
            }
            edge = edge->next;
        }
        while (graphula_is_there(a, len, 1)){
            count = 0;
            cycle = graph;
            while (a[count] != 1){
                count++;
                cycle = cycle->next;
            }
            edge = cycle->edges;
            a[count] = 2;
            printf("%d ", cycle->index);
            while (edge != NULL){
                int where = graphula_pos_by_index(graph, edge->lead);
                if (a[where] != 2){
                    a[where] = 1;
                }
                edge = edge->next;
            }
        }
        printf("\n");
    }
    free(a);
}

char *str_in(FILE *stream) {
    int c, len = 1;
    char *str = malloc(sizeof(char));
    while(((c = fgetc(stream)) != '\n') && (c != EOF)) {
        str[len - 1] = c;
        len++;
        str = realloc(str, len);
    }
    str[len - 1] = '\0';
    if (len == 1) {
        free(str);
        return NULL;
    }
    return str;
}

int graphula_init(GraphulaGraph *graph){
    char *str;
    while ((str = str_in(stdin)) != NULL){
        char c;
        sscanf(str, "%c", &c);
        if ((c != 'e') && (c != 'n')){
            free(str);
            return 1;
        }
        if (c == 'n'){
            int key;
            char *nex = str + 2*sizeof(char);
            sscanf(nex, "%d", &key);
            graphula_add_node(graph, key);
        } else {
            int key, key2, key3;
            char *nex = str + sizeof(char);
            sscanf(nex, "%d%d%d", &key,&key2,&key3);
            graphula_add_edge(graph, key, key2, key3);
        }
        free(str);
    }
    return 0;
}

int graphula_file_init(GraphulaGraph *graph, char *name){
    FILE *f = fopen(name, "r");
    if (f == NULL){
        return 1;
    }
    char *str;
    while ((str = str_in(f)) != NULL){
        char c;
        sscanf(str, "%c", &c);
        if ((c != 'e') && (c != 'n'))
            return 2;
        if (c == 'n'){
            int key;
            char *nex = str + 2*sizeof(char);
            sscanf(nex, "%d", &key);
            graphula_add_node(graph, key);
        } else {
            int key, key2, key3;
            char *nex = str + sizeof(char);
            sscanf(nex, "%d%d%d", &key,&key2,&key3);
            graphula_add_edge(graph, key, key2, key3);
        }
        free(str);
    }
    fclose(f);
    return 0;
}

void graphula_def_init(GraphulaGraph *graph){
	*graph = NULL;
}
