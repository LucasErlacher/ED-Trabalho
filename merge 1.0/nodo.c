#include <stdio.h>
#include <stdlib.h>
#include "nodo.h"


nodo* criar_nodo(void* elem){
	nodo* n;
	if ((n = malloc(sizeof(nodo))) == NULL){
		return NULL;
	};
	n->elem = (void*)elem;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

nodo* proximo_nodo(nodo* current_nodo){
	return current_nodo->next;
}

nodo* anterior_nodo(nodo* current_nodo){
	return current_nodo->prev;
}

void* get_elem(nodo* n){
	void *obj = NULL;
	
	if (n != NULL) obj = n->elem;
	
	return obj;
}
