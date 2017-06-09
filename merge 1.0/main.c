#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void print_lista(lista *list){
	int i;
	
	for(i = 0; i < get_size(list); i++){
		printf("%d ", get_index(list, i));
	}
	printf("\n");
}

int main(int argc,char **argv){
	lista* l;
	l = criar_lista();
	
	
	int i;
	for(i = 0; i < 30; i++){
		inserir(l, i);
	}
	
	print_lista(l);
	
	remover_start(l);
	
	print_lista(l);
	return 0;
}

