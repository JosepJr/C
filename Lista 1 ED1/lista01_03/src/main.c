/*
 * main.c
 *
 *  Created on: Dec 4, 2013
 *      Author: felipe
 */
#include <stdio.h>
#include <math.h>

double Pi(int n){
	int i;
	double pi = 0;

	for(i=0; i<n; i++){
		pi += pow(-1,i)/(2*i + 1);
	}
	return 4*pi;

}

int main(){
	int pi;
	printf("Digite o numero de termos pra aproximar pi: ");
	fflush(stdout);
	scanf("%d", &pi);

	printf("%f\n", Pi(pi));
        return 0;
}
