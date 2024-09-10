#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Lista encadeada ordenada - sem elemento repetidos.

typedef struct node{
	int chave;
	struct node *prox;
} noLista;

noLista* busca(noLista *topo, int valor); // retorna ponteiro pro nó do elemento buscado (NULL se ñ existe).
bool _remove(noLista **topo, int valor);  // remove elemento encontado, retorna false se não existe.
bool insere(noLista **topo, int valor);   // retorna false se já possui na lista.
void exibirLista(noLista *topo);

int main(void){

	noLista *lista1 = NULL;
	
	insere(&lista1, 25);
	insere(&lista1, 3);
	insere(&lista1, 1);
	insere(&lista1, 7);
	insere(&lista1, 19);
	exibirLista(lista1);
	
	printf("\nRemocao de elem. 7...\n\n");
	_remove(&lista1, 7);
	exibirLista(lista1);
	
	printf("\nInsercao de elem. -2...\n\n");
	insere(&lista1, -2);
	exibirLista(lista1);
	
	printf("\nBusca de elem. 19 na lista: ");
	if(busca(lista1, 19) != NULL) 
		printf("Encontrado.\n");
	else 
		printf("Nao encontrado.\n");
	
	printf("Busca de elem. 4 na lista: ");
	if(busca(lista1, 4) != NULL) 
		printf("Encontrado.\n");
	else 
		printf("Nao encontrado.\n");;
	
	return 0;
}

bool insere(noLista **topo, int valor){
	noLista *atual = *topo;
	noLista *novo = (noLista *) malloc(sizeof(noLista));
	if(novo == NULL) exit(1); // falha alocacao
	novo->chave = valor;
	novo->prox = NULL;
	
	if(*topo == NULL) // lista vazia
		*topo = novo;
	else if(atual->chave > valor){ // 1º elem. é maior que valor inserido
		novo->prox = atual;
		*topo = novo;
	}
	else{  // busca p/ inserçao ordenada
		for(;atual->prox != NULL; atual = atual->prox){
			int chaveprox = atual->prox->chave;
			if(chaveprox > valor) 
				break; // inserir antes do próximo.
			else if(chaveprox == valor) 
				return false; // já existe na lista.
		}
		noLista *aux = atual->prox;
		atual->prox = novo;
		novo->prox = aux;
	}
	return true;
}

bool _remove(noLista **topo, int valor){
	if(*topo == NULL) return false;
	if((*topo)->chave == valor){
		noLista *aux = (*topo)->prox;
		free(*topo);
		*topo = aux;
		return true;
	}
	
	noLista *atual = *topo;
	for(;atual->prox != NULL; atual = atual->prox){
		if(atual->prox->chave == valor){
			noLista *aux = atual->prox->prox;
			free(atual->prox);
			atual->prox = aux;
			break;
		}
		else if(atual->prox->chave > valor) 
			return false; // não consta na lista.
	}
	return true;
}

noLista* busca(noLista *topo, int valor){
	noLista *atual = topo;
	while(atual != NULL && atual->chave != valor){
		if(atual->chave > valor) return NULL;
		atual = atual->prox;
	}
	return atual; // retorna nó da busca.
}











void exibirLista(noLista *topo){
	noLista *atual = topo;
	for(int i = 0; atual != NULL; ++i){
		printf("Node %d: %d\n", i, atual->chave);
		atual = atual->prox;
	}
}
