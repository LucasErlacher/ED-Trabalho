#include <stdio.h>
#include <stdlib.h>

#ifndef __bibNODO__
#define __bibNODO__

#include "nodo.h"

#endif

#ifndef __bibLISTA__
#define __bibLISTA__

#include "lista.h"

#endif

#ifndef __bibFILA__

#define __bibFILA__

#include "fila.h"

#endif


int main(int argc, char** argv){
	fila *vfila;
	vfila = inic_filaNULL();
	
	int vet[] = {1, 2, 3, 4, 5};
	
	for(int x = 0; x < 5; x++){
		nodo *n = create_nodo(vet+x);
		insert_Nodo(vfila, n);
	}	
	
	for(int x = 0; x < 5; x++){
		int *num = (int*)pop_Elem(vfila);
		printf("%d \n", *num);
	}
	
	return 0;
}