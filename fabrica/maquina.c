#include "maquina.h"
#include <stdlib.h>

MAQ *criar_maquina(double (*geraTempo)(double)){
	MAQ *maquina = (MAQ*) malloc(sizeof(MAQ));

	maquina->tempo_livre = 0;
	maquina->func = geraTempo;

	return maquina;
}

void inserir_maquina(MAQ *maquina, ROL* rolamento, double tempo_atual, double tempoProcessamento){
	maquina->elem = rolamento;

	double tempo_livre;
	tempo_livre = (maquina->func)(tempoProcessamento) + tempo_atual;

	maquina->tempo_livre = tempo_livre;
	return;
}

ROL* libera_maquina(MAQ *maquina){
	ROL *rolamento = maquina->elem;
	maquina->elem = NULL;
	return rolamento;
}

double tempo_livre(MAQ *maquina){
	return maquina->tempo_livre;
}