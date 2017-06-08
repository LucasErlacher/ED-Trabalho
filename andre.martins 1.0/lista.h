#ifndef LISTA_H_
#define LISTA_H_
#include "nodo.h"

typedef void (*funcao)(void*);

typedef struct tlista
{
	struct tnodo* head; /* Head pointer either points to a node with data or NULL */
	unsigned int size; /* Size of the linked list */
	
	void (*append_first)(); 
	void (*append)(); 
	void (*append_index)(); 
	
	int (*get_size)();
	void* (*get_index)(); 
} lista;

/* Criação */
lista* criar_lista();

/* Adicionar Elementos */
void append_first(lista* llist, void* data); // Adiciona ao inicio
void append(lista* llist, void* data); // Adiciona ao final
void append_index(lista* llist, void* data, int index); // Adiciona no Index

/* Remover da Lista */
// int remove_front(list* llist, funcao free_func);
// int remove_index(list* llist, int index, funcao free_func);
// int remove_back(list* llist, funcao free_func);

/* Consulta */
int get_size(lista* llist); // Retorna tamanho da lista
void* get_index(lista* llist, int index); // Retorna dado do index 
nodo* get_nodo_index(lista* llist, int index); // Retorna NODO


void funcao_in_lista(lista* llist, funcao do_func);
void funcao_in_index(lista* llist, int index, funcao do_func);

void teste();

#endif // LISTA_H_
