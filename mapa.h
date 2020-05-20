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
