#ifndef __bibNODO__
#define __bibNODO__

#include "nodo.h"

#endif

typedef struct fila fila;

struct fila{
	nodo* first;
	nodo* last;
};

fila* inic_filaNULL();
void insert_Nodo(fila* varFila, void* object);
void* peek(fila* varFila);
void* pop_Elem(fila* varFila);
void clear_Fila(fila* varFila);