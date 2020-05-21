/*
 *          #####      GRUPO       ##### 
 *
 *    Guilherme Amaral Hiromoto - nUSP: 11218959
 *    Maria Fernanda Lucio de Mello - nUSP: 11320860
 *    Paulo Matana da Rocha - nUSP: 10892676
 *    Victor Rodrigues Russo - nUSP: 11218855
 *
*/


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "mapa.h"

int main (void) {

	GRAFO* graph = criar_grafo();
	int content;
	int avoid = -1;

	// Inicia o grafo
	for (int i = 0; i<36; i++){
		for(int j = 0; j<36; j++){
			scanf("%d", &content);
			if(content == 1){
				inserir_aresta(graph,i,j);
		  	}
		}
	}

	// Inicia o mapa
	MAP* mapa = criar_mapa();

	// Enquanto o fantasma não encontra o PACMAN	
	while (!ghost_equals_pacman(mapa)) {
		move_pacman(mapa, graph, avoid); // PACMAN se move

		avoid = move_ghost(mapa, graph); 
		if(avoid == -1) // Se o fantasma encontra o PACMAN, fim de jogo
			break;
	}

	return 0;
}
