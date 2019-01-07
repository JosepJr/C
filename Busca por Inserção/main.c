#include <stdio.h>
#include <stdlib.h>

void ordenacao(int *vet, int n){
    int k, i, aux;

    for (i = 1; i < n; i++){
        k = i;
        while(vet[k] < vet[k-1] && k > 0){
            aux = vet[k];
            vet[k] = vet[k-1];
            vet[k-1] = aux;
            k--;
        }
    }
}

void inversao(int *vet, int n){
    int k, i, aux;
    for(i = 1; i < n; i++){
        k = i;
        while(vet[k] > vet[k-1] && k > 0){
            aux = vet[k];
            vet[k] = vet[k-1];
            vet[k-1] = aux;
            k --;
        }
    }
}

int main(){

    int n, i;

    printf("Informe o tamanho do vetor a ser inserido e ordenado: ");
    scanf("%d", &n);

    int vet[n];

    printf("Informe o vetor para ordenacao:\n");
    for (i = 0; i < n; i++){
        printf("Posicao %d :", i+1);
        scanf("%d", &vet[i]);
    }

    printf("\n\n");

    printf("Ordenacao \n");
    ordenacao(vet, n);

    for (i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }

    printf("\n\n");
    printf("Inversao \n");

    inversao(vet, n);

    for (i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }

    return 0;
}
