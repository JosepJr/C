/*
 * main.c
 *
 *  Created on: Dec 4, 2013
 *      Author: felipe
 */
#include <stdio.h>

typedef struct realtype{
	int left;
	int right;
}Real;

//letra a
void LeReal(Real *r){
	printf("\nDigite a parte inteira do numero real: ");
	fflush(stdout);
	scanf("%d", &r->left);

	printf("Digite a parte fracionaria do numero real: ");
	fflush(stdout);
	scanf("%d", &r->right);
}

//letra b
void ImprimeReal(Real *r){
	printf("\nNumero real: %d.%d", r->left, r->right);
	fflush(stdout);
}

//letra c
Real Soma(Real *r1, Real *r2)
{
	Real soma;
	soma.left = r1->left + r2->left;
	soma.right = r1->right + r2->right;
	return soma;
}

int main(){
	Real real1, real2, real3;
	LeReal(&real1);
	LeReal(&real2);
	real3 = Soma(&real1, &real2);

	ImprimeReal(&real1);
	ImprimeReal(&real2);
	ImprimeReal(&real3);
	return 0;
}
