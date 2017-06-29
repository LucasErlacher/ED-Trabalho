#include <stdlib.h>
#include "nodo.h"

nodo* create_nodo_ordenada(void* object){
	nodo* n;
	if ((n = malloc(sizeof(nodo))) == NULL)	return NULL;

	n->elem = object;
	n->prox = n->ant = NULL;
	return n;
}

void* get_ElemNodo_ordenada(nodo* n){
	void *obj = NULL;
	if (n != NULL){
		obj = n->elem;
	}
	return obj;
}