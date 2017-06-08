#ifndef __default__
#define __default__

#include <stdio.h>
#include <stdlib.h>

#endif

#ifndef __bibNODO__
#define __bibNODO__

#include "nodo.h"

#endif

#ifndef __bibLISTA__
#define __bibLISTA__

#include "lista.h"

#endif

lista* inic_listNull(){
	/*
	Faz a inicialização da LISTA para os valores DEFAULT.
	*/
	lista* l = malloc(sizeof(lista));
	l->tam = 0;
	l->ini = NULL;
	l->fin = NULL;
	return l;
}

int get_lenList(lista *lst){
	/*Retorna o tamanho da LISTA*/
	return (lst->tam);
}

void _insertStart(nodo* obj, lista* list){
	/*
	Esta função insere o NODO no início da LISTA.
	*/
	obj->prox = list->ini;
	(list->ini)->ant = obj;
	list->ini = obj;
	(list->tam)++;
	return;
}

void _insertFinal(nodo* obj, lista* list){
	/*
	Esta função insere o NODO ao final da LISTA.
	*/
	(list->fin)->prox = obj;
	obj->ant = list->fin;
	list->fin = obj;
	(list->tam)++;
	return;
}

void _startList(nodo* obj, lista* list){
	/*
	Caso a lista esteja vazia esta função define o primeiro elemento.
	*/
	list->ini = obj;
	list->fin = obj;
	(list->tam)++;
	return;
}

nodo* get_Object(lista* list,int pos){
	/*
	Função criada recebe LISTA e POSIÇÃO DESEJADA p/
	retornar um PONTEIRO P/ NODO.
	*/
	nodo* temp = list->ini;
	
	if ((pos < get_lenList(list)) && (pos >= 0)){
		for(int x = 0; x < pos; x++){
			temp = temp->prox;
		}
	} else{
		temp = NULL;
	}
	
	
	return temp;
}

void _removeFinal(lista* list){
	list->fin = (list->fin)->ant;
	free((list->fin)->prox);
	(list->fin)->prox = NULL;
	return;
}

void _removeStart(lista* list){
	list->ini = (list->ini)->prox;
	free((list->ini)->ant);
	(list->ini)->ant = NULL;
	return;
}

void removeObject(lista* list,int pos){
	int tamanho_lista = get_lenList(list);
	
	if (tamanho_lista == 1){
		free(list->ini);
		list->ini = NULL;
		list->fin = NULL;
	} 
	else{
		if((pos == -1) || (pos == (tamanho_lista - 1))){
			_removeFinal(list);
		}
		if(pos == 0){
			_removeStart(list);
		}
		else{
			nodo *temp = get_Object(list,pos);
			(temp->prox)->ant = temp->ant;
			(temp->ant)->prox = temp->prox;
			free(temp);
		}
	}
	
	(list->tam)--;
	return;
}
	


void insertElem(nodo* obj, lista* list, int pos){
	/*
	Esta função recebe objeto do tipo NODO - lista - posição p/ insertion.
	
	- Se a lista estiver vazia, o elemento é criado na primeira posição.
	
	- Se (TAM da Lista > 0) então: 
	
		Se (POS == -1) então:
			Insere Final da Lista.
		Caso Se (POS == 0) então:
			Insere Início da Lista
		Caso contrário:
			Insere na posição indicada desde que seja menor que o TAM da Lista.
	*/
	int tamList = list->tam;
	
	if (tamList == 0){
		_startList(obj,list);
	}
	else{
		if (pos == -1){
			_insertFinal(obj,list);
		}
		if (pos == 0){
			_insertStart(obj,list);
		}
		else{
			if((pos < tamList) && (pos > 0)){
				nodo* aux = get_Object(list,pos);
				obj->prox = aux;
				obj->ant = aux->ant;
				(aux->ant)->prox = obj;
				aux->ant = obj;
				(list->tam)++;
			}
		}
	}
	
	return;
}
