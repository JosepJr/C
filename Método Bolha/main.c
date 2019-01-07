#include <stdio.h>
#include <stdlib.h>

void bolha(int *vet, int n){
    int continua, fim, i, aux;
    fim = n;

    do{
        continua = 0;
        for(i = 0; i < (fim - 1); i++){
            if(vet[i] > vet[i+1]){
                aux = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = aux;
                continua = i;
            }
        }
        fim--;
    }
    while(continua != 0);
}


int main(){

    int n, i;

    printf("Informe o tamanho do vetor a ordenar: ");
    scanf("%d", &n);

    int vet[n];

    printf("Informe os elementos do vetor a ordenar: \n");
    for (i = 0; i < n; i++){
        printf("Elemento %d: ", i+1);
        scanf("%d", &vet[i]);
    }

    bolha(vet, n);






    return 0;
}
