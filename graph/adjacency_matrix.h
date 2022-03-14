#ifndef _ADJACENCY_MATRIX_H_
#define _ADJACENCY_MATRIX_H_

struct graph {
    size_t size;                // number of vertices
    int **matrix;               // adjacency matrix
};

struct graph *graph_create(size_t size) {
    struct graph *g = (struct graph*)malloc(sizeof(struct graph));          //alokacja pamięci na graf
    g->size = size;
    g->matrix = (int**)malloc(size * sizeof(int*));                         //tworzenie dwuwymiarowej tablicy matrix
    for(int i = 0; i < size; i++)
        g->matrix[i] = (int*)malloc(size * sizeof(int));
    for(int i = 0; i < size; i++)                                           //wypelnienie macierzy zerami
        for(int j = 0; j < size; j++)
            g->matrix[i][j] = 0;
    return g;
}

void graph_destroy(struct graph *g) {
    free(g);
}

void graph_add_edge(struct graph *g, int i, int j) {
    g->matrix[i][j] = 1;                                     //dodanie krawedzi pomiedzy wierzcholkiem i a wierzcholkiem j
}

bool graph_has_edge(struct graph *g, int i, int j) {
    if(g->matrix[i][j] == 1)                                 //jesli krawedz istnieje, funkcja zwraca true
        return true;
    else                                                     //jesli krawedz nie istnieje, funkcja zwraca false
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
