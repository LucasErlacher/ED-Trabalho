#ifndef __bibNODO__
#define __bibNODO__

#include "nodo.h"

#endif

typedef struct lista lista;

struct lista{
	nodo* ini;
	nodo* fin;
	int tam;
};

lista* inic_listNull();

int get_lenList(lista *lst);

void _insertStart(nodo* obj, lista* list);

void _insertFinal(nodo* obj, lista* list);

void _startList(nodo* obj, lista* list);

nodo* get_Object(lista* list,int pos);

void _removeFinal(lista* list);

void _removeStart(lista* list);

void removeObject(lista* list,int pos);

void insertElem(nodo* obj, lista* list, int pos);
