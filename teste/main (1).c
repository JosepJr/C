#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct arvore{
	char chave[30];
	int linha;
	struct arvore *esq;
	struct arvore *dir;
}Arvore;

Arvore *ArvoreVazia(){
    return NULL;
}

void imprime(Arvore *Arv){
	if(Arv != NULL){
		imprime(Arv->esq);
		printf("%s\n", Arv->chave);
		imprime(Arv->dir);
	}
	else
        printf("Arvore Vazia...");
}

void InserirChave(Arvore *Arv, char *chave, int linha){
    if(Arv==NULL){
        Arv = malloc(sizeof(Arvore));
        strcpy(Arv -> chave, chave);
        Arv -> linha = linha;
        Arv -> esq = NULL;
        Arv -> dir = NULL;
    }
    else
        if (strcmp(Arv -> chave, chave) < 0)
            InserirChave(Arv -> esq, chave, linha);
        else
            InserirChave(Arv -> dir, chave, linha);
}

void BuscaChave(Arvore *Arv, char *chave){
    if(Arv != NULL){
        if (strcmp(Arv->chave, chave) == -1)
            BuscaChave(Arv -> esq, chave);
        else{
            if(strcmp(chave, Arv -> chave) == 1){
                BuscaChave(Arv -> dir, chave);
			}
            else{
                int linha, i;
                i = 0;
                linha = Arv->linha;
                FILE *dados;
                dados = fopen("arquivo.txt", "r");

                if (dados == NULL){
                printf("Nao foi possivel Abrir o Arquivo!!\n");
                getchar();
                exit(0);
                }
                while(!feof(dados)){
                    i++;
                    if (i == linha){
                        char aux[250];
                        fscanf(dados,"%s",aux);
                        printf("%s", aux);
                    }
                }
                fclose(dados);
            }
        }

    }
    else
        printf("Arvore vazia... \n");
}

void LerdoArquivo(Arvore *ArvoreCod, Arvore *ArvoreNome, Arvore *ArvoreTel){
    int linha;
    linha = 0;
    char auxiliar[250];
    char cod[30];
    char nome[30];
    char telefone[30];

    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

	while((fgets(auxiliar, sizeof(auxiliar), dados))!=NULL ){

        linha++;

		char *temp = strtok(auxiliar,";");
        strcpy(cod,temp);
        printf("%s", cod);

        temp = strtok(NULL,";");
        strcpy(nome,temp);
        printf("%s", nome);

		temp = strtok(NULL,"\0");
        strcpy(telefone,temp);
        printf("%s\n", telefone);

        InserirChave(ArvoreCod, cod, linha);
        InserirChave(ArvoreNome, nome, linha);
        InserirChave(ArvoreTel, telefone, linha);

        printf("\n");
    }

    printf("linhas: %i\n", linha);
    fclose(dados);

}



int main(){

    //Arvore com os Codigos
    Arvore *ArvoreCod;
    ArvoreCod = ArvoreVazia();

    //Arvore com os nomes
    Arvore *ArvoreNome;
    ArvoreNome = ArvoreVazia();

    //Arvore com os telefones
    Arvore *ArvoreTel;
    ArvoreTel = ArvoreVazia();

    //Lendo os aquivos
    LerdoArquivo(ArvoreCod, ArvoreNome, ArvoreTel);

    printf("Arvore de Codigo:\n");
    imprime(ArvoreCod);
    printf("\n");

    printf("Arvore de Nome:\n");
    imprime(ArvoreNome);
    printf("\n");

    printf("Arvore de telefone:\n");
    imprime(ArvoreTel);
    printf("\n");

    int m;
    char chave[30];
    do{
        printf("--------------------------------------");
        printf("Informe o metodo que deseja buscar: \n");
        printf("1 - Codigo: \n");
        printf("2 - Nome: \n");
        printf("3 - Telefone: \n");
        printf("0 - Sair: \n");
        scanf("%d", &m);
        printf("--------------------------------------");
        printf("\n\n");
        if (m == 1){
            printf("Insira o Codigo para a busca: ");
            scanf(" %s", chave);
            BuscaChave(ArvoreCod, chave);
        }
        if (m == 2){
            printf("Insira o Nome para a busca: ");
            scanf(" %s", chave);
            BuscaChave(ArvoreNome, chave);
        }
        if (m == 3){
            printf("Insira o telefone para a busca: ");
            scanf(" %s", chave);
            BuscaChave(ArvoreTel, chave);
        }
    }
    while( m != 0);
    return 0;
}
