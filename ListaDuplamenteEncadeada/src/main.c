#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no *prox;
	struct no *ant;
} NoLista;

void InsereInicio(NoLista **l, int v){
	NoLista *n = (NoLista *)malloc(sizeof(NoLista));

	if (n != NULL){
		n->info = v;
		n->ant = NULL; n->prox = *l;
		if (*l != NULL) (*l)->ant = n;
		*l = n;
	}
}

NoLista* ultimo(NoLista **l){
	NoLista *aux=NULL;
	if (*l != NULL){
		for (aux = *l; aux->prox != NULL; aux = aux->prox);
	}
	return aux;
}
void imprimeLista(NoLista **l){
	NoLista *aux, *ult;
	ult = ultimo(l);
	for (aux = ult; aux != NULL; aux = aux->ant){
		printf("%d ", aux->info);
	}
	printf("\n");
}

NoLista* busca(NoLista **l, int v){
	NoLista *aux = NULL;
	for (aux = *l; aux != NULL && aux->info != v; aux = aux->prox);
	return aux;
}

void retira(NoLista **l, int v){
	NoLista *aux = busca(l, v);

	if (aux->ant == aux->prox)
		*l = NULL;
	else{
		if(aux->ant == NULL){
			aux->prox->ant = aux->ant;
			*l = aux->prox;
		}else if(aux->prox == NULL){
			aux->ant->prox = aux->prox;
		}else{
			aux->ant->prox = aux->prox;
			aux->prox->ant = aux->ant;
		}
	}
	free(aux);
}

int main(void){
	NoLista *lista=NULL;
	InsereInicio(&lista, 5);
	imprimeLista(&lista);
	retira(&lista, 5);
	imprimeLista(&lista);
	return 0;
}
