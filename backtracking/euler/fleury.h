#ifndef __FLEURY_H__
#define __FLEURY_H__

bool bridge(struct graph *g, int u, int v){				//funkcja sprawdza czy podana krawedz jest mostem grafu
	struct graph *h = graph_copy(g);
	int *visited = (int*)calloc(h->size, sizeof(int));
	dfs(h, u, visited);									//dfs dla grafu ze wszystkimi krawedziami
	int vertex1 = 0;
	for(int i = 0; i < h->size; i++){					//vertex1 wyznacza ilosc odwiedzonych wierzcholkow przed usunieciem krawedzi
		if(visited[i] == 1)
			vertex1++;
	}
	graph_remove_edge(h, u, v);							//usuniecie krawedzi u v
	memset(visited, 0, h->size * sizeof(int));
	dfs(h, u, visited);									//dfs dla grafu bez krawedzi u v
	int vertex2 = 0;
	for(int i = 0; i < h->size; i++){					//vertex2 wyznacza ilosc odwiedzonych wierzcholkow po usunieciu krawedzi
		if(visited[i] == 1)
			vertex2++;
	}
	free(visited);
	graph_destroy(h);
	if(vertex1 == vertex2) 				//jesli liczba odwiedzonych krawedzi jest rowna, funkcja zwraca false (krawedz nie jest mostem)
		return false;
	else
		return true;					//krawedz jest mostem jesli liczba odwiedzonych wierzcholkow sie rozni
}

void euler(struct graph *g, int *cycle) {
    int u = 0;
    int number_edges = 0;
    int size = g->edges + 1;
    for(int i = 0; i < size; i++){
    	cycle[i] = u;							//wierzcholek u jest dodawany do sciezki
    	for(int v = 0; v < g->size; v++)		//podliczenie ile krawedzi odchodzi od u
    		if(g->matrix[u][v] == 1)
    			number_edges++;
    	for(int v = 0; v < g->size; v++){
    		if(g->matrix[u][v] == 1){
    			if(number_edges > 1){				//jesli od wierzcholka odchodzi kilka krawedzi
    				if(!bridge(g, u, v)){			//jesli wybrana krawedz nie jest mostem, to krawedz jest usuwana
    					graph_remove_edge(g, u, v);
    					u = v;
    					break;
    				}
    			}
    			else{								//jesli jest to jedyna krawedz, to jest od razu usuwana
    				graph_remove_edge(g, u, v);
    				u = v;
    				break;
    			}
    		}
    	}
    	number_edges = 0;
    }
}

#endif
