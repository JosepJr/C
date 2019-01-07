#include <stdio.h>
#include <stdlib.h>

void ShellSort(int *vet, int n){
    int i, h, aux;

    h = (n/2)+1;
    while (h > 0){
        for(i = h; i < n; i++){
            if(vet[i-h] > vet[i]){
                aux = vet[i-h];
                vet[i-h] = vet[i];
                vet[i] = aux;
            }
        }
        h--;
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

    printf("Ordenacao por metodo Shell: \n");

    ShellSort(vet, n);

    printf("\n\n");

    for (i = 0; i < n; i++){
        printf("%d ", vet[i]);
    }
    return 0;
}
