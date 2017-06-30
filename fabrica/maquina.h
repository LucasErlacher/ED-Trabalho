#ifndef __maquina__
#define __maquina__

#include "rolamento.h"
#include <stdlib.h>

typedef struct maquina MAQ;

struct maquina{
	ROL *elem;
	double tempo_livre; //Momento em que ficará disponível para uso
	double (*func)(double);
};

MAQ *criar_maquina();

void inserir_maquina(MAQ *maquina, ROL* rolamento, double tempo_atual, double tempoProcessamento);
ROL* libera_maquina(MAQ *maquina);
double* tempo_livre(MAQ *maquina);
int ocupada(MAQ *maquina);

#endif