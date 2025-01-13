
// Árvore binária de busca - Implementações

#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
	struct _no *esq; // filho a esquerda
	int chave;
	struct _no *dir; // filho a direita
} noArv; // nó da arvore bináriq

void init(noArv **raiz){ *raiz = NULL; }
noArv* busca(noArv *raiz, int valor);

int main(void){

	
	

	return 0;
}

noArv* busca(noArv *raiz, int valor){
	if(raiz == NULL) return NULL;
	
	if(raiz->chave == valor)
		return raiz;
	
	if(valor < raiz->chave)
		return busca(raiz->esq);
	else
		return busca(raiz->dir);
}
