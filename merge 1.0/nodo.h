#ifndef NODO_H_
#define NODO_H_

typedef struct nodo
{
	struct nodo* prev; /* Nodo anterior */
	struct nodo* next; /* Nodo seguinte */
	void* elem; /* dado salvo */
} nodo;

nodo* criar_nodo(void* elem);
nodo* proximo_nodo(nodo* current_nodo);
nodo* anterior_nodo(nodo* current_nodo);
void* get_elem(nodo* n);

#endif // NODO_H_


