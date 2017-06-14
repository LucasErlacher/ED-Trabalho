#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filaPrioridade.h"
#include "nodoPrioridade.h"

void imprimeFila(fila_prioridade *varFila){
	nodo_prioridade *n = varFila->first;
	
	int i;
	for(i = 0; i < varFila->tam; i++){
		printf("%d %d \n", (int)get_ElemNodo(n), n->prioridade);
		n = n->next;
	}
	
	return;
}


int main(int argc, char** argv){
	srand(time(NULL));
	
	fila_prioridade *varFila = criar_fila_prioridade();
	
	int x;
	for (x = 10; x > 0; x--)
	{
		int prioridade = (rand()%10) + 1;
		inserir_prioridade(varFila, x, prioridade);
	}
	
	printf("Imprimindo FILA 1:\n");
	
	imprimeFila(varFila);
	
	int s = (int)peek(varFila);
	
	pop_Elem(varFila);
	
	printf("Imprimindo FILA 2:\n");
	
	imprimeFila(varFila);
	
	printf("\n\npeek %d", s);
	
	clear_Fila(varFila);
	
	free(varFila);
	return 0;
}
