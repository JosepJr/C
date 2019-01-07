#include <stdio.h>
#include <stdlib.h>

void quicksort(int *vet, int inicio, int fim){
    int pivo;
    if (pivo > inicio){
        pivo = particiona(vet, inicio, fim);
        quicksort(vet, inicio, pivo-1);
        quicksort(vet, pivo+1, fim);
    }
}

int particiona(int *vet, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq = incio;
    dir = fim;
    pivo = vet[inicio];
    while(esq < dir){
        while(vet[esq] <= pivo)
            esq++;
        while(vet[dir] > pivo)
            dir--;
        if (esq < dir){
            aux = vet[esq];
            vet[esq] = vet[dir];
            vet[dir] = aux;
        }
    }
    vet[inicio] = vet[dir];
    vet[dir] = pivo;
    return dir;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
