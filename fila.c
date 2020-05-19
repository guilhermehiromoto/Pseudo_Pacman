#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

#define ERRO -32000

struct no{
	int vertice;
	NO* anterior;
};

struct fila{
	struct no* first;
	struct no* last;
	int tamanho;
};

FILA* fila_criar(){
	FILA* fila = (FILA*) malloc(sizeof(FILA));
	if(fila!=NULL){
		fila->first = NULL;
		fila->last = NULL;
		fila->tamanho = 0;
	}
	return (fila);
}

void fila_apagar(FILA** fila){
	if((*fila) == NULL) printf("LISTA INVALIDA\n");    
    else{    
        NO* p = (*fila)->first;    
        NO* aux = NULL;    
    
        while(p){    
            aux = p->anterior;    
            free(p);    
            p = aux;        
        }
        free (*fila);    
    }
}

int fila_vazia(FILA* fila){
	if(fila->tamanho==0){
		return 1;
	}
	return 0;

}

int fila_comeco(FILA* fila){
	if((fila!=NULL) && (!fila_vazia(fila))){
		return (fila->first->vertice);
	}
	return ERRO;
}

int fila_push(FILA* fila, int vertice){
	NO* pnovo = (NO*)malloc(sizeof(NO));
	if(pnovo!=NULL){
		pnovo->vertice = vertice;
		
		if(!fila_vazia(fila)){
			fila->last->anterior = pnovo;
		}else{
			fila->first = pnovo;
		}
		pnovo->anterior = NULL;
		fila->last = pnovo;
		fila->tamanho++;
		return(1);
	}
	return ERRO;
}


int fila_pop(FILA* fila){
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


int fila_tamanho(FILA* fila){
	return fila->tamanho;
}

int fila_cheia(FILA* fila){
	return fila->tamanho == 10;
}

int busca_fila_aux(NO* atual, int vertice){
	if(atual->anterior == NULL){
		if(atual->vertice == vertice) return 1;
		else return 0;
	}
		if(atual->vertice == vertice) return 1;
		else busca_fila_aux(atual->anterior, vertice);
	
	return ERRO;
}

int busca_fila(FILA* fila, int vertice){
	if(fila!= NULL && fila_vazia(fila))
		return 0;
	else
		busca_fila_aux(fila->first, vertice);
	return ERRO;
}

