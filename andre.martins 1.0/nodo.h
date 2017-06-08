#ifndef NODO_H_
#define NODO_H_

typedef struct tnodo
{
	struct nodo* prev; /* Nodo anterior */
	struct nodo* next; /* Nodo seguinte */
	void* data; /* dado salvo */
} nodo;

nodo* criar_nodo(void* data);

#endif // NODO_H_

