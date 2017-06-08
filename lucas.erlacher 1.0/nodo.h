typedef struct nodo nodo;

struct nodo {
	void* elem;
	nodo* prox;
	nodo* ant;
};

nodo* create_nodo(void* object);
nodo* next_nodo(nodo* current_nodo);
nodo* previous_nodo(nodo* current_nodo);
void* get_ElemNodo(nodo* n);