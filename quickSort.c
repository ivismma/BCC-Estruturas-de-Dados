#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*  Complexidade de algoritmos e quickSort:
	Dado um algoritmo A sensível à entradas e1, e2, ..., ek
	de tamanho n, que requerem tempo t1, t2, ..., tk, respec-
	tivamente, digo que a complexidade de A é:
	pior caso   = max(ti).
	melhor caso = min(ti)
	caso médio  = Somatório(ei)x(ti) de i=1 até k
*/

// T(n) = (1/n) somatorio (T(i)+T(n-i-1)+n) de i = 0 até n-1.

void quickSort(int *v, int inicio, int fim);
int particiona(int *v, int inicio, int fim);

int main(void){
	srand(time(NULL));
	
	int v[] = {7,8,1,2,5,6,0,10,2,4};
	int tam = sizeof(v)/sizeof(v[0]);
	
	quickSort(v, 0, tam);
	for(int i = 0; i < tam; ++i)
		printf("%d ", v[i]);
	
	return 0;
}

void quickSort(int *v, int inicio, int fim){
	if(fim-inicio > 1){
		int pos = particiona(v, inicio, fim);
		quickSort(v, inicio, pos);
		quickSort(v, pos+1, fim);
	}
}

int particiona(int *v, int inicio, int fim){
	int p = inicio + rand()%(fim-inicio); // gera pivot de inicio até fim-1.
	int pivot = v[p];
	v[p] = v[inicio];
	v[inicio] = pivot;
	int i = inicio+1;
	int j = fim-1;
	while(i < j){
		while(i < fim && v[i] <= pivot)
			++i;
		while(j > inicio && v[j] >= pivot)
			--j;
		if(i < j){
			int aux = v[i];
			v[i] = v[j];
			v[j] = aux;
		}
	}
	v[inicio] = v[j];
	v[j] = pivot;
	
	return j;
}
