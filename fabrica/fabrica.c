#include "filaPrioridade.h"
#include "listaordenada.h"
#include "rolamento.h"
#include "maquina.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CHEGADA_CILINDRICO 21.5
#define CHEGADA_CONICO 19.1
#define CHEGADA_ESFERICO 8.0

//Declarando funções:
double chegadaPedido(double param);
double tempoMaquina(double tempoMaquina);
int compara(void *v1, void *v2);
void imprime_lista_ordenada(lista *lst);

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

    printf("Inicio do programa: \n");
    srand(time(NULL));

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

	double tempo_total_fabrica = atof(argv[1]);

	printf("\tVariaveis de tempo preparadas.\n");

	//Declarando máquinas - 2 Tornos, 1 Mandril e 1 Fresa:
	MAQ *torno1 = criar_maquina(tempoMaquina);
	MAQ *torno2 = criar_maquina(tempoMaquina);
	MAQ *fresa = criar_maquina(tempoMaquina);
	MAQ *mandril = criar_maquina(tempoMaquina);

	printf("\tMaquinas preparadas.\n");

	//Declarando Filas de Prioridade das Máquinas:
	fila_prioridade *fila_torno = criar_fila_prioridade();
	fila_prioridade *fila_mandril = criar_fila_prioridade();
	fila_prioridade *fila_fresa = criar_fila_prioridade();

	printf("\tFilas preparadas.\n");

	//Declarando Listas:
	lista *lista_ordenada = criar_lista_ordenada(compara);

	//Declarando chegada dos pedidos:
	double chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO);
	double chegada_conico = chegadaPedido(CHEGADA_CONICO);
	double chegada_esferico = chegadaPedido(CHEGADA_ESFERICO);

	printf("\tPedidos preparados.\n");

	//Insere os pedidos na lista para ser ordenado:
	inserir_ordenada(lista_ordenada, (void*)&chegada_cilindrico);
	inserir_ordenada(lista_ordenada, (void*)&chegada_conico);
	inserir_ordenada(lista_ordenada, (void*)&chegada_esferico);

	printf("\tPedidos inseridos na lista ordenada.\n");

	//Pega o tempo_atual tempo que chegará o pedido:
	tempo_atual = *(double*)obter_ordenada(lista_ordenada, 0);//*(double*)obter_ordenada(lista_ordenada, 0);

	remover_ordenada(lista_ordenada, 0);

	//Variáveis para o rolamento
	ROL *rolamento_atual;
	double tempoProcessamento;
	char prox_maquina;
	int quantidade_pedidos_esfericos = 0;
	int prioridade;

	//Inicializa a Fabrica
	//Gera um novo tempo de pedido e atualiza a lista ordenada:

	if (tempo_atual == chegada_cilindrico)
	{
		rolamento_atual = criar_rolamento('c', tempo_atual); //Cria o rolamento
		tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
		inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
		chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO) + tempo_atual; //Gera um novo tempo para chegar um novo cilindrico
		inserir_ordenada(lista_ordenada, (void*)&chegada_cilindrico); //Insere novamente na lista
		inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1)); //Insere o tempo que a máquina ficará livre na lista de tempos de máquina
	} else if (tempo_atual == chegada_conico) //Faz o mesmo que o anterior
	{
		rolamento_atual = criar_rolamento('k', tempo_atual);
		tempoProcessamento = pegar_tempo_torno(rolamento_atual);
		inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento);
		chegada_conico = chegadaPedido(CHEGADA_CONICO) + tempo_atual;
		inserir_ordenada(lista_ordenada, (void*)&chegada_conico);
		inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
	} else //Faz o mesmo que o anterior
	{
		rolamento_atual = criar_rolamento('a', tempo_atual);
		tempoProcessamento = pegar_tempo_fresa(rolamento_atual);
		inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento);
		chegada_esferico = chegadaPedido(CHEGADA_ESFERICO) + tempo_atual;
		inserir_ordenada(lista_ordenada, (void*)&chegada_esferico);
		inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
		quantidade_pedidos_esfericos++;
	}

	while(tempo_atual < tempo_total_fabrica)
	{
		tempo_atual = *(double*)obter_ordenada(lista_ordenada,0); //Atualiza o tempo

		if(tempo_atual == chegada_cilindrico){
			remover_ordenada(lista_ordenada, 0); //Remove da lista de tempos de chegada o tempo_atual tempo
			rolamento_atual = criar_rolamento('c', tempo_atual); //Cria um novo rolamento

				if((!ocupada(torno1)) && (tamanho(fila_torno) == 0))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
				}
				else if ((!ocupada(torno2)) && (tamanho(fila_torno) == 0))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno2));
				}
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}


			chegada_cilindrico = chegadaPedido(CHEGADA_CILINDRICO) + tempo_atual; //Gera um novo tempo para chegar um novo cilindrico
			inserir_ordenada(lista_ordenada, (void*)&chegada_cilindrico); //Insere o novo tempo na lista ordenada

		} else if (tempo_atual == chegada_conico){ //Repete o mesmo procedimento que o anterior
			remover_ordenada(lista_ordenada, 0);
			rolamento_atual = criar_rolamento('k', tempo_atual);

				if((!ocupada(torno1)) && (tamanho(fila_torno) == 0))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
				}
				else if ((!ocupada(torno2)) && (tamanho(fila_torno) == 0))
				{
					tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno2));
				}
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}

			chegada_conico = chegadaPedido(CHEGADA_CONICO) + tempo_atual;
			inserir_ordenada(lista_ordenada, (void*)&chegada_conico);

		} else if (tempo_atual == chegada_esferico){ //Repete o mesmo procedimento que o anterior
			remover_ordenada(lista_ordenada, 0);
			if (quantidade_pedidos_esfericos % 9 == 0) rolamento_atual = criar_rolamento('t', tempo_atual);
			else rolamento_atual = criar_rolamento('a', tempo_atual);

				if((!ocupada(fresa)) && (tamanho(fila_fresa) == 0))
				{
					tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
					inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
					inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
				}
				else
				{
					prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
					inserir_prioridade(fila_fresa, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
				}

			quantidade_pedidos_esfericos++;
			chegada_esferico = chegadaPedido(CHEGADA_ESFERICO) + tempo_atual;
			inserir_ordenada(lista_ordenada, (void*)&chegada_esferico);

		} else if (tempo_atual == *tempo_livre(torno1)){

			remover_ordenada(lista_ordenada, 0);
			rolamento_atual = libera_maquina(torno1);
			prox_maquina = proxima_maquina(rolamento_atual);

			if (atual_maquina(rolamento_atual) == 'v')
			{
				char t_rolamento = pegar_tipo(rolamento_atual);

				if (t_rolamento == 'c')
				{
					total_cilindrico++;
					tempo_total_cilindrico += tempo_atual - pegar_tempo_inicio(rolamento_atual);
				}
				else if (t_rolamento == 'k')
				{
					total_conico++;
					tempo_total_conico += tempo_atual - pegar_tempo_inicio(rolamento_atual);
				}
				else if (t_rolamento == 'a')
				{
					total_esferico_aco++;
					tempo_total_esferico_aco += tempo_atual - pegar_tempo_inicio(rolamento_atual);
				}
				else if (t_rolamento == 't')
				{
					total_esferico_titanio++;
					tempo_total_esferico_titanio += tempo_atual - pegar_tempo_inicio(rolamento_atual);
				}

				free(rolamento_atual);
			}
			else if (atual_maquina(rolamento_atual) == 'm')
			{
					if((!ocupada(mandril)) && (tamanho(fila_mandril) == 0))
					{
						tempoProcessamento = pegar_tempo_mandril(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(mandril, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(mandril));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_mandril, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}
			else
			{
					if((!ocupada(fresa)) && (tamanho(fila_fresa) == 0))
					{
						tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_fresa, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}

			if (tamanho(fila_torno) > 0)
			{
				rolamento_atual = (ROL*) obter(fila_torno);
				tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
				inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
				inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
			}

		} else if (tempo_atual == *tempo_livre(torno2)){

			remover_ordenada(lista_ordenada, 0);
			rolamento_atual = libera_maquina(torno2);
			prox_maquina = proxima_maquina(rolamento_atual);

			if (atual_maquina(rolamento_atual) == 'v')
			{
				char t_rolamento = pegar_tipo(rolamento_atual);

				if (t_rolamento == 'c')
				{
					total_cilindrico++;
				}
				else if (t_rolamento == 'k')
				{
					total_conico++;
				}
				else if (t_rolamento == 'a')
				{
					total_esferico_aco++;
				}
				else if (t_rolamento == 't')
				{
					total_esferico_titanio++;
				}

				free(rolamento_atual);
			}
			else if (atual_maquina(rolamento_atual) == 'm')
			{
					if((!ocupada(mandril)) && (tamanho(fila_mandril) == 0))
					{
						tempoProcessamento = pegar_tempo_mandril(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(mandril, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(mandril));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_mandril, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}
			else
			{
					if((!ocupada(fresa)) && (tamanho(fila_fresa) == 0))
					{
						tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_fresa, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}

			if (tamanho(fila_torno) > 0)
			{
				rolamento_atual = (ROL*) obter(fila_torno);
				tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
				inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
				inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno2));
			}

		} else if (tempo_atual == *tempo_livre(fresa)){
			remover_ordenada(lista_ordenada, 0);
			rolamento_atual = libera_maquina(fresa);
			prox_maquina = proxima_maquina(rolamento_atual);

			if (atual_maquina(rolamento_atual) == 'm')
			{
					if((!ocupada(mandril)) && (tamanho(fila_mandril) == 0))
					{
						tempoProcessamento = pegar_tempo_mandril(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(mandril, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(mandril));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_mandril, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}
			else
			{
					if((!ocupada(torno1)) && (tamanho(fila_torno) == 0))
					{
						tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
					}
					else if ((!ocupada(torno2)) && (tamanho(fila_torno) == 0))
					{
						tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno2));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}

			if (tamanho(fila_fresa) > 0)
			{
				rolamento_atual = (ROL*) obter(fila_fresa);
				tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
				inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
				inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
			}

		} else{
			remover_ordenada(lista_ordenada, 0);
			rolamento_atual = libera_maquina(mandril);
			prox_maquina = proxima_maquina(rolamento_atual);

			if (atual_maquina(rolamento_atual) == 'v')//Teste prox_maq == 'v'
			{
				char t_rolamento = pegar_tipo(rolamento_atual);

				if (t_rolamento == 'c')
				{
					total_cilindrico++;
				}
				else if (t_rolamento == 'k')
				{
					total_conico++;
				}
				else if (t_rolamento == 'a')
				{
					total_esferico_aco++;
				}
				else if (t_rolamento == 't')
				{
					total_esferico_titanio++;
				}

				free(rolamento_atual);
			}
			else if (atual_maquina(rolamento_atual) == 'f')
			{
					if((!ocupada(fresa)) && (tamanho(fila_fresa) == 0))
					{
						tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_fresa, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}
			else
			{
					if((!ocupada(torno1)) && (tamanho(fila_torno) == 0))
					{
						tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(torno1, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno1));
					}
					else if ((!ocupada(torno2)) && (tamanho(fila_torno) == 0))
					{
						tempoProcessamento = pegar_tempo_torno(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
						inserir_maquina(torno2, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
						inserir_ordenada(lista_ordenada, (void*)tempo_livre(torno2));
					}
					else
					{
						prioridade = pegar_prioridade(rolamento_atual); //Define qual a prioridade do rolamento
						inserir_prioridade(fila_torno, (void*)rolamento_atual, prioridade); //Insere na fila da máquina onde inicia
					}
			}

			if (tamanho(fila_fresa) > 0)
			{
				rolamento_atual = (ROL*) obter(fila_fresa);
				tempoProcessamento = pegar_tempo_fresa(rolamento_atual); //Pega o tempo médio que aquele rolamento deve ficar no torno
				inserir_maquina(fresa, rolamento_atual, tempo_atual, tempoProcessamento); //Insere na maquina especificada
				inserir_ordenada(lista_ordenada, (void*)tempo_livre(fresa));
			}
		}
	}

	printf("Total Cilindrico: %d -- Tempo medio: %2f\n", total_cilindrico, (tempo_total_cilindrico/total_cilindrico));
	printf("Total Conico: %d -- Tempo medio: %2f\n", total_conico, (tempo_total_conico/total_conico));
	printf("Total Aco: %d -- Tempo medio: %2f\n", total_esferico_aco, (tempo_total_esferico_aco/total_esferico_aco));
	printf("Total Titanico: %d -- Tempo medio: %2f\n", total_esferico_titanio, (tempo_total_esferico_titanio/total_esferico_titanio));



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

void imprime_lista_ordenada(lista *lst){
	int tamanho_lst = tamanho_ordenada(lst);
	int z;
	for(z= 0; z < tamanho_lst; z++){
		double x = *(double*)obter_ordenada(lst, z);
		printf("%lf ", x);
	}
	printf("\n");
}
