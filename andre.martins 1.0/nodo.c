#include <stdlib.h>
#include <stdio.h>
#include "nodo.h"

nodo* criar_nodo(void* data)
{
	nodo *n = malloc(sizeof(nodo));
	n->data = data;
	n->prev = NULL;
	n->next = NULL;
	return n;
}
