#include <stdio.h>
#include <stdlib.h>

// fila de alocação sequencial
// implementação circular


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
void overflow(FilaSeq *fila);          // realoca espaço e copia a fila respeitando ordem.
void exibeFila(FilaSeq *fila);

int main(void){
	FilaSeq fila; 
	fila.f = NULL;
	
	init(&fila, 5);
	
	// testes
	insere(&fila, 5);
	insere(&fila, 4);
	insere(&fila, 3);
	exibeFila(&fila);
	printf("liberou -> %d\n", libera(&fila));
	exibeFila(&fila);
	insere(&fila, 1);
	printf("inseriu -> 1\n");
	exibeFila(&fila);
	insere(&fila, 7);
	printf("inseriu -> 7\n");
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
	if(fila->f != NULL || tamanho <= 1) exit(1);
	// fila ja iniciada ou tamanho invalido.
	
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
		else{ // há espaço na fila. insere...
			fila->f[fila->fim] = valor;
			fila->fim = (fila->fim+1)%fila->tam;
		}
	}
}

void overflow(FilaSeq *fila){
	int *v = fila->f; // vetor atual.
	                     // nova alocação c/ tamanho maior.
	int *vnovo = (int *) malloc(sizeof(int) * fila->tam*2);
	if(vnovo == NULL) exit(3); // falha alocacao.
	
	// copia fila atual na ordem circular.
	int j = 0;
	for(int i = fila->inicio; j < fila->tam; i=(i+1)%fila->tam, ++j){
		vnovo[j] = v[i];
	}
		
	free(v);           // libera bloco menor.
	fila->f = vnovo;   // atualiza nova alocação.
	fila->tam *= 2;    // atualiza novo tamanho.
	fila->inicio = 0;  // atualiza inicio
	fila->fim = j;     // atualiza novo fim.
}

int libera(FilaSeq *fila){
	if(fila->inicio == -1)
		exit(4); // underflow
	
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
	int i = fila->inicio;
	printf("Fila atual: ");
	// 1a iteração obrigatória senão uma fila cheia nao é exibida pq inicio = fim
	do{
		printf("%d ", fila->f[i]);
		i = (i+1)%fila->tam;
	} while(i != fila->fim);
	
	puts("");
}
