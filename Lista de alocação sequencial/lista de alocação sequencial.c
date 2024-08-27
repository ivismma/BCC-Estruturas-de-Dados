#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Listas de alocação sequencial

typedef struct{
	int *l;
	int tam;    // tamanho atual da lista
	int nelem;  // quantidade de elementos atual
} ListaSeq; // Lista sequencial

void init(ListaSeq *lista, int tamanho);          // inicia lista.
int busca(ListaSeq *lista, int valor);            // retorna indice da 1a ocorrencia do valor.
void insere(ListaSeq *lista, int valor, int pos); // insere valor na pos. como argumento.
void insereFim(ListaSeq *lista, int valor);       // insere no fim.
bool deleta(ListaSeq *lista, int valor);          // remove 1a ocorrencia do valor inserido.
void limpar(ListaSeq *lista);                     // esvazia a lista (atualiza atual).
void destroi(ListaSeq *lista);                    // limpa a lista.
void exibir(ListaSeq lista);                      // exibe a lista.

const int INT_SIZE = sizeof(int);

int main(void){
	ListaSeq lista;
	lista.l = NULL;
	init(&lista, 10);
	
	insereFim(&lista, 2);
	insereFim(&lista, 1);
	insereFim(&lista, 0);
	insereFim(&lista, 9);
	insere(&lista, -4, 1);
	exibir(lista);
	deleta(&lista, 1);
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

/*
	ao invés de realocar de tamanho + tamanho quando
	necessário, realoca o dobro do tamanho atual para
	melhorar complexidade de P.A para P.G.
	Ex.: (30+30+30+...) (P.A) | (30+60+120+...) (P.G)
*/

void insereFim(ListaSeq *lista, int valor){
	insere(lista, valor, lista->nelem);
}

void insere(ListaSeq *lista, int valor, int pos){
	if(pos > lista->nelem || pos < 0) 
		exit(10); // out of range...
	if(lista->nelem == lista->tam){ 
		lista->l = (int *) realloc(lista->l, (lista->tam*= 2));
		if(lista->l == NULL) exit(11); // falha aloc.
	}
	
	int *v = lista->l;
	if(pos == lista->nelem) // insere no fim..
		v[lista->nelem] = valor;
	else{
		int i;
		// joga todo mundo pra frente (caro)
		for(i = lista->nelem; i > pos; --i)
			v[i] = v[i-1];
		v[i] = valor;
	}
	++lista->nelem;
}

// retorna -1 se n encontrou.
int busca(ListaSeq *lista, int valor){
	int i = 0;
	while(i < lista->nelem){
		if(lista->l[i] == valor) return i;
		++i;
	}
	return -1;
}

/*
	Deleta e substitui no lugar do removido
	o atual últino da lista p/ evitar mover
	todos os elementos da direita p/ direita.
*/
bool deleta(ListaSeq *lista, int valor){
	int i = 0;
	while(i < lista->nelem){
		if(lista->l[i] == valor){
			lista->l[i] = lista->l[lista->nelem-1];
			--lista->nelem;
			return true;
		}
		++i;
	}
	return false; // não achou ou lista vazia.
}

void limpar(ListaSeq *lista){
	lista->nelem = 0;
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
