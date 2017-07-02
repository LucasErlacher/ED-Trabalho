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
	}
	else{
		nodo_prioridade	*nAux = varFila->last; //Faz referencia para o primeiro nodo da fila

		while((get_prioridade(nAux) < prioridade) && (nAux->prev != NULL)){
			nAux = nAux->prev; //Caminha na fila até encontrar um nodo igual ou o próximo ser nulo
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

void* obter(fila_prioridade* varFila){
	void* value_temp;

	if(varFila->tam == 0){
		return NULL;
	}

	value_temp = (varFila->first)->elem;
	return value_temp;
}

void remover(fila_prioridade* varFila, int pos){
	nodo_prioridade *nCurrent = varFila->first;

	if (pos < varFila->tam)
	{
	    int i;
		for (i = 0; i < pos; ++i) nCurrent = nCurrent->next;
		if (pos == 0 && varFila->tam == 1)	varFila->first = varFila->last = NULL;
		else if (pos == 0)	varFila->first = nCurrent->next;
		else if (pos == (varFila->tam)-1)	varFila->last = nCurrent->prev;
		else
		{
			(nCurrent->prev)->next = nCurrent->next;
			(nCurrent->next)->prev = nCurrent->prev;
		}

		free(nCurrent);

		(varFila->tam)--;
	}

	return;
}

int tamanho(fila_prioridade *varFila){return varFila->tam;}

void destruirFila(fila_prioridade* varFila){
	nodo_prioridade *nTemp = varFila->first;

	while(nTemp != NULL){
		varFila->first = nTemp->next;
		free(nTemp);
		nTemp = varFila->first;
	}

	free(varFila);

	return;
}
