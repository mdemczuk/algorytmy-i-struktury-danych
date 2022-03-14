#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "adjacency_matrix.h"
#include "instance_generator.h"

#ifdef HAMILTON_NO_CYCLE
    int ns[] = { 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18 };
#else
    int ns[] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 };
#endif
float density = 0.5f;

bool hamilton(struct graph *g, int n, int *path) {
    int u = path[n - 1];                     //wierzcholek u to ostatni element z tablicy path
    int v = 0;
    int in_path = 0;
    if(n == g->size){ 
        v = path[0];
        if(graph_has_edge(g, u, v))          //sprawdzenie istnienia krawedzi miedzy pierwszym i ostatnim wierzcholkiem na sciezce
            return true;
        else
            return false;
    }
    for(v = 0; v < g->size; v++){                   //szukanie krawedzi miedzy u a v, v nie moze byc na sciezce
        in_path = 0;
        if(graph_has_edge(g, u, v) && (u != v)){
            for(int j = 0; j < n; j++)
                if(path[j] == v)                    //jesli v na sciezce, to in_path przyjmuje wartosc 1
                    in_path = 1;
            if(!in_path){                           //jesli v nie ma na sciezce, to jest ono do niej dopisane
                path[n] = v;
                if(hamilton(g, n + 1, path))        //sprawdzenie hamilton dla n+1
                    return true;
                else                                //jesli hamilton dla n+1 zwraca false, to szukamy innej krawedzi
                    continue;
            }
        }
    }
    return false;
}

void check_hamilton(struct graph *g, int *path) {
    int u, v;

    // check if edges exist between consecutive vertices
    for (int i = 1; i < g->size; i++) {
        u = path[i - 1];
        v = path[i];
        assert(graph_has_edge(g, u, v));
    }

    // check if this is a cycle
    u = path[g->size - 1];
    v = path[0];
    assert(graph_has_edge(g, u, v));

    // check that `path` does not contain duplicates
    bool *occurrences = calloc(g->size, sizeof(bool));
    for (int i = 0; i < g->size; i++) {
        u = path[i];
        assert(occurrences[u] == false);
        occurrences[u] = true;
    }
}

int min_positive_degree(struct graph *g) {
    int min_degree = INT_MAX;
    int min_vertex = -1;

    for (int i = 0; i < g->size; i++) {
        int degree = 0;
        for (int j = 0; j < g->size; j++) {
            degree += graph_has_edge(g, i, j) ? 1 : 0;
        }
        if (degree > 0 && degree < min_degree) {
            min_degree = degree;
            min_vertex = i;
        }
    }

    return min_vertex;
}

int main() {
    srand(time(NULL));

    for (unsigned int i = 0; i < sizeof(ns) / sizeof(*ns); i++) {
        int n = ns[i];

        // generate instance
        struct graph *g = generate(n, density);

#ifdef HAMILTON_NO_CYCLE
        // isolate a vertex (remove all its edges)
        int u = min_positive_degree(g);
        for (int v = 0; v < g->size; v++) {
            graph_remove_edge(g, u, v);
        }
#endif

        // prepare memory for storing hamiltionian cycle
        int *cycle = calloc(n, sizeof(int));
        /*for(int i = 0; i < n; i++)
            cycle[i] = -1;*/
        cycle[0] = min_positive_degree(g);
        //printf("min_positive_degree = %d\n", cycle[0]);

        // find hamiltionian cycle
        clock_t hamilton_time = clock();
        bool found = hamilton(g, 1, cycle);
        hamilton_time = clock() - hamilton_time;

        // check if it is correct (if found)
        if (found) {
            check_hamilton(g, cycle);
        }
        else
            printf("Nie ma hamiltona dla %d wierzcholkow\n", n);

        printf("%-8d %-8g\n", n, (double)hamilton_time / CLOCKS_PER_SEC);

        free(cycle);
        graph_destroy(g);
    }
    return 0;
}
