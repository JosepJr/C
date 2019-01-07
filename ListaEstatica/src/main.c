#define MAX 10
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct lista{
	int vetor[MAX];
	int ultimo;
}Lista;

void criarLista(Lista* l){
	l->ultimo = 0;
}

int estaVazia(Lista* l){
	// Retorna 1 se for igual a zero
	return (l->ultimo == 0);
}

int estaCheia(Lista* l){
	return(l->ultimo == MAX);
}

void inserirElemento(Lista* l, int v){
	if(!estaCheia(l)){
		l->vetor[l->ultimo] = v;
		l->ultimo ++;
		printf("\t Restam %d posicoes. \n", 10-l->ultimo);
	}
	else{
		printf("Lista está cheia!");
	}
}

void imprimeLista(Lista* l){
	int i;
	if(!estaVazia(l)){
		printf("\t Elementos da lista: ");
		for(i = 0; i < l->ultimo; i++){
			printf("#%d = [ %d ] ", i+1, l->vetor[i]);
		}
		printf("\n\n");
	}
	else
		printf("Lista está vazia! \n");
}

int removerElemento(int p, Lista* l){
	int j, removeu=0;
	if (p >= 0 && p < l->ultimo){
		for (j=p; j < l->ultimo; j++)
			l->vetor[j] = l->vetor[j+1];
		l->ultimo--;
		removeu = 1;
	}
	return removeu;
}

int main(){
	int n = 0, opcao;
	char verifica = 'S';
	Lista l;

	while(verifica != 'N'){
		printf("O que deseja fazer?\n");
		printf("1 - Criar lista\n");
		printf("2 - Inserir elemento\n");
		printf("3 - Imprimir lista\n");
		printf("4 - Remover Elemento\n");
		fflush(stdout);
		scanf("%d", &opcao);

		switch(opcao){
		case 1:
			criarLista(&l);
			break;
		case 2:
			printf("Digite o elemento que deseja inserir: \n");
			fflush(stdout);
			scanf(" %d", &n);
			inserirElemento(&l, n);
			break;
		case 3:
			imprimeLista(&l);
			break;
		case 4:
			if (!estaVazia(&l)){
				printf("Digite a posicao do elemento que deseja remover: \n");
				fflush(stdout);
				scanf(" %d", &n);
				removerElemento(n, &l);
			}
			else
				printf("\t Lista Vazia meu Chapa! \n");
			break;
		}

		printf("\n\t Deseja relizar mais alguma operação? S ou N \n");
		fflush(stdout);
		scanf(" %c", &verifica);
		verifica = toupper(verifica);
	}

	return 0;
}

