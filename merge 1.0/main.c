#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "filaPrioridade.h"
#include "maquina.h"
#include "rolamento.h"

int main(int argc, char *argv[]) {
	Maquina * fresa = criar_maquina();
	Maquina * mandril = criar_maquina();
	Maquina * torno1 = criar_maquina();
	Maquina * torno2 = criar_maquina();
	
	return 0;
}

/*
void print_lista(lista *list){
	int i;
	
	for(i = 0; i < get_size(list); i++){
		printf("%d ", get_index(list, i));
	}
	printf("-\n");
}

int main(int argc,char **argv){
	lista* l;
	l = criar_lista();
	
	int *i = (int *)malloc(sizeof(int));
	for(*i = 0; *i < 10; *i = *i + 1){
		inserir(l, *i);
		
	}
	
	print_lista(l);
	
	if(remover_index(l, 5)){
		print_lista(l);
	}
	
	destruir_lista(l);
	
	print_lista(l);
	
	printf("end");
	
	return 0;
}
*/
