#include <stdlib.h>
#include <stdio.h>
#include "filaPrioridade.h"

fila_prioridade* criar_fila_prioridade(){
	fila_prioridade *var = malloc(sizeof(fila_prioridade));
	var->first = var->last = NULL;
	var->tam = 0;
	return var;
}

void inserir_prioridade(fila_prioridade* varFila, void* elemento, int prioridade){
	nodo_prioridade *nTemp = criar_nodo_prioridade(elemento, prioridade); //Encapsula o elemento e prioridade em um nodo
	
	if (varFila->tam == 0){
		varFila->first = varFila->last = nTemp; //Inicializa fila se nÃo houver elementos
	//	printf("%d if \n ", *(int*)nTemp->elem);
	}
	else{
		nodo_prioridade	*nAux = varFila->last; //Referenncia para o primeiro nodo da fila
		
		while((get_prioridade(nAux) < prioridade) && (nAux->prev != NULL)){
			nAux = nAux->prev; //Caminha na fila atÃ© encontrar um nodo igual ou o prÃ³ximo ser nulo
		}
		
		
		if((nAux->next == NULL) && (get_prioridade(nAux) >= prioridade)) //Insere no final
		{
			nTemp->prev = nAux;
			nAux->next = nTemp;
			varFila->last = nTemp;
		}
		else if((nAux->prev == NULL) && (get_prioridade(nAux) < prioridade)) //Insere no começo
		{
			nAux->prev = nTemp;
			nTemp->next = nAux;
			varFila->first = nTemp;
		}
		else //Insere no meio
		{
			nodo_prioridade *oldNext = nAux->next;
			
			nAux->next = nTemp;
			nTemp->prev = nAux;
			
			oldNext->prev = nTemp;
			nTemp->next = oldNext;
		}
	}
	
	(varFila->tam)++;
	
	return;
}

void* peek(fila_prioridade* varFila){
	void* value_temp;
	
	if(varFila->tam == 0){
		return NULL;
	}
	
	value_temp = (varFila->first)->elem;
	return value_temp;
}

int pop_Elem(fila_prioridade* varFila){
	int value = 0;
	
	if(varFila->tam != 0)
	{
		nodo_prioridade *nTemp = varFila->first;
		
		if(nTemp->next != NULL) {
			varFila->first = nTemp->next;
			(varFila->first)->prev = NULL;
		}
		else varFila->first = varFila->last = NULL;
		
		free(nTemp);
		
		(varFila->tam)--;
		
		value = 1;
	}
	

	return value;
}

void clear_Fila(fila_prioridade* varFila){
	nodo_prioridade *nTemp = varFila->first;
	
	while(nTemp != NULL){
		varFila->first = (varFila->first)->next;
		free(nTemp);
		nTemp = varFila->first;
	}
	return;
}
