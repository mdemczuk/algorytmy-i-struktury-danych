CFLAGS	= -march=native -mtune=native -Ofast

outputs = bst adjacency_matrix edge_list

all: $(outputs)

bst: bst.c

adjacency_matrix: graph.c adjacency_matrix.h
	$(CC) $(CFLAGS) -DADJ_MATRIX -o $@ $<

edge_list: graph.c edge_list.h
	$(CC) $(CFLAGS) -DEDGE_LIST -o $@ $<


clean:
	$(RM) $(outputs)
