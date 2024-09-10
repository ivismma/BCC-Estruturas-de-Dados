#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node{
	int chave;
	struct node *prox;
} noPilha;

void push(noPilha **topo, int valor); // empilhar..
int pop(noPilha **topo, int *popped); // retorna false se a pilha está vazia
void exibirPilha(noPilha *topo);

int main(void){
	
	noPilha *pilha1 = NULL;
	int valor;
	
	push(&pilha1, 4);
	push(&pilha1, 1);
	push(&pilha1, 0);
	push(&pilha1, 15);
	exibirPilha(pilha1);
	
	pop(&pilha1, &valor);
	printf("Retirado topo (%d)...\n\n", valor);
	exibirPilha(pilha1);
	
	printf("\nRetirando 0, 1 e 4...\n");
	pop(&pilha1, NULL);
	pop(&pilha1, NULL);
	pop(&pilha1, NULL);
	exibirPilha(pilha1);

	return 0;
}

void push(noPilha **topo, int valor){
	noPilha *novo = (noPilha *) malloc(sizeof(noPilha));
	novo->chave = valor;
	
	if(*topo == NULL){
		novo->prox = NULL;
		*topo = novo;
	}
	else{
		novo->prox = *topo;
		*topo = novo;
	}
}



// popped é trocado via referência p/ saber quem foi retirado.
// Retorna...
// 0 se pilha está vazia;
// 1 se desempilhou e alterou variável passada via ref para o valor retirado;
// 2 se desempilhou mas não foi passado variável para armazenar o retirado.
int pop(noPilha **topo, int *popped){
	if(*topo == NULL) return 0;

	bool passouRef = (popped != NULL);
	if(passouRef) // diz quem foi desempilhado apenas se passou endereço.
		*popped = (*topo)->chave;
	
	noPilha *aux = (*topo)->prox;
	free(*topo);
	*topo = aux;
	
	return (passouRef)? 1 : 2;
}







void exibirPilha(noPilha *topo){
	if(topo == NULL){
		printf("Pilha vazia.\n");
		return;
	}
	
	printf("TOPO\n\n");
	noPilha *atual = topo;
	for(;atual != NULL; atual = atual->prox)
		printf("%d\n", atual->chave);
	
}
