#include "filaPrioridade.h"
#include "listaordenada.h"
#include "rolamento.h"
#include "maquina.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define CHEGADA_CILINDRICO 21.5
#define CHEGADA_CONICO 19.1
#define CHEGADA_ESFERICO 8.0

int main(int argc, char** argv){
	/*
		Para criar os rolamentos, basta chamar a função: criar_rolamento(tipo)

		Os tipos de rolamentos são:

		c - cilíndrico
		k - conico
		a - esferico de aço
		t - esferico de titanio
	*/

	//Declarando variáveis - Contabilizam QUANTIDADE TOTAL e TEMPO TOTAL de cada tipo de rolamento:
	int total_cilindrico, total_conico, total_esferico_aco, total_esferico_titanio;

	total_cilindrico = 0;
	total_conico = 0;
	total_esferico_titanio = 0;
	total_esferico_aco = 0;

	double tempo_total_cilindrico, tempo_total_conico, tempo_total_esferico_aco, tempo_total_esferico_titanio, tempo_total;

	tempo_total_cilindrico = 0;
	tempo_total_conico = 0;
	tempo_total_esferico_titanio = 0;
	tempo_total_esferico_aco = 0;
	tempo_total = 0;

	//Declarando máquinas - 2 Tornos, 1 Mandril e 1 Fresa:
	torno1 = criar_maquina();
	torno2 = criar_maquina();
	fresa = criar_maquina();
	mandril = criar_maquina();

	//Declarando Filas de Prioridade das Máquinas:
	fila_torno = criar_fila_prioridade();
	fila_mandril = criar_fila_prioridade();
	fila_fresa = criar_fila_prioridade();

	//Declarando Lista:
	lista_tempo_livre_maquinas = criar_lista_ordenada();
	return 0;
}

/* Gera o tempo de chegada de um novo pedido */
float chegadaPedido(float param) {
	float u=0;
	do {
		u = (float) (rand()%RAND_MAX) / RAND_MAX;
	} while ((u==0) || (u==1));

	return (float) (-param * log (u));
}

/* Retorna o tempo de processamento em uma máquina específica. */
float tempoMaquina(float tempoMaquina) {
	return 2.0 * tempoMaquina * rand() / (RAND_MAX + 1.0);
}