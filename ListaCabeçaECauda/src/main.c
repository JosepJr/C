#include <stdio.h>
#include <stdlib.h>

typedef struct nolista{
	int info;
	struct nolista* prox;
} NoLista;

typedef struct lista{
	NoLista *cabeca;
	NoLista *cauda;
} Lista;

void criar_vazia(Lista *l){
	l->cabeca = (NoLista *)malloc(sizeof(NoLista));
	l->cauda = (NoLista *)malloc(sizeof(NoLista));
	l->cabeca->prox = l->cauda;
	l->cauda->prox = NULL;
}

void inserir_elemento(Lista *l, int v){
	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
		novo->info = v;
		novo->prox = l->cabeca->prox;
		l->cabeca->prox = novo;
	}else
		exit(1);
}

void insere_ordenado(Lista *l, int v){
	NoLista *aux = NULL;

	for (aux = l->cabeca->prox; aux != NULL && aux->info < v; aux = aux->prox);

	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
		novo->info = v;
		novo->prox = aux->prox;
		aux->prox = novo;
	}
}

void imprime_tudo(Lista *l){
	NoLista *aux;
	if (l->cabeca->prox != l->cauda){
		for(aux = l->cabeca->prox; aux->prox != NULL; aux = aux->prox)
			printf("%d ", aux->info);
		printf("\n");
	}
}

void removerElemento(Lista* l, int v){
	NoLista* p, *ant = l->cabeca;

	for(p = l->cabeca->prox; p != l->cauda && p->info != v; p = p->prox){
		ant = p;
	}

	if(p == l->cauda){
		printf("Elemento não encontrado!");
	}else{
		ant->prox = p->prox;
		free(p);
	}
}

void liberar(Lista* l){
	NoLista* p = l->cabeca->prox, *temp;

	while(p != l->cauda){
		temp = p->prox;
		free(p);
		p = temp;
	}
	l->cabeca->prox = l->cauda;
}

int main(void){
	Lista l;
	criar_vazia(&l);
	inserir_elemento(&l, 5);
	inserir_elemento(&l, 3);
	imprime_tudo(&l);
	return 0;
}
