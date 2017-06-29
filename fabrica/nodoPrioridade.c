#include <stdlib.h>
#include "nodoPrioridade.h"

nodo_prioridade* criar_nodo_prioridade(void* object, int prioridade){
	nodo_prioridade *n;
	
	if ((n = malloc(sizeof(nodo_prioridade))) == NULL)	return NULL;
	
	n->elem = object;
	n->next = n->prev = NULL;
	n->prioridade = prioridade;
	
	return n;
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
