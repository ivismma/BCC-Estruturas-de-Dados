#include <stdio.h>
#include <stdlib.h>

// fila de aloca��o sequencial
// implementa��o circular


// indice -1 simboliza fila vazia.
typedef struct{
	int *f;
	int tam; // tamanho
	int inicio;
	int fim;
} FilaSeq;

void init(FilaSeq *fila, int tamanho); // inicia fila.
void insere(FilaSeq *fila, int valor); // insere na fila. (enqueue)
int libera(FilaSeq *fila);             // remove da fila (dequeue)
void overflow(FilaSeq *fila);          // realoca espa�o e copia a fila respeitando ordem.
void exibeFila(FilaSeq *fila);

int main(void){
	FilaSeq fila; 
	fila.f = NULL;
	
	init(&fila, 5);
	
	insere(&fila, 5);
	insere(&fila, 4);
	insere(&fila, 3);
	exibeFila(&fila);
	printf("liberou -> %d\n", libera(&fila));
	exibeFila(&fila);
	insere(&fila, 1);
	printf("inseriu -> 1\n");
	exibeFila(&fila);
	insere(&fila, 3);
	printf("inseriu -> 1\n");
	insere(&fila, 10);
	printf("inseriu -> 10\n");
	exibeFila(&fila);
	printf("liberou -> %d\n", libera(&fila));
	printf("liberou -> %d\n", libera(&fila));
	printf("liberou -> %d\n", libera(&fila));
	exibeFila(&fila);
	
	return 0;
}

void init(FilaSeq *fila, int tamanho){
	if(fila->f != NULL) exit(1); // fila ja iniciada.
	
	fila->f = (int *) malloc(sizeof(int) * tamanho);
	if(fila->f == NULL) exit(2); // falha aloc.
	
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
		if(fila->inicio == fila->fim){ // realoca e insere.
			overflow(fila);
			fila->f[fila->fim++] = valor;
		}
		else{ // h� espa�o na fila. insere...
			fila->f[fila->fim] = valor;
			fila->fim = (fila->fim+1)%fila->tam;
		}
	}
}

void overflow(FilaSeq *fila){
	int *v = fila->f; // vetor atual.
	                     // nova aloca��o c/ tamanho maior.
	int *vnovo = (int *) malloc(sizeof(int) * fila->tam*2);
	
	// copia fila atual na ordem circular.
	int j = 0;
	for(int i = fila->inicio; j < fila->tam; i=(i+1)%fila->tam, ++j){
		vnovo[j] = v[i];
	}
		
	free(v);           // libera bloco menor.
	fila->f = vnovo;   // atualiza nova aloca��o.
	fila->tam *= 2;    // atualiza novo tamanho.
	fila->inicio = 0;  // atualiza inicio
	fila->fim = j;     // atualiza novo fim.
}

int libera(FilaSeq *fila){
	if(fila->inicio == -1)
		exit(3); // underflow
	
	int registro = fila->f[fila->inicio];
	
	fila->inicio = (fila->inicio+1)%fila->tam;
	if(fila->inicio == fila->fim) // verifica se fila ficou vazia.
		fila->inicio = fila->fim = -1;
		
	return registro;
}

void exibeFila(FilaSeq *fila){
	if(fila->inicio == -1){
		printf("Fila vazia.\n");
		return;
	}
	int i = fila->inicio;  // caso onde a fila est� cheia.
	printf("Fila atual: ");
	do{
		printf("%d ", fila->f[i]);
		i = (i+1)%fila->tam;
	} while(i != fila->fim);
	
	puts("");
}
