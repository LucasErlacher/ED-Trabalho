#ifndef __filaP__
#define __filaP__
#include "nodoPrioridade.h"

typedef struct fila fila_prioridade;

struct fila{
	nodo_prioridade *first, *last;
	int tam;
};

fila_prioridade* criar_fila_prioridade();
void inserir_prioridade(fila_prioridade* varFila, void* elemento, int prioridade);
void* peek(fila_prioridade* varFila);
void* pop_Elem(fila_prioridade* varFila);
void clear_Fila(fila_prioridade* varFila);

#endif