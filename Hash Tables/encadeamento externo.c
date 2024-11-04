// Impl. de hash table por **ENCADEAMENTO EXTERNO**
// Não há repetição de chaves

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define R 6 // R-1 encadeamentos externos -> [0, 1, 2, 3, 4, 5]
            // (vetores de listas encadeadas)

typedef int TIPOCHAVE;

typedef struct _noLista{
	TIPOCHAVE chave;
	struct _noLista* prox;
} noLista;

/// Funcões Listas Encadeadas ///
void exibeLista(noLista *topo);                      // exibe a lista
void push(noLista **topo, TIPOCHAVE chave);          // insere no topo
void libera(noLista **topo, noLista* endereco);      // remover/apagar
noLista *buscaChave(noLista *topo, TIPOCHAVE chave); // acha endereço da chave
/////////////////////////////////

/// Funções da HashTable ////////
void init_hashTable(noLista *hashTable[R]);
int hash(int k); // k mod R;
void exibe_hashTable(noLista *hashTable[R]);
bool insere(noLista *hashTable[R], TIPOCHAVE chave);
bool deleta(noLista *hashTable[R], TIPOCHAVE apagar);
void reinit_hashTable(noLista *hashTable[R]);
/////////////////////////////////


int main(void){
	noLista *hashTable[R];
	init_hashTable(hashTable);
	
	// Testes:
	insere(hashTable, 2);
	insere(hashTable, 4);
	insere(hashTable, 9);
	insere(hashTable, 12);
	insere(hashTable, 12); // ñ deverá ser inserido
	insere(hashTable, 88);
	insere(hashTable, 0);
	insere(hashTable, 100);
	insere(hashTable, -32);
	insere(hashTable, 4);
	insere(hashTable, 56);
	insere(hashTable, -3);
	exibe_hashTable(hashTable);
	
	int n = -32;
	deleta(hashTable, n);
	printf("\nApós tentar apagar a chave %d...\n", n);
	exibe_hashTable(hashTable);
	
	reinit_hashTable(hashTable);
	printf("\nApós reinicializar a hashTable...\n");
	exibe_hashTable(hashTable);
	
	return 0;
}

void exibeLista(noLista *topo){
	noLista *atual = topo;
	printf("[");
	for(;atual != NULL; atual = atual->prox)
		printf("%d -> ", atual->chave);
	
	printf("NULL]\n");
}

// Insere no topo da lista
void push(noLista **topo, TIPOCHAVE chave){
	noLista *novo = (noLista *) malloc(sizeof(TIPOCHAVE));
	if(novo == NULL) exit(1); // falha aloc.
	novo->chave = chave;
	if(*topo == NULL){
		*topo = novo;
		novo->prox = NULL;
	}
	else{
		novo->prox = *topo;
		*topo = novo;
	}
}

// Retorna o endereço de memória da chave buscada, NULL se ñ houver.
noLista* buscaChave(noLista *topo, TIPOCHAVE chave){
	noLista *atual = topo;
	for(;atual != NULL; atual = atual->prox){
		if(atual->chave == chave)
			return atual;
	}
	return NULL; // não achou.
}

// Desalocar o nó.
void libera(noLista **topo, noLista* endereco){
	assert(endereco != NULL);
	if(*topo == endereco){
		*topo = (*topo)->prox;
		free(endereco);
		return;
	}
	noLista *atual = *topo;
	while(atual->prox != endereco){
		atual = atual->prox;
	}
	assert(atual->prox == endereco);
	atual->prox = endereco->prox;
	free(endereco);
}

////////////////////////////////////////////////////

// uma função hash qualquer.
int hash(int k){
	if(k < 0) k = -k; // caso a chave seja negativa.
	return k%R; // nesse caso: k mod R
}

void init_hashTable(noLista* hashTable[R]){
	for(int i = 0; i < R; ++i)
		hashTable[i] = NULL;
}

void exibe_hashTable(noLista *hashTable[R]){
	for(int i = 0; i < R; ++i){
		printf("k = %d --> ", i);
		exibeLista(hashTable[i]);
	}
}

bool insere(noLista *hashTable[R], TIPOCHAVE chave){
	int i = hash(chave);
	if(buscaChave(hashTable[i], chave) != NULL)
		return false; // já tem na hash table
	
	push(&hashTable[i], chave);
	return true;
}

bool deleta(noLista *hashTable[R], TIPOCHAVE apagar){
	int i = hash(apagar);
	noLista* endereco = buscaChave(hashTable[i], apagar);
	if(endereco == NULL) 
		return false; // não está na hashtable
	
	libera(&hashTable[i], endereco);
	return true; // foi apagado.
}

void reinit_hashTable(noLista *hashTable[R]){
	for(int i = 0; i < R; ++i){
		noLista *atual = hashTable[i];
		while(atual != NULL){
			noLista *aux = atual;
			atual = atual->prox;
			free(aux);
		}
		hashTable[i] = NULL;
	}
}
