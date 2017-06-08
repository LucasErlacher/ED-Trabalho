#include <stdio.h>
#include <stdlib.h>
#include "nodoPrioridade.h"

typedef struct fila fila;

struct fila{
	nodo* first;
	nodo* last;
	int tam;
};

fila* inic_filaNULL(){
	fila *var = malloc(sizeof(fila));
	var->tam = 0;
	var->first = NULL;
	var->last = NULL;
	return var;
}

void insert_Nodo(fila* varFila, void* object){
	/*
		TERMINAR ESTE CÓDIGO
	*/
	if(varFila->first == NULL){
		varFila->first = object;
		varFila->last = object;
		(varFila->tam)++;
	} 
	else{
		nodo* nTemp = varFila->first;
		
		/*Tamanho fila igual a 1*/
		if (varFila->tam == 1){
			if(object->prioridade > nTemp->prioridade){
				nTemp->prox = object;
				object->ant = nTemp;
				varFila->last = object;
			}else{
				nTemp->ant = object;
				object->prox = nTemp;
				varFila->first = object;
			}
		}
		
		while((nTemp->prox != NULL) && !(nTemp->prioridade == object->prioridade)){
			nTemp = nTemp->prox;
		}
		//FINALIZAR ESTE PONTO
		if(nTemp->ant == NULL){
			object->prox = nTemp;
			nTemp->ant = object;
			varFila->first = object;
		} else{
			
			object->prox = nTemp;
			nTemp->ant = object;
		}
		
		(varFila->tam)++;
	}
	return;
}

void* peek(fila* varFila){
	void* value_temp;
	
	if(varFila->first == NULL){
		return NULL;
	}
	else{
		nodo *nTemp = varFila->first;
		value_temp = get_ElemNodo(nTemp); 
	}
	
	return value_temp;
}

void* pop_Elem(fila* varFila){
	nodo *nTemp = varFila->first;
	if(((varFila->first)->prox) != NULL){
		varFila->first = (varFila->first)->prox;
	}
	void *elem = get_ElemNodo(nTemp);
	
	free(nTemp);
	return elem;
}

void clear_Fila(fila* varFila){
	nodo *nTemp = varFila->first;
	
	while(nTemp != NULL){
		varFila->first = (varFila->first)->prox;
		free(nTemp);
		nTemp = varFila->first;
	}
	return;
}