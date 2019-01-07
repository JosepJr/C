/*/				Implementação de Pilha com Lista.
 *
 *   ---
 *  |   |
 *   ---       ---------
 *   ...  =>  |  prim   | => |  || -> | || -> //
 *   ---      |  |   |  |
 *  |   |      ---------
 *   ---
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
	float info;
	struct no *prox;
} NoLista;

typedef struct pilha{
	NoLista *prim;
} Pilha;

Pilha* criar_pilha(){
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	p->prim = NULL;
	return p;
}

void push(Pilha *p, float v){
	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
		novo->prox = p->prim;
		p->prim=novo;
		novo->info = v;
	}
	else
		printf("Erro!");
}

int estaVazia(Pilha* p){
	return (p->prim == NULL);
}

float pop(Pilha *p){
	float v = 0;
	if(!estaVazia(p)){
		NoLista *aux = p->prim;
		p->prim = aux->prox;
		v = aux->info;
		free(aux);
	}
	else
		printf("Vazia!");
	return v;
}

void liberar_lista(Pilha *p){
	NoLista *aux, *prox;

	while(aux != NULL){
		prox = aux->prox;
		free(aux);
		aux = prox;
	}
}

/*/void concatenaPilhas(Pilha* p1, Pilha* p2){
	Pilha *aux = criar_pilha();

	while(!estaVazia(p2))
		push(aux, pop(p2));

	while(!estaVazia(aux))
		push(p1,pop(aux));
} /*/

/*/void concatenaPilhas(Pilha* p1, Pilha* p2){
	if(!estaVazia(p2)){
		float aux = pop(p2);
		concatenaPilhas(p1, p2);
		push(p1, aux);
	}
}/*/

void concatenaPilhas(Pilha* p1, Pilha* p2){
	if (!estaVazia(p2)){
		NoLista *aux = p2->prim;

		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = p1->prim;
		p1 -> prim = p2 -> prim;
		p2 -> prim = NULL;
	}
}

void a(Pilha *p1, int v){
	if(!estaVazia(p1)){
		if(p1->prim->info != v){
			pop(p1);
			a(p1,v);
		}
	}
}

void imprime(Pilha *p){
	if(!estaVazia(p)){
		NoLista* aux;
		for(aux = p->prim; aux != NULL; aux = aux->prox)
			printf("%.2f ", aux->info);
	}
	else
		printf("Vazia!");
}

int main(void){
	Pilha *p = criar_pilha();
	Pilha *p2 = criar_pilha();
	push(p,5.5);
	push(p, 10);
	push(p, 7);
	push(p, 8.7);
	//concatenaPilhas(p,p2);
	imprime(p);
	a(p,10);
	imprime(p);
	return 0;
}
