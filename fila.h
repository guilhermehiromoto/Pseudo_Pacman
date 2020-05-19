#ifndef FILA_H
#define FILA_H

typedef struct no NO;
typedef struct fila FILA;


FILA* fila_criar();

void fila_apagar(FILA** fila);

int fila_vazia(FILA* fila);

int fila_comeco(FILA* fila);

int fila_push(FILA* fila, int vertice);

int fila_pop(FILA* fila);

int fila_tamanho(FILA* fila);

int fila_cheia(FILA* fila);

int busca_fila(FILA* fila, int vertice);

#endif
