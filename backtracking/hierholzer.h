#ifndef __HIERHOLZER_H__
#define __HIERHOLZER_H__

void euler(struct graph *g, int *cycle) {
    struct stack *s = stack_create(g->edges + 1);
    int u = 0;
   	stack_push(s, u);
   	int gSize = g->size;
	int i = 0;

   	while(!stack_is_empty(s))
   	{	
   		u = stack_peek(s);
   		for(int v = 0; v < gSize; v++)
   		{
   			if(g->matrix[u][v] == 1)
   			{
   				graph_remove_edge(g, u, v);
   				stack_push(s, v);
   				u = v;
   				v = -1;
   			}
   		}
   		cycle[i] = stack_pop(s);
   		i++;
   	}
}

#endif
