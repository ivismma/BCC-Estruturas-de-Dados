#include <stdio.h>
#include <stdlib.h>

// Aula 02 - Merge Sort
// Complexidade O(n log n)

void mergeSort(int *v, int inicio, int fim);
void merge(int *v, int inicio, int meio, int fim); // O(n)
void exibir(int *v, int tam);

const int INT_SIZE = sizeof(int);

int main(void){

	int v[] = {1,6,0,2,4,7,8,3,1,10,5,0};
	int tam = sizeof(v)/sizeof(v[0]);
	
	exibir(v, tam);
	mergeSort(v, 0, tam);
	exibir(v, tam);
	
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
	int n = fim-inicio;
	int *vaux = (int*) malloc(n*INT_SIZE);
	if(vaux == NULL) exit(2);
	
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

/* Análise de complexidade

Relação de recorrência:
T(n) = 2T(n/2) + n
T(1) = 1        <-- Caso base.


T(n) = T(teto(n/2)) T(piso(n/2)) + n <-- este último n é a última 
checagem quando, quando não há mais um caso recursivo (verif do caso base)
...
...

quantas vezes k divide n até que se atinja o caso base?
n/2^k = 1 | n = 2^k | k = log2 n
Complexidade: O(n log n)
*/

void exibir(int *v, int tam){
	for(int i = 0; i < tam; ++i)
		printf("%d ", v[i]);
	puts("");
}
