#ifndef __HIERHOLZER_H__
#define __HIERHOLZER_H__

void euler(struct graph *g, int *cycle) {
    struct stack *s = stack_create(g->edges + 1);			//utworzenie stosu
    int u = 0;
    stack_push(s, u);								//na stos dodany pierwszy wierzcholek
    int i = 0;
    while(!stack_is_empty(s)){						//dopoki stos nie jest pusty
    	u = stack_peek(s);							//do u przypisana wartosc z wierzchu stosu
    	for(int v = 0; v < g->size; v++){
    		if(g->matrix[u][v] == 1){				//szukanie krawedzi odchodzacej od u
    			graph_remove_edge(g, u, v);			//usuniecie krawedzi
    			stack_push(s, v);					//na stos trafia v
    			u = v;
    			v = -1;
    		}
    	}
    	cycle[i] = stack_pop(s);			//sciagniecie wartosci ze stosu i wpisanie jej do rozwiazania
    	i++;
    }
    stack_destroy(s);
}

#endif
