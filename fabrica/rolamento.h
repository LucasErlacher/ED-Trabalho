#ifndef __rolamento__
#define __rolamento__

typedef struct rolamento ROL;

struct rolamento
{
	char tipo;
	char ordemMaq[7];

	double tempo_torno;
	double tempo_mandril;
	double tempo_fresa;
	double tempo_inicio;

	int maquina_atual;
	int prioridade;
};

void criar_cilindrico(ROL* rolamento);
void criar_conico(ROL* rolamento);
void criar_esferico_aco(ROL* rolamento);
void criar_esferico_titanio(ROL* rolamento);

ROL* criar_rolamento(char tipo_rolamento, double tempo_atual);

char atual_maquina(ROL *rolamento);
char proxima_maquina(ROL *rolamento);

double pegar_tempo_torno(ROL *rolamento);
double pegar_tempo_mandril(ROL *rolamento);
double pegar_tempo_fresa(ROL *rolamento);
double pegar_tempo_inicio(ROL *rolamento);

char pegar_tipo(ROL* rolamento);
int pegar_prioridade(ROL* rolamento);

#endif
