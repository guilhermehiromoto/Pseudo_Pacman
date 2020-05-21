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
#include "fila.h"

#define ERRO -32000

// Struct define o nó, indicando qual o vértice e seu anterior
struct no {
	int vertice;
	NO* anterior;
};

// Essa struct cria uma fila com os nós implementados com ponteiros para o começo e o final, e indicador de tamanho
struct fila {
	struct no* first;
	struct no* last;
	int tamanho;
};

// Inicializa a fila
FILA* fila_criar () {
	FILA* fila = (FILA*) malloc(sizeof(FILA)); 
	if(fila!=NULL){
		fila->first = NULL;
		fila->last = NULL;
		fila->tamanho = 0;
	}
	return (fila);
}

// Finaliza fila
void fila_apagar (FILA** fila) {
	if((*fila) == NULL) printf("LISTA INVALIDA\n"); // Se não existe
    else {    
        NO* p = (*fila)->first; // Ponteiro auxiliar que indica o começo da fila    
        NO* aux = NULL;        
    
    	// Caminha pela fila liberando os nós (vértices)
        while (p){    
            aux = p->anterior;    
            free (p);    
            p = aux;        
        }
        free (*fila);    
    }
}

// Verifica se a fila está vazia 
int fila_vazia (FILA* fila) {
	if(fila->tamanho == 0){
		return 1;
	}
	return 0;
}

// Função que retorna o ínicio da fila == primeiro vértice
int fila_comeco (FILA* fila) {
	if((fila != NULL) && (!fila_vazia(fila))) {
		return (fila->first->vertice);
	}
	return ERRO;
}

// Função que insere novo vértice
int fila_push (FILA* fila, int vertice) {
	NO* pnovo = (NO*)malloc(sizeof(NO));
	if(pnovo != NULL) {
		pnovo->vertice = vertice; // Inicializa com o parametro passado
		
		if(!fila_vazia(fila)) {
			fila->last->anterior = pnovo; // Se a fila não estiver vazia, coloca o vértice na ultima posição
		}else {
			fila->first = pnovo; // Se estiver vazia, o novo vértice é também o primeiro
		}
		pnovo->anterior = NULL;
		fila->last = pnovo;
		fila->tamanho++;
		return(1);
	}
	return ERRO;
}

// Função que retira todos os vértices
int fila_pop (FILA* fila) {
	if((fila != NULL) && (!fila_vazia(fila))){
		NO* pnew = fila->first;
		int vertice = fila->first->vertice;
		fila->first = fila->first->anterior;
		pnew->anterior = NULL;
		free(pnew);
		pnew = NULL;
		fila->tamanho--;
		return vertice;
	}
	return-1;
}

// Retorna o tamanho da fila
int fila_tamanho (FILA* fila) {
	return fila->tamanho;
}

int fila_cheia (FILA* fila) {
	return fila->tamanho == 10;
}

// Função recursiva auxiliar para buscar o nó
int busca_fila_aux (NO* atual, int vertice) {
	if(atual->anterior == NULL){
		if(atual->vertice == vertice) return 1;
		else return 0;
	}
		if(atual->vertice == vertice) return 1;
		else busca_fila_aux(atual->anterior, vertice);
	
	return ERRO;
}

// Busca um nó (vértice)
int busca_fila (FILA* fila, int vertice) {
	if(fila != NULL && fila_vazia(fila))
		return 0;
	else
		busca_fila_aux(fila->first, vertice);
	return ERRO;
}

