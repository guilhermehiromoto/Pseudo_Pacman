/*
 *          #####      GRUPO       ##### 
 *
 *	  Guilherme Amaral Hiromoto - nUSP: 11218959
 *	  Maria Fernanda Lucio de Mello - nUSP: 11320860
 *    Paulo Matana da Rocha - nUSP: 10892676
 *    Victor Rodrigues Russo - nUSP: 11218855
 *
*/


#ifndef MAPA_H
#define MAPA_H
#include "graph.h"

typedef struct map MAP;

MAP* criar_mapa();
void printa_mapa(MAP* mapa);
void move_pacman(MAP* mapa, GRAFO* grafo, int avoid);
void clear_mapa(MAP* mapa);
int ghost_equals_pacman(MAP*);
int move_ghost(MAP* mapa, GRAFO* grafo);

#endif
