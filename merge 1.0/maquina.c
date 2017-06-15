#include <stdio.h>
#include <stdlib.h>
#include "maquina.h"
#include "rolamento.h"

Maquina * criar_maquina(){
	Maquina * m = malloc(sizeof(Maquina));
	m->item = NULL;
	m->time_left = 0;
	
	return m;
}


