#include<stdlib.h>
#include<stdio.h>

typedef struct arvore{
	int info;
	struct arvore* esq;
	struct arvore* dir;
}Arvore;

Arvore* criarArvoreVazia(){
	return NULL;
}

int estaVazia(Arvore* a){
	return (a == NULL);
}

Arvore* busca(Arvore* a, int v){
	if(estaVazia(a))
		return NULL;
	else{
		if(v < a->info)
			return busca(a->esq,v);
		else if(v > a->info)
			return busca(a->dir,v);
		else
			return a;
	}
}

Arvore* insere(Arvore* a, int v){
	if(estaVazia(a)){
		a = malloc(sizeof(Arvore));
		a->info = v;
		a->esq = NULL;
		a->dir = NULL;
	}else{
		if(v < a->info)
			a->esq = insere(a->esq,v);
		else if(v >= a->info)
			a->dir = insere(a->dir,v);
	}
	return a;
}

Arvore* remover(Arvore* a,int v){
	if(estaVazia(a))
		return NULL;
	else{
		if(v < a->info)
			a->esq = remover(a->esq,v);
		else if(v > a->info)
			a->dir = remover(a->dir,v);
		else{
			if(a->esq == NULL && a->dir == NULL){
				free(a);
				a = NULL;
			}else if(a->dir == NULL){
				Arvore* t = a;
				a = a->esq;
				free(t);
			}else if(a->esq == NULL){
				Arvore* t = a;
				a = a->dir;
				free(t);
			}else{
				Arvore* t = a->esq;
				while(t->dir != NULL){
					t = t->dir;
				}
				a->info = t->info;
				t->info = v;
				a->esq = remover(a->esq,v);
			}
		}
	}
	return a;
}

int qtdeNos(Arvore* a){
	if(estaVazia(a)){
		return 0;
	}else
		return 1 + qtdeNos(a->esq) + qtdeNos(a->dir);
}

Arvore* menor(Arvore* a){
	if(estaVazia(a)){
		printf("Avore vazia!");
		return NULL;
	}else{
		if(estaVazia(a->esq))
				return a;
		else{
			return menor(a->esq);
		}
	}
}

/*Arvore* menor(Arvore* a){
	if(estaVazia(a))
		return NULL;
	else{
		if(!estaVazia(a->esq)){
			Arvore*t = a->esq;
			while(t->esq != NULL)
				t = t->esq;
			return t;
		}
		else
			return a;
	}
}
*/

Arvore* maior(Arvore* a){
	if(estaVazia(a)){
		printf("Avore vazia!");
		return NULL;
	}else{
		if(estaVazia(a->dir))
				return a;
		else{
			return maior(a->dir);
		}
	}
}

int qtdeChar(Arvore* a, int c){
	if(estaVazia(a))
		return 0;
	else
		return a->info % 2 != 0 + qtdeChar(a->esq, c) + qtdeChar(a->dir, c);
}


void balancear(Arvore* a){
	if(!estaVazia(a)){
		int n_esq = qtdeNos(a->esq);
		int n_dir = qtdeNos(a->dir);
		if(n_dir >= n_esq + 2){
			a->esq = insere(a->esq,a->info);
			Arvore* m = menor(a->dir);
			a->info = m->info;
			a->dir = remover(a->dir,m->info);
		}
		else if(n_esq >= n_dir + 2){
			a->dir = insere(a->dir,a->info);
			Arvore* m = maior(a->esq);
			a->info = m->info;
			a->esq = remover(a->esq,m->info);
		}
	}
}

void imprime(Arvore* a){
	printf("<");
	if(!estaVazia(a)){
		printf("%d ", a->info);
		imprime(a->esq);
		imprime(a->dir);
	}
		printf(">");
}

void imprimeContrario(Arvore *a){
	if(!estaVazia(a)){
		imprimeContrario(a->dir);
		printf("%d ", a->info);
		imprimeContrario(a->esq);
	}
}

int main(){
	Arvore* a;
	a = criarArvoreVazia();
	a = insere(a,6);
	a = insere(a,9);
	a = insere(a,8);
	a = insere(a,9);
	a = insere(a,4);
	a = insere(a,5);
	imprime(a);
	printf("\n");
	imprimeContrario(a);
	printf("\n %d", qtdeChar(a, 9));
	return 0;
}
