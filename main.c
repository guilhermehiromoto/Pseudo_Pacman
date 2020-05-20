#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mapa.h"

int main(){

	GRAFO* graph = criar_grafo();
	int content;
	int avoid = -1;

	for (int i = 0; i<36; i++){
		for(int j = 0; j<36; j++){
			scanf("%d", &content);
			if(content == 1){
				inserir_aresta(graph,i,j);
		  	}
		}
	}

	MAP* mapa = criar_mapa();

	while(!ghost_equals_pacman(mapa)){

		move_pacman(mapa, graph, avoid);

		avoid = move_ghost(mapa, graph);
		if(avoid == -1) break;
	}

	return 0;
}
