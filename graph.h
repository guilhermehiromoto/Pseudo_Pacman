#ifndef GRAFO_H
	#define GRAFO_H

	typedef struct grafo GRAFO;
	
	GRAFO* criar_grafo();
	
	void inserir_aresta(GRAFO* graph, int i, int j);

	void remover_aresta(GRAFO* graph, int i, int j);

	void exibir_matriz(GRAFO* graph, int n);
	
	int get_matriz(GRAFO* graph,int i, int j);

	void deleta_grafo(GRAFO* graph);

	int* calculate_path(GRAFO* graph ,int v, int u);

#endif
