#include "maquina.h"
#include <stdlib.h>

MAQ *criar_maquina(double (*geraTempo)(double)){
	MAQ *maquina = (MAQ*) malloc(sizeof(MAQ));

	maquina->tempo_livre = 0;
	maquina->func = geraTempo;

	return maquina;
}

void inserir_maquina(MAQ *maquina, ROL* rolamento, double chegada, double tempo_atual){
	maquina->elem = rolamento;
	maquina->tempo_livre = (maquina->func)();
	return;
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