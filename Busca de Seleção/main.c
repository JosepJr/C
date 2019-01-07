#include <stdio.h>
#include <stdlib.h>

void selecao(int *vet, int n){
    int i, j, aux, menor;
    for (i = 0; i < n ; i++){
        menor = i;
        for (j = i+1; j < n; j++){
            if(vet[j] < vet[menor])
                menor = j;
        }
        if (i != menor){
            aux = vet[i];
            vet[i] = vet[menor];
            vet[menor] = aux;
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

    printf("Ordenacao por Selecao: \n");
    selecao(vet, n);

    printf("\n\n");

    for (i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }
    return 0;
}
