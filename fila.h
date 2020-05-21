/*
 *          #####      GRUPO       ##### 
 *
 *    Guilherme Amaral Hiromoto - nUSP: 11218959
 *    Maria Fernanda Lucio de Mello - nUSP: 11320860
 *    Paulo Matana da Rocha - nUSP: 10892676
 *    Victor Rodrigues Russo - nUSP: 11218855
 *
*/

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
