// Trabalho 2
// Ordenação topológica - Estruturas de Dados

#include <stdio.h>
#include <stdlib.h>
#define MAX 100 // máx. do exercício (1 <= n <= 100).

// estrutura do nó
typedef struct _noLista{
	int chave;
	struct _noLista *prox;
} noLista;

// estrutura da lista
typedef struct{
	int qtd;
	noLista *topo;
} Lista; // Lista que irá guardar as listas

void initLista(Lista *lista);
void insereTarefa(Lista *lista, int t1, int t2);
void limpaListas(Lista *lista);
void ordenacao_topologica(Lista *lista, int n);

int main(void){
	// inicialização das listas
	Lista lista_tarefas[MAX]; // Lista de listas
	int n, m;
	int t1, t2; // tarefa 1, tarefa2.
	
	scanf("%d %d", &n, &m);
	while(!(n == 0 && m == 0)){
		for(int i = 0; i < MAX; ++i)
			initLista(&lista_tarefas[i]);
		
		for(int i = 0; i < m; ++i){
			scanf("%d %d", &t1, &t2);
			insereTarefa(lista_tarefas, t1-1, t2-1);
		}
		ordenacao_topologica(lista_tarefas, n);
		limpaListas(lista_tarefas);
		scanf("%d %d", &n, &m);
	}
	
	return 0;
}

void initLista(Lista *lista){
	lista->qtd = 0;
	lista->topo = NULL;
}

void insereTarefa(Lista *lista, int t1, int t2){
	noLista *novo = (noLista *) malloc(sizeof(noLista));
	if(novo == NULL) exit(1); // falha aloc.
	novo->chave = t2;
	novo->prox = NULL;
	
	if(lista[t1].topo == NULL) 
		lista[t1].topo = novo;
	else{
		noLista *atual = lista[t1].topo;
		for(;atual->prox != NULL; atual = atual->prox);
		
		atual->prox = novo;
	}
	++lista[t2].qtd;
}

void limpaListas(Lista *lista){
	for(int i = 0; i < MAX; ++i){
		noLista *atual = lista[i].topo;
		// percorre a lista atual (da lista que guarda as listas)
		while(atual != NULL){
			noLista *aux = atual;
			atual = atual->prox;
			free(aux);
		}
	}
}

void ordenacao_topologica(Lista *lista, int n){
	int ordem[MAX];
	int k = 0;      
	int fila[MAX];  // nós com grau entrada 0
	int inicio = 0, fim = 0;

	for(int i = 0; i < n; ++i){
		if(lista[i].qtd == 0)
			fila[fim++] = i;
	}

	while(inicio < fim){
		int atual = fila[inicio++];
		ordem[k++] = atual + 1;

		noLista *sucessor = lista[atual].topo; 
		while(sucessor != NULL){
			--lista[sucessor->chave].qtd; 
			if(lista[sucessor->chave].qtd == 0){
				fila[fim++] = sucessor->chave; 
			}
			sucessor = sucessor->prox;
		}
	}

	for(int i = 0; i < k; ++i)
		printf("%d ", ordem[i]);
	puts("");
}

