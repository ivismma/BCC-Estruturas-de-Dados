#include <stdio.h>

// Aula 02 - Selection Sort
// Complexidade O(n²)
// Diz-se a complexidade do algoritmo sempre o seu *pior* caso.

// não é possível aplicar flag "está ordenado" nesse
// algoritmo como no Bubble Sort porque pra cada 
// elemento i, ele se compara a todos os j restantes,
// sendo impossível saber se já está ordenado ou não.

void selectionSort(int *v, int tam);
void bubbleSort(int *v, int tam);
void exibir(int *v, int tam);

int main(void){

	int v[] = {1,6,0,2,4,7,8,3,1,10,5};
	int tam = sizeof(v)/sizeof(v[0]);
	
	exibir(v, tam);
	bubbleSort(v, tam);
	exibir(v, tam);
	
	
	return 0;
}

void selectionSort(int *v, int tam){
	for(int i = 0; i < tam; ++i){
		for(int j = i+1; j < tam; ++j){
			if(v[i] > v[j]){
				int aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
}

void exibir(int *v, int tam){
	for(int i = 0; i < tam; ++i)
		printf("%d ", v[i]);
	puts("");
}
