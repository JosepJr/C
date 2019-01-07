/*
 * main.c
 *
 *  Created on: Dec 4, 2013
 *      Author: felipe
 */

#include <stdio.h>

#define MAX 12

void Inverte(int n, int *v){
	int i, aux = 0;
	for(i = 0; i<n/2; i++)
	{
		aux = v[i]; //armazena o atual
		v[i] = v[n-1-i]; //troca atual pelo simetrico
		v[n-1-i] = aux;
		//printf("%d", v[i]);
	}
}

void Imprime(int n, int *v){
	int i;
	for(i=0; i<n; i++){
		printf("%d ", v[i]);
	}
}

int main(){
	int vetor[MAX] = {0,2,4,6,8,10,12,14,16,18, 20, 21};

	Imprime(MAX, vetor);
	printf("\n");

	Inverte(MAX, vetor); //vetor já é um endereço da primeira posicao
	Imprime(MAX, vetor);

	return 0;
}


