#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Listas de alocação sequencial

typedef struct{
	int *l;
	int tam;    // tamanho atual da lista
	int nelem;  // quantidade de elementos atual
} ListaSeq; // Lista sequencial

void init(ListaSeq *lista, int tamanho); // inicia lista
int busca(ListaSeq *lista, int valor);   // retorna indice da 1a ocorrencia do valor
void insere(ListaSeq *lista, int valor); // insere valor
bool deleta(ListaSeq *lista, int valor); // remove 1a ocorrencia do valor
void limpar(ListaSeq *lista);  // esvazia a lista (atualiza atual).
void destroi(ListaSeq *lista); // limpa a lista
void exibir(ListaSeq lista);   // exibe a lista

const int INT_SIZE = sizeof(int);

int main(void){
	ListaSeq lista;
	lista.l = NULL;
	
	init(&lista, 10);
	insere(&lista, 2);
	insere(&lista, 1);
	insere(&lista, 0);
	insere(&lista, -4);
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
	ao invés de realocar de tamanho + tamanho,
	realoca o dobro do tamanho atual para
	melhorar complexidade de P.A para P.G.	
*/
void insere(ListaSeq *lista, int valor){
	if(lista->nelem == lista->tam){
		int *aux = realloc(lista->l, (lista->tam *= 2));
		if(aux == NULL){
			printf("falha na realocacao.\n");
			exit(3);
		}
		else lista->l = aux;
	}
	lista->l[lista->nelem++] = valor;
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

