#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 264346

/*void CriarMatriz(int **Matriz, int DIM){
	int i, j;
    //criando a matriz
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
*/
int NumeroArcos(){
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

    int arcos, auxiliar, cont;
    arcos = 0;
    cont = 0;

    while( (fscanf(dados, "%d", &auxiliar)) != EOF){
        if(cont == 1){
           arcos = auxiliar;
            break;
        }
        cont ++;
    }

    fclose(dados);

    return arcos;
}

void PreencherMatriz(int *Matriz/*, int DIM*/){
    int linha = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    char auxiliar[250];
    char lixo1[50];
    char lixo2[50];
    char lixo3[50];
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }
    while((fgets(auxiliar, sizeof(auxiliar), dados))!= NULL ){
        if (linha > 1){

            char *temp = strtok(auxiliar,"-");

            strcpy(lixo1,temp);
            x = atoi(lixo1);

            temp = strtok(NULL,"-");
            strcpy(lixo2,temp);
            y = atoi(lixo2);

            temp = strtok(NULL,"\n");
            strcpy(lixo3,temp);
            z = atoi(lixo3);


            Matriz[x-1][y-1] = z;

        }
        linha++;
    }

    fclose(dados);
}

void dijkstra(int Matriz/*, int DIM*/){

   char vis[DIM];
   int dis[DIM];
   memset(vis, 0, sizeof(vis));
   memset(dis, 0x7f, sizeof(dis));

   int t, i, aux2;
   printf("Informe o vertice incial: ");
   scanf("%d", &aux2);

   if(aux2 > DIM || aux2 < 1){
        printf("Nao e possivel fazer o calculo de distancia pois a cidade inicial nao existe... ");
        getchar();
        exit(1);
   }

   dis[aux2-1] = 0;

   for(t = 0; t < DIM; t++){
        int v = -1;
        for(i = 0; i < DIM; i++){
            if(!vis[i] && (v < 0 || dis[i] < dis[v]))
                v = i;
        }
        vis[v] = 1;

        for(i = 0; i < DIM; i++){
            if(Matriz[v][i] && dis[i] > dis[v] + Matriz[v][i])
                dis[i] = dis[v] + Matriz[v][i];
        }
   }

    int lixo;
    printf("Informe o vertice do qual deseja saber a distancia do Inicial ate ele: ");
    scanf("%d", &lixo);
    printf("\n");

    if(lixo > DIM || lixo < 1){
        printf("Nao e possivel fazer o calculo de distancia pois a cidade de destino nao existe... ");
        getchar();
        exit(1);
   }

    if(dis[lixo-1] == 2139062143){
            printf("Nao existe rota entre a cidade incial e chegar no seu destino...");
            getchar();
            exit(1);
    }
    else
        printf("A distancia e: %d \n", dis[lixo-1]);


    /*for(i = 0; i < DIM; i++){
       printf("%d ", dis[i]);
    }*/

}

int main(){

    /*int DIM = DimencaoMatriz();
    int **Matriz;
    int *vet[DIM];

    Matriz = vet;*/
    //int DIM;
    //DIM = DimencaoMatriz();

    Matriz = new int (DIM)(DIM);



    printf("\n");
    printf("Quantidade de Arcos: %d \n", NumeroArcos());

    //criando a matriz
    //CriarMatriz(Matriz, DIM);

    //Preencher matriz com as arestas
    PreencherMatriz(Matriz);

    //imprime matriz
    //ImprimeMatriz(Matriz, DIM);



    dijkstra(Matriz);

    // liberando a matriz
	//LiberaMatriz(Matriz, DIM);


    return 0;
}
