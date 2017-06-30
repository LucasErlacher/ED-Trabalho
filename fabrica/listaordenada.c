#include <stdlib.h>
#include "listaordenada.h"
#include "nodo.h"

lista* criar_lista_ordenada(int (*func)(void*,void*)){
	lista *lst = malloc(sizeof(lista));
	lst->func = func;
	lst->tam = 0;
	lst->ini = lst->fim = NULL;
	return lst;
}

void inserir_ordenada(lista *lst, void *elem){
	nodo *nTemp = create_nodo_ordenada(elem);

	if(lst->tam == 0)
	{
		lst->ini = lst->fim = nTemp;
	}
	else
	{
		nodo *current = lst->ini;

		while((current->prox != NULL) && (lst->func(elem, current->elem)))
		{
			current = current->prox;
		}
		
		if((current->ant == NULL) && !(lst->func(elem, current->elem))){
			nTemp->prox = current;
			current->ant = nTemp;
			lst->ini = nTemp;
		}
		else if (current->prox == NULL && (lst->func(elem, current->elem)))
		{
			nTemp->ant = current;
			current->prox = nTemp;
			lst->fim = nTemp;
		}
		else
		{
			(current->ant)->prox = nTemp;
			nTemp->ant = current->ant;
			
			current->ant = nTemp;
			nTemp->prox = current;
		}
	}
	
	(lst->tam)++;
	
	return;
}

void remover_ordenada(lista *lst, int pos){
	nodo *current = lst->ini;
	
	if (pos < lst->tam){
		
		for(int x = 0; x < pos; x++) current = current->prox;
		
		if((pos == 0) && (lst->tam == 1))
		{
			lst->ini = lst->fim = NULL;
		}
		else if(current->prox == NULL)
		{
			(current->ant)->prox = NULL;
			lst->fim = current->ant;	
		}
		else if(current->ant == NULL)
		{
			(current->prox)->ant = NULL;
			lst->ini = current->prox;
		}
		else
		{
			(current->ant)->prox = (current->prox);
			(current->prox)->ant = (current->ant);
		}
		
		free(current);
	
		(lst->tam)--;
	}
	return;
}

void* obter_ordenada(lista *lst, int pos){
	nodo *nTemp = lst->ini;
	void *elem;

	if (pos < lst->tam)
	{
		for (int i = 0; i < pos; ++i) nTemp = nTemp->prox;
		elem = get_ElemNodo_ordenada(nTemp);
	}

	return elem;
}

int tamanho_ordenada(lista *lst){return lst->tam;}

void destruir_lista_ordenada(lista *lst){
	nodo *nTemp = lst->ini;
	int tam = lst->tam;

	for (int i = 0; i < tam; ++i)
	{	
		lst->ini = nTemp->prox;

		free(nTemp);

		nTemp = lst->ini;
	}

	free(lst);

	return;
}