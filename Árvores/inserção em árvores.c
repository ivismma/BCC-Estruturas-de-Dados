
// Inserção em árvores binárias de busca

#include <stdio.h>
#include <stdlib.h>

typedef struct _noArv{
	struct _noArv *esq;
	int chave;
	struct _noArv *dir;
} noArv;

noArv* init(){ return NULL; }
void insere1(noArv **ptarv, int chave); // iterativo
void insere2(noArv **ptarv, int chave); // recursivo
void imprimeArvore(noArv *raiz);

int main(void){
	noArv *arvore1 = init();

	insere1(&arvore1, -1);
	insere1(&arvore1, 100);
	insere1(&arvore1, 5);
	insere1(&arvore1, -7);
	insere1(&arvore1, -2);
	insere1(&arvore1, 40);
	imprimeArvore(arvore1);
	
	return 0;
}

void insere1(noArv **arv, int chave){
	noArv* pai = NULL;
	noArv* ptarv = *arv;
	while(ptarv != NULL && ptarv->chave != chave){
		pai = ptarv;
		if(chave < ptarv->chave)
			ptarv = ptarv->esq;
		else
			ptarv = ptarv->dir;
	}
	noArv *novo;
	if(ptarv == NULL){
		novo = (noArv *) malloc(sizeof(noArv));
		if(novo == NULL) exit(1); // falha aloc.
	
		novo->chave = chave;
		novo->esq = novo->dir = NULL;
		if(pai == NULL) *arv = novo; // significa que a árvore era vazia.
		// então atualiza novo nó para raiz da árvore.
		else if(chave < pai->chave)
			pai->esq = novo;
		else
			pai->dir = novo;
	}
}

// pré-ordem
void imprimeArvore(noArv *raiz){
	if(raiz != NULL){
		printf("%d ", raiz->chave);
		imprimeArvore_1(raiz->esq); // começa pela esq.
		imprimeArvore_1(raiz->dir);
	}
}
