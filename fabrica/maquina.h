#ifndef __maquina__
#define __maquina__

#include "rolamento.h"
#include <stdlib.h>

typedef struct maquina MAQ;

struct maquina{
	ROL *elem;
	float tempo_processamento; //Tempo que vai processar o rolamento
	float tempo_livre; //Momento em que ficará disponível para uso
};

MAQ *criar_maquina();

ROL* libera_maquina(MAQ *maquina);
float pegar_tempo_processamento(MAQ *maquina);
float tempo_livre(MAQ *maquina);

#endif