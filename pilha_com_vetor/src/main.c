/*/              Pilhas!
 *
 *  Estruturas de Dados mais simples;
 *  Restrição de Lista;
 *  Regra de acesso: - Insere no Topo.
 *  				 - Remove do Topo.
 *  				 - Busca a partir do Topo.
 *  Ultimo a entrar é o ultimo a sair. ("Last In. Last out.");
 *
 *  Exemplo: Avaliação de expressões aritméticas;
 *  		 Alocação de memória;
 *
 *
 *  Implementação: - Vetor.
 *  			   - Lista;
 *
 *	  @ push(empilhar) - pop(desempilhar) : retorna o elemento @
 *
 *	   ---
 *	  |   | n
 *	   ---
 *	   ...
 *	  |   | 0
 *	   ---
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct pilha{
	float info[MAX];
	int n;
} Pilha;

Pilha* criar_pilha(){
	Pilha *p = (Pilha *)malloc(sizeof(Pilha));
	p->n=0;
	return p;
}

int estaCheia(Pilha *p){
	return (p->n == MAX);
}

int estaVazia(Pilha *p){
	return (p->n == 0);
}

void Push(Pilha *p, float v){
	if (!estaCheia(p)){
		p->info[p->n] = v;
		p->n++;
	}
	else
		printf("Pilha Cheia!");
}

void imprime_pilha(Pilha *p){
	if (!estaVazia(p)){
		int i;
		for (i=p->n-1; i >= 0; i--)
			printf("%.2f ", p->info[i]);
		printf("\n");
	}
	else
		printf("Pilha Vazia!");
}

float Pop(Pilha *p){
	float aux=0;
	if (!estaVazia(p)){
		aux = p->info[p->n-1];
		p->n--;
	}
	else
		printf("Pilha Vazia!");
	return aux;
}

float ver_topo(Pilha *p){
	return (p->info[p->n-1]);
}

void liberar_pilha(Pilha *p){
	if (!estaVazia(p)){
		free(p);
	}
	else
		printf("Pilha Vazia!");
}

void concatenaPilha(Pilha *p1, Pilha *p2){
	if(!estaVazia(p2)){
		int i;
		for(i=0; i < p2->n; i++){
			p1->info[p1->n] = p2->info[i];
			p1->n++;
		}
		p2->n = 0;
	}
}

int main(void){
	Pilha *p = criar_pilha();
	Pilha *p2 = criar_pilha();
	Push(p, 5.5);
	Push(p, 10);
	Push(p2, 7);
	Push(p2, 8.7);
	imprime_pilha(p);
	imprime_pilha(p2);
	concatenaPilha(p,p2);
	imprime_pilha(p);
	//liberar_pilha(p);
	imprime_pilha(p2);
	return 0;
}
