//Aluno: Jose Paulo de Amorim Junior
//Matricula: 2012204304


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 250

typedef struct no{
	int info;
	struct no *prox;
} NoLista;

typedef struct pilha{
	NoLista *prim;
} Pilha;

Pilha* criar_pilha(){
	Pilha *p = (Pilha*)malloc(sizeof(Pilha));
	p -> prim = NULL;
	return p;
}

int EstaVazia(Pilha* p){
	return (p -> prim == NULL);
}

void push(Pilha *p, int v){
	NoLista *novo = (NoLista *)malloc(sizeof(NoLista));
	if (novo != NULL){
        novo -> info = v;
		novo -> prox = p -> prim;
		p -> prim = novo;
	}
	else
		printf("Erro!");
}

void pop(Pilha *p){
	if(!EstaVazia(p)){
		NoLista *aux = p -> prim;
		p -> prim = p -> prim -> prox;
		free(aux);
	}
	else
		printf("Pilha Vazia!");
}

void liberarPilha(Pilha* p){
    NoLista* q;
    q = p -> prim;
    while(q!=NULL){
        NoLista* temp;
        temp = q -> prox;
        free(q);
        q = temp;
    }
    free(p);
}

void imprime(Pilha *p){
	if(!EstaVazia(p)){
		NoLista* aux;
		for(aux = p -> prim; aux != NULL; aux = aux -> prox)
			printf("%d ", aux -> info);
	}
	else
		printf("Pilha Vazia!");
}


int main(){

    Pilha *p = criar_pilha();
    push(p, -1);

    char w[MAX];
    int TamanhoPalavra;
    int aux;
    int i = 0;



    printf("Considerando o Alfabeto de entrada [0,1]*,\n");
    printf("onde o numero de 0's em w e igual ao numero de 1's:\n\n");
    printf("OBS: Considere 'enter' como o simbolo de entrada 'epslon'(0^01^0). \n");
    printf("Informe a palavra a ser analizada: ");

    fgets(w,MAX,stdin);

    printf("\n");

    TamanhoPalavra = strlen(w);

    if((TamanhoPalavra == 1) && (w[0] == '\n')){
        printf("Simbolo 'epslon' identificado!!!\n");
        printf("Palavra aceita com sucesso... \n");
        getchar();
        exit(1);
    }
    else{
        for(i = 0; i < TamanhoPalavra-1; i++){
            aux = (w[i] - 48);
            switch(aux){
                case 0:
                    if(p -> prim -> info == -1){
                        push(p, aux);
                    }
                    else{
                        if (p -> prim -> info == 0){
                            push(p, aux);
                        }
                        else
                            pop(p);
                        }
                break;
                case 1:
                    if(p -> prim -> info == -1){
                        push(p, aux);
                    }
                    else{
                        if (p -> prim -> info == 1){
                            push(p, aux);
                        }
                        else
                            pop(p);
                    }
                break;
                default:
                    printf("Palavra nao aceita... \n");
                    getchar();
                    exit(1);
                }
            }
    }
    if(p -> prim -> info != -1){
        printf("Palavra nao aceita... \n");
        getchar();
    }
    else{
        printf("Palavra aceita com sucesso... \n");
        getchar();
    }

    //imprime(p);
    liberarPilha(p);

    return 0;
}
