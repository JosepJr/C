/*
 * main.c
 *
 *  Created on: Dec 4, 2013
 *      Author: felipe
 */
#include <stdio.h>

int Primo(int n){
	int i;
	for(i = 2; i<n; i++){
		if(n % i == 0)
		{
			return 0;
		}
	}
	return 1;
}

int main(){

	//verificando os primos de 1 a 100
	int i;
	for(i=1; i<101; i++)
	{
		printf("%d: %d\n", i, Primo(i));
	}

	return 0;
}
