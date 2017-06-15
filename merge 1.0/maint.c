#include <stdio.h>
#include <stdlib.h>
#include "maquina.h"
#include "rolamento.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	Maquina * m = criar_maquina();
	
	printf("%f", m->time_left);
	
	return 0;
}
