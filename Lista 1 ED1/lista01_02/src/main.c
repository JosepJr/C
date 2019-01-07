/*
 * main.c
 *
 *  Created on: Dec 4, 2013
 *      Author: felipe
 */
#include <stdio.h>

//soma dos n primeiros numeros naturais impares
int soma_impares(int n){
	int i = 1, soma = 0, count = 0;

	while(count<n){
		soma += i;
		i+=2;
		count++;
	}

	return soma;
}

int main(){
	//testezinho suave na neve
	printf("%d\n", soma_impares(4));
	return 0;
}
