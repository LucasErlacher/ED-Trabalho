#include "nodo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void teste(){
	printf("Funcionou!");
}

int get_size(lista* llist){
	return llist->size;
}

void* get_index(lista* llist, int index)
{
	// if the list is 0 or if the index in larger than the size
	if (!llist->size || index >= llist->size) {
		return NULL;
	}
	
	// loop through the list until you get to the desired index
	nodo *current = llist->head; // index = 0
	int i;
	for (i = 0; i<index; i++) {
		current = current->next;
	}
		
	return current->data;
}

nodo* get_nodo_index(lista* llist, int index)
{
	// if the list is 0 or if the index in larger than the size
	if (!llist->size || index >= llist->size) {
		return NULL;
	}
	
	// loop through the list until you get to the desired index
	nodo *current = llist->head; // index = 0
	int i;
	for (i = 0; i<index; i++) {
		current = current->next;
	}
		
	return current;
}

void append_first(lista* llist, void* data)
{
	nodo *n = criar_nodo(data);
	
	// Se tamanho da lista for 0
	if (!llist->size) {
		// então o próximo e o anterior são o próprio nó
		n->next = n;
		n->prev = n;
	} else {
		nodo *head = llist->head;
		nodo *prev = head->prev;
		
		// Seta os novos nós dos nós vizinhos
		n->next = head;
		n->prev = head->prev;
		
		// Seta novos nós do novo nó
		head->prev = n;
		prev->next = n;
	}
	
	// Seta o novo nó como primeiro da lista
	llist->head = n;
	llist->size++;
}

void append(lista* llist, void* data)
{
	nodo *n = criar_nodo(data);
	
	// if the list size is 0
	if (!llist->size) {
		// set the next and prev to the new node
		n->next = n;
		n->prev = n;
	
		// since there are no other nodes this node will be the head
		llist->head = n;
	} else {
		nodo *head = llist->head;
		nodo *prev = head->prev;
		
		// insert to the back by setting next to the head
		n->next = head;
		n->prev = head->prev;
		
		// Update the next and prev pointers to the current node
		head->prev = n;
		prev->next = n;
	}
	
	llist->size++;
}

lista* criar_lista()
{
	lista *l;
	l = malloc(sizeof(lista));
	l->head = NULL;
	l->size = 0;
	l->append_first = append_first;
	l->append = append;
	l->get_size = get_size;
	l->get_index = get_index;
	l->append_index = append_index;
	return l;
}

void funcao_in_lista(lista* llist, funcao do_func)
{
  nodo *current = llist->head;
  int i;
  for (i = 0; i < llist->size; i++) {
    do_func(current->data);
    current = current->next;
  }
}

void funcao_in_index(lista* llist, int index, funcao do_func)
{
  nodo *current = llist->head;
  
  int i;
  for (i = 0; i <= index; i++) {
    current = current->next;
  }
  
  do_func(current->data);
}

void append_index(lista* llist, void* data, int index){
	if(index == 0) append_first(llist, data);
	else if(index >= llist->size) append(llist, data);
	else{
		nodo *novo = criar_nodo(data);
		nodo* cur = get_index(llist, index);
		
		// Fazer ligação dos próximos nodos 
		
	}
}
