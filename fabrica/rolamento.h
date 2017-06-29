#ifndef __rolamento__
#define __rolamento__

typedef struct rolamento ROL;

struct rolamento
{
	char tipo;
	char ordemMaq[6];
	float tempo_torno;
	float tempo_mandril;
	float tempo_fresa;
	float tempo_inicio;
	int prioridade;
};

void criar_cilindrico(ROL* rolamento);
void criar_conico(ROL* rolamento);
void criar_esferico_aco(ROL* rolamento);
void criar_esferico_titanio(ROL* rolamento);

ROL* criar_rolamento(char tipo_rolamento);


char pegar_tipo(ROL* rolamento);
int pegar_prioridade(ROL* rolamento);

#endif