#ifndef __filaP__
#define __filaP__
#include "nodoPrioridade.h"

typedef struct fila fila_prioridade;

struct fila{
	nodo_prioridade *first, *last;
	int tam;
};

fila_prioridade* criar_fila_prioridade();
void inserir(fila_prioridade* varFila, void* elemento, int prioridade);
void* obter(fila_prioridade* varFila);
void remover(fila_prioridade* varFila, int pos);
int tamanho(fila_prioridade *varFila);
void destruirFila(fila_prioridade* varFila);

#endif
