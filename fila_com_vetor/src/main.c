#include <stdio.h>
#include <stdlib.h>

#define N 10

typedef struct fila{
	float info[N];
	int n;
	int inicio;
} Fila;

Fila* criar_fila(){
	Fila *f = (Fila *)malloc(sizeof(Fila));
	if (f != NULL){
		f->inicio = 0;
		f->n = 0;
	}
	return f;
}

int esta_cheia(Fila *f){
	return (f->n == N);
}

int esta_vazia(Fila *f){
	return (f->n == 0);
}

int incr(int i){
	return (i+1) % N;
}

void insere(Fila *f, float v){
	if (!esta_cheia(f)){
		int fim = (f->inicio + f->n) % N;
		f->info[fim] = v;
		f->n++;
	}
	else
		printf("Cheia!");
}

void imprimir(Fila *f){
	if (!esta_vazia(f)){
		int i, t = f->inicio;
		for (i=0; i < f->n; i++){
			printf("%.2f ", f->info[t]);
			t = incr(t);
		}
	}
	else
		printf("Vazia!");
}

float maior(Fila* f){
	float maior=0;
	if (!esta_vazia(f)){
		maior = f->info[f->inicio];
		int i;
		for (i=0; i < f->n; i++)
			if (f->info[i] >= maior)
				maior = f->info[i];
		return maior;
	}
	else
		printf("Vazia!");
	return maior;
}

float remover(Fila *f){
	if(!esta_vazia(f)){
		float v = f->info[f->inicio];
		f->n--;
		f->inicio = incr(f->inicio);
		return v;
	}
	else
		printf("Vazio!");
	exit(1);
}

void liberar_fila(Fila *f){
	free(f);
}

int main(void){
	Fila *f = criar_fila();
	insere(f, 5);
	insere(f, 7.5);
	insere(f, 15);
	insere(f, 15.5);
	imprimir(f);
	printf("Maior %.2f", maior(f));
	return 0;
}
