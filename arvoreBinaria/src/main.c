#include<stdlib.h>
#include<stdio.h>

typedef struct arv{
	char info;
	struct arv* sae;
	struct arv* sad;
}Arvore;

Arvore* criarArvoreVazia(){
	return NULL;
}

Arvore* criarArvore(char c, Arvore* esq, Arvore* dir){
	Arvore* a = malloc(sizeof(Arvore));
	if(a != NULL){
		a->info = c;
		a->sae = esq;
		a->sad = dir;
	}
	return a;
}

int estaVazia(Arvore* arv){
	return(arv == NULL);
}

void imprime(Arvore* a){
	if(!estaVazia(a)){
		printf("%c ", a->info);
		imprime(a->sae);
		imprime(a->sad);
	}
}

void imprimeNotacao(Arvore* a){
	printf("<");
	if(!estaVazia(a)){
		printf("%c ", a->info);
		imprimeNotacao(a->sae);
		imprimeNotacao(a->sad);
	}
	printf(">");
}

Arvore* copia_normal(Arvore *a){
	if (estaVazia(a)){
		return NULL;
	}
	else{
		Arvore *copia = criarArvore(a->info, NULL, NULL);
		copia->sae = copia_normal(a->sae);
		copia->sad = copia_normal(a->sad);
		return copia;
	}
}

Arvore* copiaEspelhada(Arvore *a){
	if(estaVazia(a))
		return NULL;
	else{
		Arvore *copia = criarArvore(a->info,  NULL, NULL);
		copia->sae = copiaEspelhada(a->sad);
		copia->sad = copiaEspelhada(a->sae);
		return copia;
	}
}

int maior(Arvore *a){
	static int m;
	if(estaVazia(a))
		return -1;
	else{
		m = a->info;
		maior(a->sae);
		maior(a->sad);
		if (a->info > m)
			m = a->info;
	}
	return m;
}

int iguais(Arvore *a, Arvore *b){
	if(estaVazia(a) && estaVazia(b))
		return 1;
	else if (estaVazia(a) || estaVazia(b))
		return 0;
	else{
		if(a->info != b->info)
			return 0;
		else{
			return(iguais(a->sae, b->sae) && iguais(a->sad, b->sad));
		}
	}
}

Arvore* liberar(Arvore* a){
	if(!estaVazia(a)){
		liberar(a->sae);
		liberar(a->sad);
		free(a);
	}
	return NULL;
}

int pertence (Arvore* a, char c){
	if(estaVazia(a)){
		return 0;
	}else{
		return (a->info == c || pertence(a->sae,c) || pertence(a->sad,c));
	}
}

int num_nos(Arvore* a){
	if(estaVazia(a)){
		return 0;
	}else{
		return (1 + num_nos(a->sad) + num_nos(a->sad));
	}
}

int altura(Arvore *a){
	if(estaVazia(a))
		return -1;
	else if (estaVazia(a->sae) && estaVazia(a->sad))
		return 0;
	else{
	int he = altura(a->sae);
	int hd = altura(a->sad);
	if (he >= hd)
		return 1 + he++;
	else
		return 1 + hd++;
	}
}

int qtdeFolhas(Arvore* a){
	if(estaVazia(a))
		return 0;
	else if (estaVazia(a->sae) && estaVazia(a->sad))
		return 1;
	return qtdeFolhas(a->sae) + qtdeFolhas(a->sad);
}

int qtdeChar(Arvore* a, char c){
	if(estaVazia(a))
		return 0;
	else if(a->info == c)
		return 1;
	return qtdeChar(a->sae, c) + qtdeChar(a->sad, c);
}


int main(){
	Arvore* a;
	a = criarArvoreVazia();
	//Arvore* criarArvore(char c, Arvore* esq, Arvore* dir)
	Arvore* arvD = criarArvore('d',criarArvoreVazia(),criarArvoreVazia());
	Arvore* arvB = criarArvore('b',criarArvoreVazia(),arvD);
	Arvore* arvE = criarArvore('e',criarArvoreVazia(),criarArvoreVazia());
	Arvore* arvF = criarArvore('e',criarArvoreVazia(),criarArvoreVazia());
	Arvore* arvC = criarArvore('c',arvE,arvF);
	a = criarArvore('a',arvB,arvC);
	imprime(a);
	printf("\n");
	imprimeNotacao(a);
	printf("\n");
	int num = qtdeChar(a, 'e');
	printf("%d",num);
	return 0;
}

