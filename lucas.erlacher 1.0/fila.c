#ifndef __default__

#define __default__

#include <stdio.h>
#include <stdlib.h>

#endif

#ifndef __bibNODO__

#define __bibNODO__

#include "nodo.h"

#endif

#ifndef __bibFILA__

#define __bibFILA__

#include "fila.h"

#endif

fila* inic_filaNULL(){
	fila *var = malloc(sizeof(fila));
	var->first = NULL;
	var->last = NULL;
	return var;
}

void insert_Nodo(fila* varFila, void* object){
	if(varFila->first == NULL){
		varFila->first = object;
		varFila->last = object;
	} 
	else{
		(varFila->last)->prox = object;
		varFila->last = object;
	}
	return;
}

void* peek(fila* varFila){
	void* value_temp;
	
	if(varFila->first == NULL){
		return NULL;
	}
	else{
		nodo *nTemp = varFila->first;
		value_temp = get_ElemNodo(nTemp); 
	}
	
	return value_temp;
}

void* pop_Elem(fila* varFila){
	nodo *nTemp = varFila->first;
	if(((varFila->first)->prox) != NULL){
		varFila->first = (varFila->first)->prox;
	}
	void *elem = get_ElemNodo(nTemp);
	
	free(nTemp);
	return elem;
}

void clear_Fila(fila* varFila){
	nodo *nTemp = varFila->first;
	
	while(nTemp != NULL){
		varFila->first = (varFila->first)->prox;
		free(nTemp);
		nTemp = varFila->first;
	}
	return;
}





















