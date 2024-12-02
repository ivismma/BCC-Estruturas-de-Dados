/*  
	Trabalho 3 - Estruturas de Dados
	Inserção em árvore rubro-negra (não recursiva,
	usando pilhas) e exibição em **pré-ordem**.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int CHAVE_ARV;

typedef struct _noArv {
    CHAVE_ARV chave;
    char cor; // 'R' Rubro | 'N' Negro
    struct _noArv *esq;
    struct _noArv *dir;
    struct _noArv *pai; // pai só é atribuido após a inserção de cada nó.
} noArv;

typedef noArv* CHAVE_PILHA;

typedef struct _noPilha {
    CHAVE_PILHA chave;
    struct _noPilha *prox;
} noPilha;

// funções de Árvore
void initArv(noArv **raiz);
void exibe_preOrdem(noArv *raiz);
noArv* aloca(CHAVE_ARV chave);
bool insere(noArv **raiz, CHAVE_ARV chave);
void conserta(noArv **raiz, noArv *novo);
void rotacaoEsq(noArv **raiz, noArv *x);
void rotacaoDir(noArv **raiz, noArv *x);

// funções de Pilha
void initPilha(noPilha **pilha);
void push(noPilha **topo, CHAVE_PILHA chave);
bool pop(noPilha **topo, CHAVE_PILHA *ref);

int main(void){
    noArv* arvore;
    initArv(&arvore);
    
   { // Leitura
    	int buffer;
		while(scanf("%d", &buffer) == 1)
			insere(&arvore, buffer);
	}
    exibe_preOrdem(arvore);
    
    return 0;
}

void initArv(noArv **raiz){
    *raiz = NULL;
}

void exibe_preOrdem(noArv *raiz){
    if (raiz != NULL){
        printf("%d%c ", raiz->chave, raiz->cor);
        exibe_preOrdem(raiz->esq);
        exibe_preOrdem(raiz->dir);
    }
}

noArv* aloca(CHAVE_ARV chave){
    noArv *novo = (noArv *) malloc(sizeof(noArv));
    if (novo == NULL) exit(1); // falha aloc..
    
    novo->chave = chave;
    novo->cor = 'R';
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    return novo;
}

// inserção não recursiva (usando pilhas)
bool insere(noArv **raiz, CHAVE_ARV chave){
    noArv *novo = aloca(chave);
    noPilha* pilha;
    initPilha(&pilha);
    noArv* atual = *raiz;
    noArv* pai = NULL;

    while(atual != NULL){
        push(&pilha, atual); // push na pilha do nó atual
        pai = atual;
        
        if(chave > atual->chave)
            atual = atual->dir;
        else if(chave < atual->chave)
            atual = atual->esq;
        else{
            printf("Chave %d ja inserida.\n", chave);
            return false;
        }
    }

    if (pai == NULL)
        *raiz = novo;
    else if (chave > pai->chave)
        pai->dir = novo;
    else
        pai->esq = novo;
    
    novo->pai = pai; // atualiza nó pai
    conserta(raiz, novo);
    
    return true;
}

// consertar após inserção:
void conserta(noArv **raiz, noArv *novo){
    while(novo != *raiz && novo->pai->cor == 'R'){
        // caso 1: pai é vermelho
        if(novo->pai == novo->pai->pai->esq){
            noArv* tio = novo->pai->pai->dir;
            
            if(tio != NULL && tio->cor == 'R'){
                // tio é vermelho
                novo->pai->cor = 'N';
                tio->cor = 'N';
                novo->pai->pai->cor = 'R';
                novo = novo->pai->pai;
        	}
            else{
                // tio é negro ou não tem tio
                if(novo == novo->pai->dir){
                    novo = novo->pai;
                    rotacaoEsq(raiz, novo);
                }
                novo->pai->cor = 'N';
                novo->pai->pai->cor = 'R';
                rotacaoDir(raiz, novo->pai->pai);
            }
        }
		else{
            noArv* tio = novo->pai->pai->esq;
            
            if(tio != NULL && tio->cor == 'R'){
                novo->pai->cor = 'N';
                tio->cor = 'N';
                novo->pai->pai->cor = 'R';
                novo = novo->pai->pai;
            }
			else{
                if(novo == novo->pai->esq){
                    novo = novo->pai;
                    rotacaoDir(raiz, novo);
                }
                novo->pai->cor = 'N';
                novo->pai->pai->cor = 'R';
                rotacaoEsq(raiz, novo->pai->pai);
            }
        }
    }
    
	(*raiz)->cor = 'N'; // A raiz deve ser sempre negra
}

void rotacaoEsq(noArv **raiz, noArv *x){
    noArv *y = x->dir;
    x->dir = y->esq;
    
    if(y->esq != NULL)
        y->esq->pai = x;
    
    y->pai = x->pai;
    
    if(x->pai == NULL)
        *raiz = y;
    else if(x == x->pai->esq)
        x->pai->esq = y;
    else 
        x->pai->dir = y;
    
    y->esq = x;
    x->pai = y;
}

void rotacaoDir(noArv **raiz, noArv *x){
    noArv *y = x->esq;
    x->esq = y->dir;
    
    if(y->dir != NULL)
        y->dir->pai = x;
    
    y->pai = x->pai;
    
    if(x->pai == NULL)
        *raiz = y;
    else if(x == x->pai->dir)
        x->pai->dir = y;
	else
        x->pai->esq = y;
    
    y->dir = x;
    x->pai = y;
}

// Funções de Pilha
void initPilha(noPilha **pilha){
    *pilha = NULL;
}

void push(noPilha **topo, CHAVE_PILHA chave){
    noPilha *novo = (noPilha *) malloc(sizeof(noPilha));
    if(novo == NULL) exit(1); // falha aloc.
    
    novo->chave = chave;
    novo->prox = *topo;
    *topo = novo;
}

bool pop(noPilha **topo, CHAVE_PILHA *ref){
    if(*topo == NULL)
        return false; // pilha vazia.

    // se ref for NULL, nao ha interesse em saber a chave, apenas desempilhar.
    if (ref != NULL){
        *ref =(*topo)->chave;
    }
    noPilha *apagar = *topo;
    *topo =(*topo)->prox;
    free(apagar);
    return true;
}

