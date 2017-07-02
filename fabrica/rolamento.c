#include "rolamento.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criar_cilindrico(ROL* rolamento){
	rolamento->tipo = 'c';
	strcpy(rolamento->ordemMaq,"tftm\0");
	rolamento->tempo_torno = 0.8;
	rolamento->tempo_fresa = 0.5;
	rolamento->tempo_mandril = 1.2;
	rolamento->prioridade = 1;
	rolamento->maquina_atual = 0;
	return;
}

void criar_conico(ROL* rolamento){
	rolamento->tipo = 'k';
	strcpy(rolamento->ordemMaq,"tmt\0");
	rolamento->tempo_torno = 1.8;
	rolamento->tempo_mandril = 2.1;
	rolamento->prioridade = 2;
	rolamento->maquina_atual = 0;
	return;
}

void criar_esferico_aco(ROL* rolamento){
	rolamento->tipo = 'a';
	strcpy(rolamento->ordemMaq,"fmt\0");
	rolamento->tempo_torno = 1.0;
	rolamento->tempo_fresa = 0.5;
	rolamento->tempo_mandril = 1.4;
	rolamento->prioridade = 3;
	rolamento->maquina_atual = 0;
	return;
}

void criar_esferico_titanio(ROL* rolamento){
	rolamento->tipo = 't';
	strcpy(rolamento->ordemMaq,"fmtft\0");
	rolamento->tempo_torno = 1.6;
	rolamento->tempo_fresa = 0.6;
	rolamento->tempo_mandril = 1.5;
	rolamento->prioridade = 3;
	rolamento->maquina_atual = 0;
	return;
}

ROL* criar_rolamento(char tipo_rolamento){
	ROL *rolamento = (ROL*) malloc(sizeof(ROL));

	switch(tipo_rolamento)
	{
		case 'c':
			criar_cilindrico(rolamento);
			break;
		case 'k':
			criar_conico(rolamento);
			break;
		case 'a':
			criar_esferico_aco(rolamento);
			break;
		case 't':
			criar_esferico_titanio(rolamento);
			break;
		default:
			break;
	}

	return rolamento;
}

char atual_maquina(ROL *rolamento){
	return (rolamento->ordemMaq)[rolamento->maquina_atual];
}

char proxima_maquina(ROL *rolamento){
	int maquinaAtual = (rolamento->maquina_atual);
	printf("%d %c maquina atual\n", maquinaAtual, rolamento->tipo);
	(rolamento->maquina_atual)++;

    maquinaAtual = (rolamento->maquina_atual);

	char prox_maquina = (rolamento->ordemMaq)[maquinaAtual];
	return prox_maquina;
}

double pegar_tempo_torno(ROL *rolamento){return rolamento->tempo_torno;}

double pegar_tempo_mandril(ROL *rolamento){return rolamento->tempo_mandril;}

double pegar_tempo_fresa(ROL *rolamento){return rolamento->tempo_fresa;}

char pegar_tipo(ROL* rolamento){return rolamento->tipo;}

int pegar_prioridade(ROL* rolamento){return rolamento->prioridade;}
