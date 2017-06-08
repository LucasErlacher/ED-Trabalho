#include <stdio.h>
#include <stdlib.h>

/*Nodo simples encadeado dinamicamente*/

typedef struct nodo nodo;

struct nodo{
	void* elem;
	int prioridade;
	nodo* prox;
	nodo* ant;
};

nodo* create_nodo(void* object,int prioridade){
	nodo* n;
	if ((n = malloc(sizeof(nodo))) == NULL){
		return NULL;
	};
	n->elem = (void*)object;
	n->prox = NULL;
	n->ant = NULL;
	n->prioridade = prioridade;
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

int get_Priority(nodo* n){
	int value = NULL;
	if(n != NULL){
		value = n->prioridade;
	}
	return value;
}