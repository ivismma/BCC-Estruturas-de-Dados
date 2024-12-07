/*
	Trabalho 4 - Estrutura de Dados
	Implementar uma tabela hash com as seguintes propriedades:

	Encademento interno. Sem área de colisão e sem coalescência. 
	Inserções. Remoções. Exibições.
*/

// entrada até EOF:
// i (valor) - inserir | r (valor) - remover | l - exibir

/* 
exemplo de entrada:
5
i 11
i 21
i 3
i 42
i 13
r 3
i 31
l
saída esperada:
31
11
42
13
21
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _tChave{
	int chave;
	bool ocupado;
	int prox;
} tChave;

typedef struct{
	tChave *v;
	int tam;
} hashTable;

void init_table(hashTable *t, int tam); // init na estrutura de dados
int busca(hashTable *t, int chave); // busca indice da chave, retorna -1 se não tem.
int fhash(int chave, int mod); // aplica função hash.
int proxDisponivel(hashTable *t, int chave, int indAtual); // retorna indice do proximo indice disponivel
void atualizaPonteiro(hashTable *t, int movido, int novaPos); // atualiza ponteiro quando uma chave é movida de lugar
void insere(hashTable *t, int chave); // insere na hash table
void apaga(hashTable *t, int chave); // apaga da hash table
void exibe(hashTable *t); // exibe

int main(){
    hashTable ht;
    
    { // entrada
    	char buffer1;
		int buffer2;
		
		if(scanf("%d", &buffer2) == 1)
			init_table(&ht, buffer2);
		else exit(4);
		
		while(scanf("%c", &buffer1) == 1){
			switch(buffer1){
				case 'i':
					if(scanf("%d", &buffer2) == 1)
						insere(&ht, buffer2);
					else
						exit(2); // entrada incompleta. EOF.
					break;
				case 'r':
					if(scanf("%d", &buffer2) == 1)
						apaga(&ht, buffer2);
					else
						exit(3); // entrada incompleta. EOF.
					break;
				case 'l':
					exibe(&ht);
					break;
				default:
					break;
			}
		}
	}
    
    return 0;
}


void init_table(hashTable *t, int tam){
	t->v = (tChave *) malloc(tam * sizeof(tChave));
	if(t->v == NULL) exit(1); // falha aloc.
	t->tam = tam;
	
	for(int i = 0; i < tam; ++i){
		t->v[i].ocupado = false;
		t->v[i].prox = -1;
	}
}

int fhash(int chave, int mod){
	return chave%mod;
}

int proxDisponivel(hashTable *t, int chave, int indAtual){
	int cont = 0;
	for(int i = indAtual+1; cont < t->tam-1; i = (i+1)%t->tam, ++cont){
		if(t->v[i].ocupado == false)
			return i;
	}
	return -1; // não tem lugar disponivel, overflow...
}

void insere(hashTable *t, int chave){
	int indice = fhash(chave, t->tam);
	
	if(t->v[indice].ocupado == false){
		t->v[indice].chave = chave;
		t->v[indice].ocupado = true;
	}
	else{
		int proxLugar = proxDisponivel(t, chave, indice);
		int hashChave = fhash(chave, t->tam);
		if(fhash(t->v[indice].chave, t->tam) != hashChave){ // tem gente de hash diferente o ocupando o hash dele.
			if(proxLugar == -1) exit(2); // overflow.
			
			atualizaPonteiro(t, indice, proxLugar);
			t->v[proxLugar].chave = t->v[indice].chave;
			t->v[proxLugar].ocupado = true;	
			t->v[indice].chave = chave;
			t->v[indice].prox = -1;
			
		}
		else{ // ocupa um indice e posiciona os ponteiros desse hash corretamente.
			t->v[proxLugar].ocupado = true;
			t->v[proxLugar].chave = chave;
			
			int atual = t->v[indice].prox;
			if(atual == -1) // a chave já é a última do encadeamento interno. aponta direto
				t->v[indice].prox = proxLugar;
			else{                
				while(t->v[atual].prox != -1){ // percorre até a ultima chave do hash para atualizar o próximo
					atual = t->v[atual].prox;
				}
		 	
				t->v[atual].prox = proxLugar; // atualiza o último do enc. interno desse hash para a nova inserida
			}
		}
	}
}

int busca(hashTable *t, int chave){
	int hash = fhash(chave, t->tam);
	int atual = hash;
	while(t->v[atual].prox != -1){ // percorre encadeamento interno buscando...
		if(t->v[atual].chave == chave)
			return atual;
		atual = t->v[atual].prox;
	}
	// verifica se é o último do encadeamento, se não for, então a chave não está na hash table.
	return (t->v[atual].chave == chave)? atual : -1; 
}

// se alguém apontava para uma chave e ela foi movida de lugar, atualiza ponteiro p/ seu novo indice
// essa função percorre encadeamento do hash e procura quem apontava pro cara q vai ser movido p/ atualizar.
void atualizaPonteiro(hashTable *t, int movido, int novaPos){
	int i = fhash(t->v[movido].chave, t->tam);
	// percorre o encadeamento e atualiza nova posição da chave movida de lugar.
	while(t->v[i].prox != -1){
		if(t->v[i].prox == movido){
			t->v[i].prox = novaPos;
			break;
		}
		i = t->v[i].prox;
	}
}

void apaga(hashTable *t, int chave){
	int remover = busca(t, chave); // indice do que vai apagar
	if(remover == -1) return; // não está na hashtable.
	
	int hash = fhash(chave, t->tam);
	if(remover == hash){ // significa que ele está no próprio lugar do seu hash.
		int prox = t->v[remover].prox;
		if(prox != -1){ // ele aponta para alguém
			t->v[remover] = t->v[prox];
			t->v[prox].ocupado = false;
			t->v[prox].prox = -1;
		}
		else{ // apenas remove.
			t->v[remover].ocupado = false;
			t->v[remover].prox = -1;
		}
	}
	else if(fhash(t->v[remover].chave, t->tam) == hash){
		// significa que esse cara provavelmente está entre os ponteiros, precisa "reamarrar":
		// esse segundo caso irá cobrir qualquer remoção em que o removido esteja sendo apontado por alguém.
		
		int anterior = hash; // é o primeiro
		int atual = t->v[anterior].prox;
		while(t->v[atual].chave != chave){
			//printf("%d -> %d\n", t->v[anterior].chave, t->v[atual].chave);
			anterior = atual;
			atual = t->v[atual].prox;
		}
		int desocupar = t->v[anterior].prox;
		t->v[anterior].prox = t->v[desocupar].prox;
		t->v[desocupar].ocupado = false;
		t->v[desocupar].prox = -1;
	}
}

void exibe(hashTable *t){
	for(int i = 0; i < t->tam; ++i){
		if(t->v[i].ocupado){
			printf("%d", t->v[i].chave);
			int prox = t->v[i].prox;
			if(prox != -1)
				printf(" (aponta para %d)", t->v[prox].chave);
			printf("\n");
		}
		else
			printf("VAZIO\n");
	}
}
