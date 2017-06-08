#ifndef __default__
#define __default__

#include <stdio.h>
#include <stdlib.h>

#endif

#ifndef __bibNODO__
#define __bibNODO__

#include "nodo.h"

#endif

nodo* create_nodo(void* object){
	nodo* n;
	if ((n = malloc(sizeof(nodo))) == NULL){
		return NULL;
	};
	n->elem = (void*)object;
	n->prox = NULL;
	n->ant = NULL;
	return n;
}

nodo* next_nodo(nodo* current_nodo){
	nodo *n1 = current_nodo->prox;
	return n1;
}

nodo* previous_nodo(nodo* current_nodo){
	nodo *n1 = current_nodo->ant;
	return n1;
}

void* get_ElemNodo(nodo* n){
	void *obj = NULL;
	if (n!=NULL){
		obj = n->elem;
	}
	return obj;
}