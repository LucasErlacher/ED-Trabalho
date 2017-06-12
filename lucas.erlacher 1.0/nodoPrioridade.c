#include <stdlib.h>
#include "nodoPrioridade.h"

nodo_prioridade* criar_nodo_prioridade(void* object,int prioridade){
	nodo_prioridade *n;
	
	if ((n = malloc(sizeof(nodo_prioridade))) == NULL)	return NULL;
	
	n->elem = object;
	n->next = n->prev = NULL;
	n->prioridade = prioridade;
	
	return n;
}

nodo_prioridade* next_nodo(nodo_prioridade* current_nodo){
	nodo_prioridade *n1 = current_nodo->next;
	return n1;
}

nodo_prioridade* previous_nodo(nodo_prioridade* current_nodo){
	nodo_prioridade *n1 = current_nodo->prev;
	return n1;
}

void* get_ElemNodo(nodo_prioridade* n){
	void *obj = NULL;
	if (n != NULL){
		obj = n->elem;
	}
	return obj;
}

int get_prioridade(nodo_prioridade* n){
	int value = n->prioridade;
	return value;
}