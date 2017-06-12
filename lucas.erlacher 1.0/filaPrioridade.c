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
		varFila->first = varFila->last = nTemp; //Inicializa fila se não houver elementos
		printf("NOVO %p\n\n", (void*)nTemp);//-------------- TESTE ---------------
	}
	else
	{
		nodo_prioridade	*nAux = varFila->first; //Referência para o primeiro nodo da fila
		
		while((get_prioridade(nAux) < prioridade) && (nAux->next != NULL))
		{	
			nAux = nAux->next; //Caminha na fila até encontrar um nodo igual ou o próximo ser nulo
		}
		
		if((nAux->prev == NULL) && (get_prioridade(nAux) >= prioridade)) //Insere no começo
		{
			nTemp->next = nAux;
			nAux->prev = nTemp;
			varFila->first = nTemp;
			
			printf("NOVO %p -> %p \n\n", (void*)nTemp, (void*)nTemp->next);//-------------- TESTE ---------------
		}
		else if((nAux->next == NULL) && (get_prioridade(nAux) < prioridade)) //Insere no final
		{
			nAux->next = nTemp;
			nTemp->prev = nAux;
			varFila->last = nTemp;
			
			printf("%p <- NOVO %p\n\n", (void*)nTemp->prev, (void*)nTemp);//-------------- TESTE ---------------
		}
		else //Insere no meio
		{
			(nAux->prev)->next = nTemp;
			nTemp->prev = nAux->prev;
			nAux->prev = nTemp;
			nTemp->next = nAux;
			
			printf("%p <- NOVO %p -> %p \n\n", (void*)nTemp->prev, (void*)nTemp, (void*)nTemp->next);//-------------- TESTE ---------------
		}
		
	}
	
	(varFila->tam)++;
	
	return;
}

void* peek(fila_prioridade* varFila){
	void* value_temp;
	
	if(varFila->first == NULL){
		return NULL;
	}
	else{
		nodo_prioridade *nTemp = varFila->first;
		value_temp = get_ElemNodo(nTemp); 
	}
	
	return value_temp;
}

void* pop_Elem(fila_prioridade* varFila){
	nodo_prioridade *nTemp = varFila->last;
	
	if(nTemp->prev != NULL)	varFila->last = (varFila->last)->prev;

	void *elem = get_ElemNodo(nTemp);
	
	free(nTemp);
	
	(varFila->tam)--;
	
	return elem;
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