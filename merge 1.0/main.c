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
	
	int *i = (int *)malloc(sizeof(int));
	for(*i = 0; *i < 10; *i = *i + 1){
		inserir(l, *i);
		
	}
	
	print_lista(l);
	
	if(remover_final(l)){
		print_lista(l);
	}
	
	if(remover_start(l)){
		print_lista(l);
	}
	
	return 0;
}

