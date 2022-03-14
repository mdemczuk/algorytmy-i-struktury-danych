#ifndef __FLEURY_H__
#define __FLEURY_H__

bool bridge(struct graph *g, int u, int v) {
	struct graph *h = graph_copy(g);
	int *visited = (int*) calloc(h->size, sizeof(int));
	dfs(h, u, visited);
	int vertex1 = 0;
	for(int i = 0; i < h->size; i++)
		if(visited[i] == 1)
			vertex1++;
	graph_remove_edge(h, u, v);
	memset(visited, 0, h->size * sizeof(int));
	dfs(h, u, visited);
	int vertex2 = 0;
	for(int i = 0; i < h->size; i++)
		if(visited[i] == 1)
			vertex2++;

	free(visited);
    graph_destroy(h);

	if(vertex1 == vertex2)
		return false;
	else
		return true;
}



void euler(struct graph *g, int *cycle) {
    int u = 0;
    int numberEdges = 0;
    int size = g->edges + 1;
    for(int i = 0; i < size; i++){
        cycle[i] = u;
        for(int v = 0; v < g->size; v++)
            if(g->matrix[u][v] == 1)
                numberEdges++;
        for(int v = 0; v < g->size; v++) {
            if(g->matrix[u][v] == 1) {
                if(numberEdges > 1) {
                    if(bridge(g, u, v) == false) {
                        graph_remove_edge(g, u, v);
                        u = v;
                        break;
                    }
                }
                else {
                    graph_remove_edge(g, u, v);
                    u = v;
                    break;
                }
            }
        }
        numberEdges = 0;
    }
}


#endif
