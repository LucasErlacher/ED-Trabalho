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

double tempoMaquina(double tempoMaquina);

MAQ *criar_maquina();

void inserir_maquina(MAQ *maquina, ROL* rolamento);
ROL* libera_maquina(MAQ *maquina);
float pegar_tempo_processamento(MAQ *maquina);
float tempo_livre(MAQ *maquina);

#endif