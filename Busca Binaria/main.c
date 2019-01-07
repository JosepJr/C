#include <stdio.h>
#include <stdlib.h>

int BuscaBinaria(int *v, int k, int n){
    int baixo = 0;
    int alto = n;
    int meio;

    while (baixo <= alto){
        meio = ((baixo + alto)/2);
        if (k < v[meio])
            alto = (meio - 1);
        else{
            if (k > v[meio])
                baixo = (meio + 1);
            else
                return v[meio];
        }
    }
    return -1;
}


int Busca(int *v, int k, int n){
    int i;
    for (i = 0; i < n; i++){
        if (v[i] == k)
            return k;
    }
    return -1;
}

int main()
{
    int k, n, i;

    printf("Informe o tamanho do vetor: ");
    scanf("%d", &n);

    int v[n];

    printf("\n\n");

    printf("Informe os valores para preencher o vetor: \n");

    for (i = 0; i < n; i++){
        printf("Valor %d:", i+1);
        scanf("%d", &v[i]);
    }

    for (i = 0; i < n; i++){
        printf("%d\n",v[i]);
    }

    printf("Informe o valor que deseja buscar: ");
    scanf("%d", &k);

    printf("\n");
    printf("%d", BuscaBinaria(v, k, n));

    return 0;
}
