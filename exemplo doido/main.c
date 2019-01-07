#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DimencaoMatriz(){
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

    int dimencao;

    fscanf(dados, "%d", &dimencao);

    fclose(dados);
    return dimencao;
}

void CriarMatriz(int **Matriz, int DIM){
	int i, j;
    for (i = 0; i < DIM; i++){
        Matriz[i] = (int *) malloc(DIM *sizeof(int));
        for (j = 0; j < DIM; j++){
            Matriz[i][j] = 0;
        }
    }
}

void ImprimeMatriz(int **Matriz, int DIM){
	int i, j;
    // Imprimindo a Matriz
    for (i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            printf("%d ", Matriz[i][j]);
        }
        printf("\n");
    }
}

void LiberaMatriz(int **Matriz, int DIM){
	int i;
    // liberando a matriz
    for (i = 0; i < DIM; i++){
        free(Matriz[i]);
    }
    free(*Matriz);
}

void PreencherMatriz(int **Matriz, int DIM){
    int linha = 0;
    int x = 0;
    int y = 0;
    char auxiliar[250];
    char lixo1[4];
    char lixo2[4];

    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }
    while((fgets(auxiliar, sizeof(auxiliar), dados))!= NULL ){
        if (linha > 0){

            char *temp = strtok(auxiliar,"-");

            strcpy(lixo1,temp);
            x = atoi(lixo1);

            temp = strtok(NULL,"\n");
            strcpy(lixo2,temp);
            y = atoi(lixo2);

            Matriz[x-1][y-1] = 1;
            Matriz[y-1][x-1] = 1;
        }
        linha++;
    }
    fclose(dados);
}

void CriarVetorDeCaminhos(int *Vetor, int DIM){
    int i;
    Vetor = (int *)malloc(DIM *sizeof(int));
    for (i = 0; i < DIM; i++){
        Vetor[i] = 0;
    }
}

void PreencherVetorCaminhos(int **Matriz, int *Vetor, int DIM){
    int i, j, cont;
    for (i = 0; i < DIM; i++){
        cont = 0;
        for(j = 0; j < DIM; j++){
            if(Matriz[i][j] == 1){
                    cont++;
            }
        }
        Vetor[i] = cont;
        printf("aujeauiheiwuaeuh");
    }
}

void LiberarVetor(int *Vetor){
    free(Vetor);
}

void SujestaoCidade(int *Vetor, int DIM){
    int i, cont;
    for (i = 0; i < DIM; i++){
        if(Vetor[i] > cont){
            cont = Vetor[i];
        }
    }
    printf("As Melhores sugestoes de cidades sao: \n");
    for(i = 0; i < DIM; i++){
        if(Vetor[i] == cont){
            printf("Cidade: %d\n", i+1);
        }
    }
    printf("\n\n");
}

void CaminhosCriticos(int **Matriz, int DIM){
     // Percorrendo a Matriz e preenchendo o vetor
    int vetaux[DIM];
    int i,j, cont;
    for (i = 0; i < DIM; i++){
        cont = 0;
        for(j = 0; j < DIM; j++){
            if(Matriz[i][j] == 1){
                    cont++;
            }
        }
        vetaux[i] = cont;
    }
    cont = 9999;
    for (i = 0; i < DIM; i++){
        if(vetaux[i] < cont){
            cont = vetaux[i];
        }
    }
    if(cont == 1){
        printf("Caminho(s) critico(s): \n");
        for(i = 0; i < DIM; i++){
            if(vetaux[i] == 1){
                for(j = 0; j < DIM; j++){
                    if(Matriz[i][j] == 1){
                        printf("%d - %d \n", i+1,j+1);
                    }
                }
            }
        }
    }
    else
        printf("Nao existem caminhos criticos!!! \n");
    printf("\n\n");
}

int main(){

    int DIM = DimencaoMatriz();

    int **Matriz;
    int *vet[DIM];
    Matriz = vet;

    //criando a matriz
    CriarMatriz(Matriz, DIM);

    //Preencher matriz com as arestas
    PreencherMatriz(Matriz, DIM);

    //Imprimir Matriz
    ImprimeMatriz(Matriz, DIM);

    //criando um vetor de caminhos
    int *Vetor;
    Vetor = NULL;
    CriarVetorDeCaminhos(Vetor, DIM);


    //preenecher vetor
    PreencherVetorCaminhos(Matriz, Vetor, DIM);

    //Respostas dos exercicios...
    SujestaoCidade(Vetor, DIM);
    CaminhosCriticos(Matriz, DIM);

    // liberando a matriz
	LiberaMatriz(Matriz, DIM);

	//Liberando Vetor
	LiberarVetor(Vetor);


    return 0;
}
