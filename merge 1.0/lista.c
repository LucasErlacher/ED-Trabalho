#include "nodo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

/*
	Faz a inicialização da LISTA para os valores DEFAULT.
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
	
	// Percorre a lista até pegar o index desejado
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
	
	// Percorre a lista até pegar o index desejado
	nodo *current = list->start; // index = 0
	int i;
	for (i = 0; i<index; i++) {
		current = current->next;
	}
		
	return current;
}

/*
	Insere um elemento qualquer no início da LISTA.
*/
void inserir_start(lista* list, void* elem){
	nodo *n = criar_nodo(elem);

	// Se tamanho da lista for 0
	if (!list->size) {
		// então o ultimo elemento da lista é n
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
		// Já que não há outros nós, esse será o inicial;
		list->start = n;
	} 
	else {
		nodo *end = list->end; // Pega ultimo nodo
		end->next = n; // Seta proximo nodo de END como N
		n->prev = end; // Seta anterior de N como END
	}

	list->end = n; // Seta N como nó final da lista
	list->size++; // Incrementa tamanho
}

/*
	Insere elemento no index enviado como parametro
*/
void inserir_index(lista* list, void* elem, int index){
	if(index == 0) inserir_start(list, elem); // Caso index seja 0, usa a função insere_start
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
	Remove primeiro elemento da lista
*/
void remover_start(lista* list){
	nodo *start = list->start; // Pega primeiro elemento
	
	list->start = start->next; // Seta Elemento seguinte como primeiro elemento
	free(start);

	(list->start)->prev = NULL; // Seta anterior do novo primeiro elemento como NULL
	(list->size)--;
	return;
}

/*
	Remove o elemento no index enviado como parametro
*/
void remover_index(lista* list, int index){
	
	if (index >= get_size(list)) return;
	else if (index == 0) remover_start(list);
	else if (index == get_size(list)-1) remover_final(list);
	else
	{
		nodo *n = _get_nodo_index(list,index); //Pega o nodo do index
		
		(n->prev)->next = n->next; //Seta o próximo nodo do elemento anterior ao Index
		(n->next)->prev = n->prev; //Seta o nodo anterior do próximo elemento do Index.
		
		free(n);
		
		(list->size)--;
		
	}
	return;
}

/*
	Destrói a lista inteira
*/
void destruir_lista(lista* list){
	nodo *current = list->start;
	
	for(int i = 0; i < get_size(list); i++){
		if (current->next == NULL){
			list->end = list->start = NULL; //Seta os valores do início e fim para NULL
			free(current);
		}
		else{
			list->start = current->next;
			free(current);
			current = list->start;
		}
	}
	
	list->size = 0;
	
	return;
}