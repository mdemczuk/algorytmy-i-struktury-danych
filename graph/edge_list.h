#ifndef _EDGE_LIST_H_
#define _EDGE_LIST_H_

#include <stdbool.h>

struct edge_list {
    size_t size;                // number of edges
    int *vertices;              // adjacent vertices
};

struct graph {
    size_t size;                // number of vertices
    struct edge_list *edges;    // edge lists
};

struct graph *graph_create(size_t size) {
    struct graph *g = (struct graph*)malloc(sizeof(struct graph));                  //alokacja dynamiczna pamięci na graf
    g->size = size;
    g->edges = (struct edge_list*)malloc(size * sizeof(struct edge_list));          //alokacja dynamiczna tablicy wszytskich wierzcholkow w grafie
    for(int i = 0; i < size; i++){
        g->edges[i].size = 0;
        g->edges[i].vertices = (int*)malloc(size * sizeof(int));                    //utworzenie tablicy z wierzcholkami, z ktorymi sasiaduje wierzcholek i
        for(int k = 0; k < size; k++)
            g->edges[i].vertices[k] = -1;                                           //wypelnienie tablicy sasiadujacych wierzcholkow liczbami ujemnymi (brak krawedzi z innymi wierzcholkami)
    }
    return g;
}

void graph_destroy(struct graph *g) {
    free(g);
}

void graph_add_edge(struct graph *g, int i, int j) {
    for(int k = 0; k < g->size; k++){
        if(g->edges[i].vertices[k] < 0){             //wyszukanie "wolnego miejsca" w tablicy wierzcholkow sasiadujacych
            g->edges[i].size += 1;
            g->edges[i].vertices[k] = j;             //utworzenie krawedzi pomiedzy wierzcholkiem i a wierzcholkiem j
            break;
        }
    }
}

bool graph_has_edge(struct graph *g, int i, int j) {
    for(int k = 0; k < g->size; k++){
        if((g->edges[i]).vertices[k] == j)          //sprawdzenie czy wyst. krawedz pomiedzy wierzcholkiem i a wierzcholkiem j
            return true;
    }
    return false;
}

void dfs(struct graph *g, int i, int *visited) {
    if(visited[i] == 0)
        visited[i] = 1;
    int v;  // vertices to visit
    int s = g->size;
    for(v = 0; v < s; v++)
        if(graph_has_edge(g, i, v) && visited[v] == 0)
            dfs(g, v, visited);
}

void bfs(struct graph *g, int *visited) {
    int s = g->size;
    struct fifo *queue = fifo_create(s);
    fifo_enqueue(queue, 0);
    int i;

    while(!fifo_is_empty(queue)){
        i = fifo_dequeue(queue);
        visited[i] = 1;
        for(int v = 0; v < s; v++)
            if(graph_has_edge(g, i, v) && visited[v] == 0){
            fifo_enqueue(queue, v);
            visited[v] = 1;
        }
    }
}

#endif
