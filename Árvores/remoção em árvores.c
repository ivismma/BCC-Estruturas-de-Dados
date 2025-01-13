
// Remoção em árvores binárias de busca

#include <stdio.h>
#include <stdlib.h>

// predecessor: menor chave das sub-árvores da raiz
// sucessor:    maior chave das sub-árvores da raiz

typedef struct _noArv{
	struct _noArv *esq;
	int chave;
	struct _noArv *dir;
} noArv;

noArv* init(){ return NULL; }
void imprimeArvore(noArv *raiz);
void remove(**arv, int chave);


int main(void){
	noArv *arvore1 = init();
	
	return 0;
}

void remove(**arv, int chave){
	noArv* NULL;
	noArv* ptarv = arv;
	
	while(ptarv != NULL && ptarv->chave != chave){
		if(chave < ptarv->chave){
			pai = ptarv;
			ptarv = ptarv->esq;
		}
		else{
			pai = ptarv;
			ptarv = ptarv->dir;
		}
	}
}
