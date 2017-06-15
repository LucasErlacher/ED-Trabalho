#include "rolamento.h"
#ifndef _maquina_h_
#define _maquina_h_

typedef struct Maquina {
	Rolamento *item;
	double time_left;
} Maquina;

Maquina * criar_maquina();


#endif
