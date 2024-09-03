#include <stdio.h>
#include <stdlib.h>

// fila sequencial impl. circular

typedef struct{
	int *f;
	int tam; // tamanho
	int inicio;
	int fim;
} FilaSeq;

void init(FilaSeq *fila, int tamanho);
void insere(FilaSeq *fila, int valor);
int libera(FilaSeq *fila);
void exibirFila(FilaSeq *fila);

int main(void){
	
	FilaSeq fila = {NULL, 0, 0, 0};
	
	init(&fila, 5);
	
	insere(&fila, 5);
	insere(&fila, 4);
	insere(&fila, 3);
	exibirFila(&fila);
	printf("liberou -> %d\n", libera(&fila));
	exibirFila(&fila);
	insere(&fila, 1);
	printf("inseriu -> 1\n");
	exibirFila(&fila);
	
	return 0;
}

void init(FilaSeq *fila, int tamanho){
	fila->f = (int *) malloc(sizeof(int) * tamanho);
	if(fila->f == NULL) exit(1); // falha aloc.
	
	fila->tam = tamanho;
	fila->inicio = fila->fim = -1;
}

void insere(FilaSeq *fila, int valor){
	if(fila->inicio == -1){
		fila->f[0] = valor;
		fila->inicio = 0;
		fila->fim = 1;
	}
	else{
		if(fila->inicio == fila->fim){ // realoca..
			// fila cheia.
			exit(2);
		}
		else{
			fila->f[fila->fim] = valor;
			fila->fim = (fila->fim+1)%fila->tam;
		}
	}
}

int libera(FilaSeq *fila){
	if(fila->inicio == -1)
		exit(2); // underflow
	
	int registro = fila->f[fila->inicio];
	
	fila->inicio = (fila->inicio+1)%fila->tam;
	if(fila->inicio == fila->fim)
		fila->inicio = fila->fim = -1;
		
	return registro;
}


void exibirFila(FilaSeq *fila){
	if(fila->inicio == -1){
		printf("Fila vazia.\n");
		return;
	}
	int i = fila->inicio;  // caso onde a fila está cheia.
	do{
		printf("%d ", fila->f[i]);
		i = (i+1)%fila->tam;
	} while(i != fila->fim);

	puts("");
}
