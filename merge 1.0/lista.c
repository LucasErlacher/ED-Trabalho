#include "nodo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/*
	Faz a inicializa��o da LISTA para os valores DEFAULT.
*/
lista *criar_lista(){
	lista* l = malloc(sizeof(lista));
	l->start = NULL;
	l->end = NULL;
	l->size = 0;
	return l;
}

/*
	Retorna o tamanho da lista enviada
*/
int get_size(lista *list){
	return (list->size);
}

/*
	Retorna o elem do nodo equivalente ao index da lista
*/
void* get_index(lista* list, int index)
{
	// Caso lista vazia ou index > size
	if (!list->size || index >= list->size) {
		return NULL;
	}
	
	// Percorre a lista at� pegar o index desejado
	nodo *current = list->start; // index = 0
	int i;
	for (i = 0; i<index; i++) {
		current = current->next;
	}
		
	return current->elem;
}

/*
	Retorna o nodo equivalente ao index da lista
*/
nodo* _get_nodo_index(lista* list, int index)
{
	// Caso lista vazia ou index > size
	if (!list->size || index >= list->size) {
		return NULL;
	}
	
	// Percorre a lista at� pegar o index desejado
	nodo *current = list->start; // index = 0
	int i;
	for (i = 0; i<index; i++) {
		current = current->next;
	}
		
	return current;
}

/*
	Insere um elemento qualquer no in�cio da LISTA.
*/
void inserir_start(lista* list, void* elem){
	nodo *n = criar_nodo(elem);

	// Se tamanho da lista for 0
	if (!list->size) {
		// ent�o o ultimo elemento da lista � n
		list->end = n;
	} 
	else {
		nodo *start = list->start;	// Pega primeiro nodo
		start->prev = n; // Seta nodo anterior de start como N
		n->next = start; // Seta o nodo seguinte de N como start
	}
	
	list->start = n; // Seta primeiro elemento da lista como N
	list->size++; // Incrementa Lista
	return;
}

/*
	Insere o NODO ao final da LISTA.
*/
void inserir(lista* list, void* elem){
	nodo *n = criar_nodo(elem);

	// Se tamanho da lista for 0
	if (!list->size) {
		// J� que n�o h� outros n�s, esse ser� o inicial;
		list->start = n;
	} 
	else {
		nodo *end = list->end; // Pega ultimo nodo
		end->next = n; // Seta proximo nodo de END como N
		n->prev = end; // Seta anterior de N como END
	}

	list->end = n; // Seta N como n� final da lista
	list->size++; // Incrementa tamanho
}

/*
	Insere elemento no index enviado como paramentro
*/
void inserir_index(lista* list, void* elem, int index){
	if(index == 0) inserir_start(list, elem); // Caso index seja 0, usa a fun��o insere_start
	else if(index >= list->size) inserir(list, elem); // Caso o index seja maior ou igual ao tamanho da lista, insere no final
	else{
		nodo *novo = criar_nodo(elem);
		nodo* cur = _get_nodo_index(list, index);
		
		novo->next = cur; // 
		novo->prev = cur->prev;
		
		(novo->prev)->next = novo;
		
		cur->prev = novo;
		(list->size)++;		
	}
}

/*
	Remove ultimo elemento da lista
*/
void remover_final(lista* list){
	nodo *end = list->end;
	list->end = end->prev;
	//free(end->elem);
	free(end);
	(list->end)->next = NULL;
	(list->size)--;
	return;
}

/*
	Remove ultimo elemento da lista
*/
void remover_start(lista* list){
	nodo *start = list->start; // Pega primeiro elemento
	
	list->start = start->next; // Seta Elemento seguinte como primeiro elemento
	free(start);

	(list->start)->prev = NULL; // Seta anterior do novo primeiro elemento como NULL
	(list->size)--;
	return;
}