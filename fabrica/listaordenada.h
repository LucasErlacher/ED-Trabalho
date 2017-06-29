#ifndef __listaordenada__
#define __listaordenada__

#include "nodo.h"

typedef struct lista lista;

struct lista
{
	nodo *ini, *fim;
	int tam;
	int (*func)(void*,void*);
};

//int compara(void* elem1, void* elem2);
lista* criar_lista_ordenada(int (*func)(void*, void*));
void inserir_ordenada(lista *lst, void *elem);
void remover_ordenada(lista *lst, int pos);
void* obter_ordenada(lista *lst, int pos);
int tamanho_ordenada(lista *lst);
void destruir_lista_ordenada(lista *lst);

#endif