#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "filaPrioridade.h"
#include "nodoPrioridade.h"
/*
void imprimeFila(fila_prioridade *varFila){
	nodo_prioridade *n = varFila->first;
	
	do{
		printf("%d \n",(*(int*)get_ElemNodo(n)));
		if(n->next != NULL) n = n->next;
	}while(n->next != NULL);
	
	return;
}
*/

int main(int argc, char** argv){
	srand(time(NULL));
	
	fila_prioridade *varFila = criar_fila_prioridade();
	
	for (int x = 0; x < 10; x++)
	{
		int prioridade = (rand()%3) + 1;
		printf("%d\n",prioridade);
		inserir_prioridade(varFila,&x,prioridade);
		
	}
	
	//imprimeFila(varFila);
	
	clear_Fila(varFila);
	
	free(varFila);
	return 0;
}