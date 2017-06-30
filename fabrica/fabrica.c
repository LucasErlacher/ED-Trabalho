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
int compara(void *v1, void *v2);

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
	MAQ *torno1 = criar_maquina(tempoMaquina);
	MAQ *torno2 = criar_maquina(tempoMaquina);
	MAQ *fresa = criar_maquina(tempoMaquina);
	MAQ *mandril = criar_maquina(tempoMaquina);

	//Declarando Filas de Prioridade das Máquinas:
	fila_prioridade *fila_torno = criar_fila_prioridade();
	fila_prioridade *fila_mandril = criar_fila_prioridade();
	fila_prioridade *fila_fresa = criar_fila_prioridade();

	//Declarando Listas:
	lista *lista_tempo_livre_maquinas = criar_lista_ordenada(compara);
	lista *lista_tempo_chegada_pedidos = criar_lista_ordenada(compara);

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

	//Variáveis para o rolamento
	ROL *rolamento_atual;
	double tempoProcessamento;
	char prox_maquina;
	int quantidade_pedidos_esfericos;
	int prioridade;

	//Inicializa a Fabrica
	//Gera um novo tempo de pedido e atualiza a lista ordenada:
	if (menor == chegada_cilindrico)
	{
		rolamento_atual = criar_rolamento('c'); //Cria o rolamento
		tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
		inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
		chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO) + tempo_atual; //Gera um novo tempo para chegar um novo cilindrico
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_cilindrico); //Insere novamente na lista
		inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno1));
	} else if (menor == chegada_conico)
	{
		rolamento_atual = criar_rolamento('k');
		tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
		inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
		chegada_conico = chegadaPedido(CHEGADA_CONICO) + tempo_atual;
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_conico);
		inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno1));
	} else
	{
		rolamento_atual = criar_rolamento('a');
		tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
		inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
		chegada_esferico = chegadaPedido(CHEGADA_ESFERICO) + tempo_atual;
		inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_esferico);	
		inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(fresa));
		quantidade_pedidos_esfericos++;
	}

	while(tempo_atual < atof(argv[1])){

		double aux1, aux2;

		aux1 = *(double*)obter_ordenada(lista_tempo_chegada_pedidos,0);
		aux2 = *(double*)obter_ordenada(lista_tempo_livre_maquinas,0);

		if(aux1 < aux2)	menor = aux1; //Verifica quem é o menor (tempo de chegada ou tempo da maquina ficar livre)
		else menor = aux2;
		
		tempo_atual += menor; //Atualiza o tempo

		if(menor == chegada_cilindrico){

			remover_ordenada(lista_tempo_chegada_pedidos, 0); //Remove da lista de tempos de chegada o menor tempo
			rolamento_atual = criar_rolamento('c'); //Cria um novo rolamento

			if (tamanho(fila_torno) != 0)
			{
				prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
				inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
			}
			else
			{
				if(!ocupada(torno1))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno1));
				} 
				else if (!ocupada(torno2))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno2));
				}
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}
			}

			chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO) + tempo_atual; //Gera um novo tempo para chegar um novo cilindrico
			inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_cilindrico); //Insere o novo tempo na lista ordenada			

		} else if (menor == chegada_conico){ //Repete o mesmo procedimento que o anterior

			remover_ordenada(lista_tempo_chegada_pedidos, 0);
			rolamento_atual = criar_rolamento('k');

			if (tamanho(fila_torno) != 0)
			{
				prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
				inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
			}
			else
			{
				if(!ocupada(torno1))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno1));
				} 
				else if (!ocupada(torno2))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(torno2));
				}
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}
			}

			chegada_conico = chegadaPedido(CHEGADA_CONICO) + tempo_atual;
			inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_conico);			

		} else if (menor == chegada_esferico){ //Repete o mesmo procedimento que o anterior

			remover_ordenada(lista_tempo_chegada_pedidos, 0);
			if (quantidade_pedidos_esfericos % 9 == 0) rolamento_atual = criar_rolamento('t');
			else rolamento_atual = criar_rolamento('a');

			if (tamanho(fila_fresa) != 0)
			{
				prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
				inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
			}
			else
			{
				if(!ocupada(fresa))
				{
					tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_tempo_livre_maquinas, (double*)&tempo_livre(fresa));
				} 
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_fresa, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}
			}

			quantidade_pedidos_esfericos++;
			chegada_esferico = chegadaPedido(CHEGADA_ESFERICO) + tempo_atual;
			inserir_ordenada(lista_tempo_chegada_pedidos, (void*)&chegada_esferico);

		} else if (menor == *(double*)tempo_livre(torno1)){
			remover_ordenada(lista_tempo_livre_maquinas, 0);
			rolamento_atual = libera_maquina(torno1);
			prox_maquina = proxima_maquina(rolamento_atual);

			if (prox_maquina == '\0')
			{
				
			} 
			else if (prox_maquina == 'm')
			{
				/* code */
			}
			else
			{
				//Fresa
			}

			//Verifica se a próxima maquina está ocupada, se estiver, insere na fila de prioridades dela

		} else if (menor == *(double*)tempo_livre(torno2)){

		} else if (menor == *(double*)tempo_livre(fresa)){

		} else {

		}



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
	if (*(double*)v1 > *(double*)v2) return 1;
	else return 0;
}