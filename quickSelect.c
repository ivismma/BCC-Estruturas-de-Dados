#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/*  Selection Algorithm - método QuickSelect:
	Retorne o valor do elemento que
	ocuparia a pos. k do vetor como
	se v estivesse ordenado.
	(sem v precisar estar ordenado)
	
	Em outras palavras: O vetor estará 
	ordenado até a posição k inclusive.
*/

int quickSelect(int *v, int inicio, int fim, int k);
int particiona(int *v, int inicio, int fim);


int main(void){
	srand(time(NULL));
	int v[] = {8,1,3,7,9,5,3,9,5,10};
	int tam = sizeof(v)/sizeof(v[0]);
	
	int sel = quickSelect(v, 0, tam, 3);
	
	for(int i = 0; i < tam; ++i)
		printf("%d ", v[i]);
	
	printf("\n%d", sel);
	
	return 0;
}

int quickSelect(int *v, int inicio, int fim, int k){
	if(fim-inicio == 1){
		if(k != inicio)
			exit(1); // Erro - o algoritmo está errado.
		else 
			return v[k];
	}
	
	int pos = particiona(v, inicio, fim);
	if(pos == k){
		return v[k];
	}
	else{
		if(k < pos)
			return quickSelect(v, inicio, pos, k);
		else
			return quickSelect(v, pos+1, fim, k);
	}
}


int particiona(int *v, int inicio, int fim){
	int p = inicio + rand()%(fim-inicio);
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
