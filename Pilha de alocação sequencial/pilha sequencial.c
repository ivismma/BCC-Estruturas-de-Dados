#include <stdio.h>
#include <stdlib.h>

// pilha de alocação sequencial

typedef struct{
	int *p;
	int tam; // tamanho
	int topo;
} PilhaSeq;

void init(PilhaSeq *pilha, int tamanho);
void push(PilhaSeq *pilha, int valor);
int pop(PilhaSeq *Pilha);

int main(void){
	
	PilhaSeq pilha = {NULL, 0, 0};
	init(&pilha, 5);
	
	push(&pilha, 3);
	push(&pilha, 4);
	push(&pilha, 5);
	push(&pilha, 6);
	push(&pilha, 7);
	push(&pilha, 8);
	printf("- %d -", pop(&pilha));
	
	return 0;
}

void init(PilhaSeq *pilha, int tamanho){
	pilha->p = (int *) malloc(sizeof(int) * tamanho);
	if(pilha->p == NULL) exit(1); // falha aloc.
	
	pilha->tam = tamanho;
	pilha->topo = -1; // -1
}

void push(PilhaSeq *pilha, int valor){
	if(pilha->topo == pilha->tam-1)
		pilha->p = (int *) realloc(pilha->p, pilha->tam *= 2); // dobra o tamanho.
	if(pilha->p == NULL) exit(2); // falha realoc.
	
	pilha->p[++pilha->topo] = valor;	
}

int pop(PilhaSeq *pilha){
	int registro;
	if(pilha->topo == -1)
		// underflow
		exit(1);
	else
		return pilha->p[pilha->topo--];
}
