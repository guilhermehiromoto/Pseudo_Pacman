#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "fila.h"

struct grafo{
	int matriz[100][100]; 
};

GRAFO* criar_grafo(){
	GRAFO* graph = (GRAFO*)malloc(sizeof(GRAFO));
	return graph;
}

void inserir_aresta(GRAFO* graph, int i, int j){
	graph->matriz[i][j] = 1;
	graph->matriz[j][i] = 1;
}

void remover_aresta (GRAFO* graph, int i, int j){
	graph->matriz[i][j] = 0;
	graph->matriz[j][i] = 0;
}

void exibir_matriz(GRAFO* graph, int n){
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%d ", graph->matriz[i][j]);
		}	
		printf("\n");
	}
}

int get_matriz(GRAFO* graph,int i, int j){
	return graph->matriz[i][j];
}

void deleta_grafo(GRAFO* graph){
	free (graph);
}

void calculate_path_aux(int u,int i,int* path, int* shortest_path){
	if (u == -1)	return;
	calculate_path_aux(path[u],--i,path,shortest_path);
	shortest_path[i] = u;
}

int* calculate_path(GRAFO* graph,int v, int u){
	
	int* visited = (int*)malloc(36*sizeof(int));
	int* path = (int*)malloc(36*sizeof(int));
	int* shortest_path = (int*)malloc(36*sizeof(int));

	for(int i = 0; i<36; i++){
		visited[i]= -1;
		path[i]= -1;
		shortest_path[i] = -1;
	}

	FILA* fila = fila_criar();

	int i;

	fila_push(fila,v);
	int atual;
	visited[v] = 0;

	while(!fila_vazia(fila)){
		atual = fila_pop(fila);

		for(i=0; i<36; i++){
			if(graph->matriz[atual][i] == 1 && visited[i]==-1){
				fila_push(fila,i);
				visited[i] = visited[atual]+1;
				path[i] = atual;
			}
		}
	}

	calculate_path_aux(u, visited[u]+1, path, shortest_path);

	return shortest_path;
}



