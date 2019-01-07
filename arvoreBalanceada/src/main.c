#include<stdlib.h>
#include<stdio.h>

typedef struct arvore{
	int info;
	struct arvore* esq;
	struct arvore* dir;
}Arvore;

Arvore* criarArvore(int n, Arvore* esq, Arvore* dir){
	Arvore* a = malloc(sizeof(Arvore));
	if(a != NULL){
		a->info = n;
		a->esq = esq;
		a->dir = dir;
	}
	return a;
}

int estaVazia(Arvore* a){
	return (a == NULL);
}

Arvore* menor(Arvore *a){
	if(estaVazia(a))
		return NULL;
	else if (!estaVazia(a->esq))
		return menor(a->esq);
	else
		return a;
}

Arvore* maior(Arvore *a){
	if (estaVazia(a)){
		printf("Vazia!");
		return NULL;
	}
	else if(!estaVazia(a->dir))
		return maior(a->dir);
	else
		return a;
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
		else if(v > a->info)
			a->dir = insere(a->dir,v);
	}
	return a;
}

int quantidade_nos(Arvore *a){
	if(estaVazia(a))
		return 0;
	else
		return 1 + quantidade_nos(a->dir);
}

Arvore* criarArvoreVazia(){
	return NULL;
}


Arvore* remover(Arvore* a,int v){
	if(estaVazia(a))
		return NULL;
	else{
		if(v < a->info)
			a-> esq = remover(a->esq,v);
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

void balancear(Arvore *a){
	if(!estaVazia(a)){
		int nosdir = quantidade_nos(a->dir);
		int nosesq = quantidade_nos(a->esq);
		if (nosdir >= nosesq + 2){
			a->esq = insere(a->esq, a->info);
			Arvore *m = menor(a->dir);
			a->info = m->info;
			a->dir = remover(a->dir, m->info);
		}
		else if (nosdir+2 <= nosesq){
			a->dir = insere(a->dir, a->info);
			Arvore *m = maior(a->esq);
			a->info = m->info;
			a->esq = remover(a->esq, m->info);
		}
	}
	else
		printf("Vazia!");
}

int main(){
	Arvore *a = criarArvoreVazia();
	insere(a, 5);
	insere(a, 7);
	insere(a, 9);
	return 0;
}
