
// Árvore binária - Percurso em árvores

#include <stdio.h>
#include <stdlib.h>

#define ALT(ptraiz) (ptraiz == NULL)? 0 : ptraiz->altura
#define MAX(he,hd) (he > hd)? he : hd

typedef struct _no{
	struct _no *esq; // filho a esquerda
	int chave;
	struct _no *dir; // filho a direita
	int altura;
	int nesq; // número de nós a esquerda p/ func calcula_esq().
} noArv; // nó da arvore bináriq

void imprimeArvore_1(noArv *raiz);
void imprimeArvore_2(noArv *raiz);
void imprimeArvore_3(noArv *raiz);
int calcula_h(noArv *raiz);     // calcula altura da árvore
int calcula_esq(noArv *raiz);   // atualiza (nesq) de todos os nós.

int main(void){

	


	return 0;
}

// método 1: percurso em pré-ordem.
void imprimeArvore_1(noArv *raiz){
	if(raiz != NULL){
		printf("%d ", raiz->chave);
		imprimeArvore_1(raiz->esq); // começa pela esq.
		imprimeArvore_1(raiz->dir);
	}
}

// método 2: percurso em ordem.
void imprimeArvore_2(noArv *raiz){
	if(raiz != NULL){
		imprimeArvore_2(raiz->esq);
		printf("%d ", raiz->chave);
		imprimeArvore_2(raiz->dir);
	}
}

// método 3: percurso em pós-ordem.
void imprimeArvore_3(noArv *raiz){
	if(raiz != NULL){
		imprimeArvore_3(raiz->esq);
		imprimeArvore_3(raiz->dir);
		printf("%d ", raiz->chave);
	}
}

/*
void emOrdem_iterativo(noArv *raiz, noPilha *pilha){
	pt = ptraiz
	while(pt != NULL){
		while(pt != NULL){
			push(pt);
			pt = pt->esq;
		}
		while(pt == NULL e pilha não vazia){
			pt = pop();
			printf("%d", pt->chave);
			pt = pt->chave;
		}
	}
}

void percorre(noArv *raiz){
	push(raiz, 1)
	enquanto pilha ñ vazia
		pt, op = pop()
		if(op == 1){
			push(pt, 2)
			if(pt->esq != NULL)
				push(pt->esq, 1)
		if(op == 2)
			printf("%d", pt->chave);
			if(pt->dir != NULL)
				push(pt0>dir, 1);
		}
}
*/


int calcula_h(noArv *raiz){
	if(raiz == NULL) return 0;
	
	int hesq = calcula_h(raiz->esq);
	int hdir = calcula_h(raiz->dir);
	raiz->altura = MAX(hesq,hdir) + 1;
	
	return raiz->altura;
}

int calcula_esq(noArv *raiz){
	if(raiz == NULL)
		return 0;
		
	int ne = calcula_esq(raiz->esq);
	int nd = calcula_esq(raiz->dir);
	raiz->nesq = ne;
	return ne+nd+1;
}
