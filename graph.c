#include "graph.h"

#include "vector.h"
#include "simbolTable.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_SIZE 100

struct Graph{
    int n_vertex;
    ST * adjacent_list; // vetor de listas.
};


Graph * graph_create(){
    Graph * g = (Graph*)malloc(sizeof(Graph));

    g->n_vertex = 0;
    g->adjacent_list = calloc(INITIAL_SIZE, sizeof(List*));

    return g;
}
void graph_destroy(Graph * graph){
    if(graph){

        if(graph->adjacent_list){
            for(int i = 0; i < graph->n_vertex; i++){
                list_destroy(graph->adjacent_list[i], NULL);
            }

            free(graph->adjacent_list);
        }

        free(graph);
    }
}
