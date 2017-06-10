#ifndef LISTA_H_
#define LISTA_H_
#include "nodo.h"

typedef struct lista
{
	nodo* start;
	nodo* end;
	unsigned int size; /* Tamanho da lista */
} lista;

/* Inicio Cria��o da lista */
lista* criar_lista();
/* Fim Cria��o da lista */

/* Inicio Consulta */
int get_size(lista *lst);
void* get_index(lista* list, int index); 
nodo* get_nodo_index(lista* list, int index);
/* Fim Consulta */

/* Inicio Adicionar Elementos */
void inserir_start(lista* list, void* elem);
void inserir_index(lista* list, void* elem, int index);
void inserir(lista* list, void* elem);
/* Fim Adicionar Elementos */

/* Inicio Remover Elementos */
void remover_start(lista* list);
void remover_index(lista* list, int pos);
void remover_final(lista* list);
/* Fim Remover Elementos */

/* In�cio destruir toda a lista */
void destruir_lista(lista* list);
/* Fim destruir toda a lista*/

#endif
