#ifndef _ADJACENCY_MATRIX_H_
#define _ADJACENCY_MATRIX_H_

#include <stdbool.h>

struct graph {
    int size;       // number of vertices
    int edges;      // number of edges
    bool **matrix;  // adjacency matrix
};

struct graph *graph_create(int size) {
    struct graph *g = malloc(sizeof(struct graph));
    g->size = size;
    g->edges = 0;

    g->matrix = malloc(size * sizeof(bool *));
    for (int i = 0; i < size; i++) {
        g->matrix[i] = calloc(size, sizeof(bool));
    }

    return g;
}

struct graph *graph_copy(struct graph *g) {
    struct graph *h = graph_create(g->size);
    h->edges = g->edges;

    for (int i = 0; i < g->size; i++) {
        memcpy(h->matrix[i], g->matrix[i], g->size * sizeof(bool));
    }
    return h;
}

void graph_destroy(struct graph *g) {
    for (int i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
}

bool graph_has_edge(struct graph *g, int i, int j) {
    return g->matrix[i][j];
}

void graph_add_edge(struct graph *g, int i,int j) {
    g->matrix[i][j] = 1;
    g->matrix[j][i] = 1;
    g->edges++;
}

void graph_remove_edge(struct graph *g, int i, int j) {
    g->matrix[i][j] = 0;
    g->matrix[j][i] = 0;
    g->edges--;
}

void dfs(struct graph *g, int i, int *visited) {
    if (!visited[i]) {
        visited[i] = 1;
        for (int j = 0; j < g->size; j++) {
            if (g->matrix[i][j] && !visited[j]) {
                dfs(g, j, visited);
            }
        }
    }
}

#endif
