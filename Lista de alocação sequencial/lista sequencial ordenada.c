#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Implementações p/ uma lista de aloc. sequencial ORDENADA.

typedef struct{
	int *l;
	int tam;    // tamanho atual da lista
	int nelem;  // quantidade de elementos atual
} ListaSeq; // Lista sequencial

void init(ListaSeq *lista, int tamanho);
int busca(ListaSeq *lista, int valor);
void insere(ListaSeq *lista, int valor);
bool deleta(ListaSeq *lista, int valor);
void destroi(ListaSeq *lista);
void exibir(ListaSeq lista);

const int INT_SIZE = sizeof(int);

int main(void){
	ListaSeq lista;
	lista.l = NULL;
	
	init(&lista, 10);
	insere(&lista, 1);
	insere(&lista, 7);
	insere(&lista, 2);
	insere(&lista, 4);
	insere(&lista, 8);
	deleta(&lista, 2);
	exibir(lista);
	destroi(&lista);
	
	return 0;
}

void init(ListaSeq *lista, int tamanho){
	if(lista->l != NULL){
		printf("lista ja inicializada.\n");
		exit(1);
	}
	lista->l = (int *) malloc(tamanho * INT_SIZE);
	if(lista->l == NULL){
		printf("falha na alocacao.\n");
		exit(2);
	}
	lista->tam = tamanho;
	lista->nelem = 0;
}

// retorna -1 se não encontrou.
int busca(ListaSeq *lista, int valor){
	int i;
	int *v = lista->l;
	for(int i = 0; v[i] <= valor; ++i)
		if(valor == v[i])
			return i;
	
	return -1;
}

void insere(ListaSeq *lista, int valor){
	if(lista->nelem == lista->tam){ 
		lista->l = (int *) realloc(lista->l, (lista->tam*= 2));
		if(lista->l == NULL) exit(11); // falha aloc.
	}
	int *v = lista->l;
	if(v[lista->nelem-1] < valor){
		v[lista->nelem] = valor;
	}
	else{
		int i = 0, j;
		while(v[i] <= valor) ++i;
		
		for(j = lista->nelem; j > i; --j)
			v[j] = v[j-1];
		v[j] = valor;
	}
	++lista->nelem;
}

bool deleta(ListaSeq *lista, int valor){
	int *v = lista->l;
	int i;
	for(i = 0; i < lista->nelem; ++i){
		if(v[i] == valor){
			for(int j = i; j < lista->nelem; ++j) 
				v[j] = v[j+1];
			--lista->nelem;
			return true;
		}
	}
	return false; // não encontrou.
}

void destroi(ListaSeq *lista){
	lista->nelem = 0;
	lista->tam = 0;
	free(lista->l);
    lista->l = NULL;
}

void exibir(ListaSeq lista){
	printf("[");
	for(int i = 0; i < lista.nelem-1; ++i)
		printf("%d ", lista.l[i]);
	printf("%d]\n", lista.l[lista.nelem-1]);
}
