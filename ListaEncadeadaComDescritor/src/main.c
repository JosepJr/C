#include <stdio.h>
#include <stdlib.h>

typedef struct descritor{
	struct nolista *prim;
	struct nolista *ult;
	int n;
} Descritor;

typedef struct nolista{
	int info;
	struct nolista *prox;
} NoLista;

void criarLista(Descritor *d){
	d->prim = NULL;
	d->ult = NULL;
	d->n = 0;
}

void inserirElementoInicio(Descritor *d, int v){
	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
		novo->info = v;
		novo->prox = d->prim;
		d->prim = novo;
		if (d->n == 0)
			d->ult = novo;
		d->n++;
	}
	else
		exit(1);
}

void inserirElementoFim(Descritor *d, int v){
	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
		novo->info = v;
		novo->prox = NULL;
		if (d->n == 0)
			d->prim = novo;
		else
			d->ult->prox = novo;
		d->ult = novo;
		d->n++;
	}
	else
		exit(1);
}

int estaVazia(Descritor *d){
	return (d->n == 0);
}

void imprimeLista(Descritor *d){
	NoLista *aux=NULL;
	if (!estaVazia(d)){
		for (aux = d->prim; aux != NULL; aux = aux->prox)
			printf("%d ", aux->info);
		printf("\n");
	}
	else
		printf("\t Lista Vazia! \n");
}

void removerElemento(Descritor *d, int v){
	if (!estaVazia(d)){
		NoLista *aux=NULL, *ant=NULL;
		for(aux = d->prim; aux != NULL && aux->info != v; aux = aux->prox)
			ant = aux;
		if (ant == NULL){
			d->prim = aux->prox;
			if (d->n == 1)
				d->ult = NULL;
		}
		else{
			if (aux -> prox == NULL)
				d->ult = ant;
			ant->prox = aux->prox;
		}
		free(aux);
		d->n--;
	}
	else
		printf("\t Lista Vazia! \n");
}

void liberarLista(Descritor *d){
	if (!estaVazia(d)){
		NoLista *aux, *ant;
		for (aux = d->prim; aux != NULL; aux = aux->prox){
			free(ant);
			ant = aux;
		}
		criarLista(d);
	}
	else
		printf("\t Lista Vazia! \n");
}

int main(void){
	Descritor l;
	criarLista(&l);
	inserirElementoInicio(&l, 5);
	inserirElementoInicio(&l, 2);
	inserirElementoInicio(&l, 10);
	inserirElementoFim(&l,6);
	inserirElementoFim(&l, 15);
	imprimeLista(&l);
	removerElemento(&l, 2);
	imprimeLista(&l);
	liberarLista(&l);
	imprimeLista(&l);
	return 0;
}
