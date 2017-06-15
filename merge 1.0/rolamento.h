#include "filaPrioridade.h"
#ifndef _rolamento_h_
#define _rolamento_h_

typedef struct Rolamento
{
	fila_prioridade *funcoes;
	int prioridade;
} Rolamento;

void criar_cilindrico();
void criar_conico();
void criar_esfera_aco();
void criar_esferico_titanio();

#endif
