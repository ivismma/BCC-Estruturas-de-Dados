/* Trabalho 1 - Estruturas de Dados

	Implemente o algoritmo Merge Sort e um algoritmo de
	ordenação de sua preferência, que tenha complexidade
	O(n²). A main(...) deve ter os seguintes argumentos:
	
	-m     -> roda merge sort (caso não insira essa flag
	roda o algoritmo escolhido).
	-n NUM -> define tamanho do vetor e cria randomizado.
	
	O programa deverá medir o tempo de execução do algoritmo
	e exibir na tela ao fim da execução.
*/

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
const int INT_SIZE = sizeof(int);

#define INICIA_CRONO clock_gettime(CLOCK_MONOTONIC, &t1);
#define PARA_CRONO clock_gettime(CLOCK_MONOTONIC, &t2);

void randomizaVet(int *v, int tam);
void mergeSort(int *v, int inicio, int fim);
void merge(int *v, int inicio, int meio, int fim);
void bubbleSort(int *v, int tam);
double tempoDecorrido(struct timespec t1, struct timespec t2);
void exibir(int *v, int tam);

// Exemplos de execução: "trabalho 1" -m -n 10
//                       "trabalho 1" -m
//                       "trabalho 1" -n 10
//                       "trabalho 1"

int main(int argc, char *argv[]){
	
	int ordenacao = 0; // 0 = bubble | 1 = merge.
	bool flagn = false; // flag p/ saber se n foi inserido como arg.
	int n = -1; // -1 significa que não foi lido ainda.
	int *v;
	
	// leitura e avaliacao dos argumentos da main()
	for(int i = 1; i < argc; ++i){
		if(strcmp("-m", argv[i]) == 0)
			ordenacao = 1;
		else if(strcmp("-n", argv[i]) == 0)
			flagn = true;
		else{                 
			bool valido = true;
			for(int j = 0; argv[i][j] != '\0'; ++j)
				if(argv[i][j] < '0' || argv[i][j] > '9'){
					valido = false;
					break;
				} // verifica se é o número, se for, guarda.
			if(valido){
				if((n = atoi(argv[i])) <= 0){
					printf("tamanho do vetor invalido.\n");
					exit(1);
				}
			}
		}
	}
	if(flagn){ // flag -n: criar vetor tamanho n do argumento e randomizar.
		if(n == -1){
			printf("flag -n encontrada, porem nao foi inserido o tamanho do vetor.\n");
			exit(2);
		}
		v = (int *) malloc(n * INT_SIZE);
		randomizaVet(v, n);
	}
	else{     // ausencia da flag -n: inserir do teclado valores do vetor até ENTER.
		int alocado = 30; // pré-alocacao de 30 numeros.
		v = (int *) malloc(30 * INT_SIZE);
		if(v == NULL) exit(3);
		
		printf("Insira numeros de ate 9 digitos (ENTER para parar):\n");
		for(n = 0; ; ++n){ // leitura até o ENTER
			char str[10];
			if(n >= alocado){
				int *aux = realloc(v, (alocado = alocado+30));
				if(aux != NULL) v = aux;
				else exit(3); // falha realoacao
			} 
			fflush(stdin);
			fgets(str, 10, stdin);
			if(str[0] != '\n') v[n] = atoi(str);
			else break;
		}
	}
	
	struct timespec t1, t2;
	if(ordenacao == 0){
		printf("BUBBLE SORT\n");
		INICIA_CRONO;
		bubbleSort(v, n);
	}
	else{
		printf("MERGE SORT\n");
		INICIA_CRONO;
		mergeSort(v, 0, n);
	} 
	PARA_CRONO;
	printf("#topo de exec - %.10lf segundos\n", tempoDecorrido(t1, t2));
	exibir(v, n);
	
	free(v);
	return 0;
}

void mergeSort(int *v, int inicio, int fim){
	if(fim - inicio > 1){
		int meio = (inicio+fim)/2;
		mergeSort(v, inicio, meio);
		mergeSort(v, meio, fim);
		merge(v, inicio, meio, fim);
	}
	
}

void merge(int *v, int inicio, int meio, int fim){
	int i = inicio;
	int j = meio;
	int n = fim - inicio;
	int *vaux = (int*) malloc(n*INT_SIZE);
	if(vaux == NULL) exit(2); // falha alocacao.
	
	int pos = 0;
	while(i < meio && j < fim){
		if(v[i] <= v[j]){
			vaux[pos] = v[i];
			++i;
			++pos;
		}
		else{
			vaux[pos] = v[j];
			++j;
			++pos;
		}
	}
	while(i < meio){
		vaux[pos] = v[i];
		++i;
		++pos;
	}
	
	for(int i = 0; i < pos; ++i)
		v[inicio+i] = vaux[i];
	
	free(vaux);
}

void bubbleSort(int *v, int tam){
	int fim = tam-1;
	bool ordenado;
	do{
		ordenado = true;
		for(int i = 0; i < fim; ++i){
			if(v[i] > v[i+1]){
				int aux = v[i];
				v[i] = v[i+1];
				v[i+1] = aux;
				ordenado = false;
			}
		}
		--fim;
	} while(!ordenado);
}

void exibir(int *v, int tam){
	for(int i = 0; i < tam; ++i) printf("%d\n", v[i]);
}

void randomizaVet(int *v, int tam){
	for(int i = 0; i < tam; ++i)
		v[i] = rand()%50 + 1; // gera de 1 a 50.
}

double tempoDecorrido(struct timespec t1, struct timespec t2){
	return (t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1e9;
}
