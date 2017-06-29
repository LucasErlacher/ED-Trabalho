#include "maquina.h"
#include <stdlib.h>

MAQ *criar_maquina(){
	MAQ *maquina = (MAQ*) malloc(sizeof(MAQ));

	maquina->tempo_livre = 0;

	return maquina;
}

ROL* libera_maquina(MAQ *maquina){
	ROL *rolamento = maquina->elem;
	maquina->elem = NULL;
	return rolamento;
}

float pegar_tempo_processamento(MAQ *maquina){
	return maquina->tempo_processamento;
}

float tempo_livre(MAQ *maquina){
	return maquina->tempo_livre;
}