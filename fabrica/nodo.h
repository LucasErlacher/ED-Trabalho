#ifndef _nodo_h
#define _nodo_h

typedef struct nodo nodo;

struct nodo {
	void* elem;
	nodo* prox;
	nodo* ant;
};

nodo* create_nodo_ordenada(void* object);
void* get_ElemNodo_ordenada(nodo* n);

#endif