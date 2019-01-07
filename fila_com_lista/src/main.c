#include<stdlib.h>
#include<stdio.h>

typedef struct no{
	float info;
	struct no* prox;
}NoLista;

typedef struct fila{
	NoLista* ini;
	NoLista* fim;
}Fila;

Fila* criarFila(){
	Fila* f = malloc(sizeof(Fila));
	if(f != NULL){
		f->ini = NULL;
		f->fim = NULL;
	}
	return f;
}

int estaVazia(Fila* f){
	return(f->ini == NULL);
}

void insereElemento(Fila* f, float v){
	NoLista* n = malloc(sizeof(NoLista));
	if(n != NULL){
		n->info = v;
		n->prox = NULL;
		if(f->fim != NULL){
			f->fim->prox = n;
			f->fim = n;
		}else{
			f->ini = n;
			f->fim = n;
		}
	}else{
		exit(1);
	}
}

void imprime(Fila* f){
	if(!estaVazia(f)){
		NoLista* p;
		for(p = f->ini; p != NULL; p = p->prox){
			printf("%.2f ", p->info);
		}
	}else{
		printf("A fila está vazia");
	}
	printf("\n");
}

float removerElemento(Fila* f){
	NoLista* p;
	if(!estaVazia(f)){
		int n = f->ini->info;
		p = f->ini;
		f->ini = f->ini->prox;
		if(f->ini == NULL){
			f->fim = NULL;
		}
		free(p);
		return n;
	}else{
		printf("Fila está vazia");
		exit(1);
	}
}

void liberarFila(Fila* f){
	NoLista* p = f->ini, *aux;
	while(p != NULL){
		aux = p->prox;
		free(p);
		p = aux;
	}
	free(f);
}

void furarFila(Fila* f, float v){
	NoLista* ant = NULL;
	NoLista* p;
	if(!estaVazia(f)){
		for(p = f->ini; p != NULL && p->info != v; p = p->prox){
			ant = p;
		}
		if(ant != NULL){
			if(p->prox == NULL){
				ant->prox = NULL;
				f->fim = ant;
			}else{
				ant->prox = p->prox;
			}
			p->prox = f->ini;
			f->ini = p;
		}
	}else{
		printf("Fila vazia");
		exit(1);
	}
}

/*/void combinaFilas(Fila* f_res, Fila* f1, Fila* f2){
	while(!estaVazia(f1) || !estaVazia(f2)){
		if(!estaVazia(f1) && !estaVazia(f2)){
			insereElemento(f_res, removerElemento(f1));
			insereElemento(f_res, removerElemento(f2));
		}
		else{
			if(!estaVazia(f2)){
				insereElemento(f_res, removerElemento(f2));
			}
			else if (!estaVazia(f1)){
				insereElemento(f_res, removerElemento(f1));
			}
		}
	}
}/*/

void combinaFilas(Fila* f_res, Fila* f1, Fila* f2){
	if(!estaVazia(f1) && !estaVazia(f2)){
		float um = removerElemento(f1);
		float dois = removerElemento(f2);
		combinaFilas(f_res, f1, f2);
		NoLista *aux = (NoLista *)malloc(sizeof(NoLista));
		aux->info = um;
		aux->prox = NULL;
		f_res->fim->prox = aux;
		NoLista *aux2 = (NoLista *)malloc(sizeof(NoLista));
		aux2->info = dois;
		aux2->prox = NULL;
		f_res->fim->prox = aux2;
	}
	else{
		if(!estaVazia(f1)){
			float um = removerElemento(f1);
			combinaFilas(f_res, f1, f2);
			NoLista *aux = (NoLista *)malloc(sizeof(NoLista));
			aux->info = um;
			aux->prox = NULL;
			f_res->fim->prox = aux;

		}
		else if(!estaVazia(f2)){
			float dois = removerElemento(f2);
			NoLista *aux2 = (NoLista *)malloc(sizeof(NoLista));
			aux2->info = dois;
			aux2->prox = NULL;
			f_res->fim->prox = aux2;
		}
	}
}

float maior(Fila* f){
	float n;
	if(!estaVazia(f)){
		NoLista* p;
		for(p = f->ini; p != NULL; p = p->prox){
			if(p->prox == NULL)
				n = p->info;
			else if(p->info > p->prox->info)
				n = p->info;

		}
	}else
		printf("Fila Vazia!");
	return n;
}

int main(){
	Fila* f = criarFila();
	Fila *f2 = criarFila();
	Fila *f3 = criarFila();
	insereElemento(f,2.1);
	insereElemento(f,4.5);
	insereElemento(f,1.0);
	insereElemento(f2, 7.2);
	insereElemento(f2, 3.1);
	insereElemento(f2, 9.8);
	imprime(f);
	imprime(f2);
	combinaFilas(f3,f,f2);
	imprime(f3);
	//removerElemento(f);
	//imprime(f);
	//furarFila(f,5);
	//imprime(f);
	//float n = maior(f);
	//printf("%.2f",n);

	return 0;
}
