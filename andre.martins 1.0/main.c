#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void print_elemento(void* elem){
	int x = (int*)elem;
	printf("%d\n", x);
}

int main(int argc,char **argv){
	lista* l;
	l = criar_lista();
	
	l->append(l, 10);
	l->append(l, 0);
	l->append(l, 0);
	l->append(l, 0);
	l->append_first(l, 33);
	l->append_index(l, 22, 1);
	
	funcao_in_lista(l, print_elemento);
	
	teste();
	
	return 0;
}
