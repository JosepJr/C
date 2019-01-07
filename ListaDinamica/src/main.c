#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	int info;
	struct no* prox;
} NoLista;

NoLista* criarLista(){
	return NULL;
}

/* void criarLista(NoLista **l){
	*l = NULL;
} */

int estaVazia(NoLista **l){
	return (*l == NULL);
}

void InsereInicio(NoLista **l, int v){
	NoLista* n = (NoLista *)malloc(sizeof(NoLista));
	if (n != NULL){
		n->info = v;
		n->prox = *l;
		*l = n;
	}
}

void imprime(NoLista **l){
	if (!estaVazia(l)){
		NoLista *aux;
		for (aux = *l; aux != NULL; aux = aux->prox)
			printf("%d ", aux->info);
		printf("\n");
	}
	else
		printf("\n\t Lista Vazia!");
}

NoLista* busca(NoLista **l, int v){
	if (!estaVazia(l)){
		NoLista *aux;
		for (aux = *l; aux != NULL; aux = aux->prox)
			if (aux->info == v)
				return aux;
		return NULL;
	}
	else{
		printf("\n\t Lista Vazia!");
		return NULL;
	}
}

void insere_ordenado(NoLista** l, int v){
	NoLista* p, *ant = NULL, *n;
	for(p = *l; p != NULL && p->info < v; p = p->prox){
		ant = p;
	}
	n = malloc(sizeof(NoLista));
	n->info = v;
	if(ant == NULL){
		n->prox = *l;
		*l = n;
	}else{
		n->prox = ant->prox;
		ant->prox = n;
	}
}

int numElementos(NoLista** l){
	NoLista* p;
	int n = 0;

	for(p = *l; p != NULL; p = p->prox){
		n++;
	}
	return n;
}

void remover(NoLista **l, int v){
	if (!estaVazia(l)){
		NoLista *aux, *ant=NULL;

		for(aux = *l; aux != NULL && aux->info != v; aux = aux->prox)
			ant = aux;

		if (aux == NULL)
			printf("\t Elemento nao encontrado!");
		else{
			if (ant == NULL)
				*l = aux->prox;
			else
				ant->prox = aux->prox;
		}
		free(aux);
	}
	else
		printf("\n\t Lista Vazia!");
}

void limpa_lista(NoLista **l){
	if (!estaVazia(l)){
		NoLista *aux, *prox;
		for (aux = *l; aux != NULL; aux = prox){
			prox = aux->prox;
			free(aux);
		}
		*l = NULL;
	}
	else
		printf("\n\t Lista Vazia!");
}

NoLista* ultimo(NoLista **l){
	if (!estaVazia(l)){
		NoLista *aux;
		for (aux = *l; aux != NULL; aux = aux->prox)
			if (aux->prox == NULL)
				return aux;
		return NULL;
	}
	else{
		printf("\n\t Lista Vazia!");
		return NULL;
	}
}

NoLista* concatena(NoLista** l1, NoLista** l2){
	if(l1 == NULL)
		*l1 = *l2;
	else{
		NoLista *aux;
		for (aux = *l1; aux->prox != NULL; aux = aux->prox);
		aux->prox = *l2;
	}
	return *l1;
}

NoLista* separa(NoLista** l, int n){
	if (!estaVazia(l)){
		NoLista *aux, *l2 = NULL;
		for (aux = *l; aux != NULL; aux = aux->prox)
			if(aux->info == n){
				l2 = aux->prox;
				aux->prox = NULL;
				return l2;
			}
		return NULL;
	}
	else{
		printf("\n\t Lista Vazia!");
		return NULL;
	}
}

NoLista* concatena_intercalada(NoLista **l1, NoLista **l2){
	NoLista *l3 = NULL;
	if (!estaVazia(l1))
		l3 = *l2;
	else if (!estaVazia(l2))
		l3 = *l1;
	else{
		NoLista *p, *q, *aux;
		for (p = *l1, q = *l2; p != NULL && q != NULL; p = p->prox, q = q->prox){
			NoLista *n1 = (NoLista *)malloc(sizeof(NoLista));
			NoLista *n2 = (NoLista *)malloc(sizeof(NoLista));

			n1->info = p->info;
			n2->info = q->info;
			n1->prox = n2;
			n2->prox = NULL;
			aux = n2;
			if (l3 == NULL)
				l3 = n1;
			else
				aux->prox = n1;
		}
		if (q != NULL)
			aux->prox = q;
		else
			aux->prox = p;
	}
	return l3;
}

void imprimeRecursiva(NoLista** l){
	if (!estaVazia(l)){
		NoLista *aux = *l;
		printf("%d ", aux->info);
		imprimeRecursiva(&aux->prox);
	}
}

void liberarLista(NoLista **l){
	if (*l != NULL){
		liberarLista(&(*l)->prox);
		free(*l);
	}
}

NoLista* buscaRecursiva(NoLista** l, int v){
	if (!estaVazia(l)){
		if((*l)->info == v)
			return (*l);
		else if ((*l) == NULL)
			return NULL;
		else
			return buscaRecursiva(&(*l)->prox, v);
	}
	else
		return NULL;
}

void imprimeRecursivaContrario(NoLista** l){
	if (!estaVazia(l)){
		imprimeRecursivaContrario(&(*l)->prox);
		printf("%d", (*l)->info);
	}
}

void removerElemento(NoLista **l, int v){
	if (*l == NULL)
		printf("Elemento nao encontrado! \n");
	else if ((*l)->info == v){
		NoLista *aux = *l;
		*l = (*l)->prox;
		free(aux);
	}
	else
		removerElemento(&(*l)->prox, v);
}


int main(void){
	NoLista *lista, *lista4, *lista5;
	lista = criarLista();
	//lista4 = criarLista();
	//lista5 = criarLista();
	// criarLista(&lista);
	int i;

	for (i=0; i < 10; i++)
		insere_ordenado(&lista, i);

	NoLista *lista2 = buscaRecursiva(&lista, 3);
	if (lista2 != NULL)
		printf("\n %d\n", lista2->info);

	//removerElemento(&lista, 5);
	imprimeRecursivaContrario(&lista);

	//lista4 = separa(&lista, 3);

	//lista = concatena(&lista, &lista4);
	//lista5 = concatena_intercalada(&lista, &lista4);

	liberarLista(&lista);
	lista = NULL;
	imprime(&lista);
	return 0;
}
