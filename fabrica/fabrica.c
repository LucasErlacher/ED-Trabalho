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

//Declarando funções:
double chegadaPedido(double param);
double tempoMaquina(double tempoMaquina);
double compara(void *v1, void *v2);

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

	double tempo_total_cilindrico, tempo_total_conico, tempo_total_esferico_aco, tempo_total_esferico_titanio, tempo_atual;

	tempo_total_cilindrico = 0;
	tempo_total_conico = 0;
	tempo_total_esferico_titanio = 0;
	tempo_total_esferico_aco = 0;
	tempo_atual = 0;

	//Declarando máquinas - 2 Tornos, 1 Mandril e 1 Fresa:
	torno1 = criar_maquina(tempoMaquina);
	torno2 = criar_maquina(tempoMaquina);
	fresa = criar_maquina(tempoMaquina);
	mandril = criar_maquina(tempoMaquina);

	//Declarando Filas de Prioridade das Máquinas:
	fila_torno = criar_fila_prioridade();
	fila_mandril = criar_fila_prioridade();
	fila_fresa = criar_fila_prioridade();

	//Declarando Listas:
	lista_tempo_livre_maquinas = criar_lista_ordenada(compara);
	lista_tempo_chegada_pedidos = criar_lista_ordenada(compara);

	//Declarando chegada dos pedidos:
	double chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO);
	double chegada_conico = chegadaPedido(CHEGADA_CONICO);
	double chegada_esferico = chegadaPedido(CHEGADA_ESFERICO);

	//Insere os pedidos na lista para ser ordenado:
	inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_cilindrico);
	inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_conico);
	inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_esferico);

	//Pega o menor tempo que chegará o pedido:
	double menor = *(double*)obter_ordenada(lista_tempo_chegada_pedidos, 0);
	remover_ordenada(lista_tempo_chegada_pedidos, 0);

	tempo_atual = tempo_atual + menor;

	ROL *rolamento_atual;

	//Gera um novo tempo de pedido e atualiza a lista ordenada:
	if (menor == chegada_cilindrico)
	{
		rolamento_atual = criar_rolamento('c');
		inserir_maquina();
		chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO) + tempo_atual;
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_cilindrico);
	} else if (menor == chegada_conico)
	{
		rolamento_atual = criar_rolamento('k');
		inserir_maquina();
		chegada_conico = chegadaPedido(CHEGADA_CONICO) + tempo_atual;
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_conico);
	} else
	{
		rolamento_atual = criar_rolamento('a');
		inserir_maquina();
		chegada_esferico = chegadaPedido(CHEGADA_ESFERICO) + tempo_atual;
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_esferico);		
	}


	return 0;
}

/* Gera o tempo de chegada de um novo pedido */
double chegadaPedido(double param) {
	double u=0;
	do {
		u = (double) (rand()%RAND_MAX) / RAND_MAX;
	} while ((u==0) || (u==1));

	return (double) (-param * log (u));
}

/* Retorna o tempo de processamento em uma máquina específica. */
double tempoMaquina(double tempoMaquina) {
	return 2.0 * tempoMaquina * rand() / (RAND_MAX + 1.0);
}

int compara(void *v1, void *v2){
	if (*(double*)v1 < *(double*)v2) return 1;
	else return 0;
}