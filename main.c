#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Aluno: José Paulo de Amorim Júnior
// Matricula: 2012204304
// Prof: Elder
// Estrutura de Dados II

typedef struct arvore{
	char chave[30];
	int linha;
	struct arvore *esq;
	struct arvore *dir;
}Arvore;

Arvore *ArvoreVazia(){
    return NULL;
}

void InserirChave(Arvore **Arv, char *chave, int linha){
    if(*Arv==NULL){
        *Arv = malloc(sizeof(Arvore));
        strcpy((*Arv) -> chave, chave);
        (*Arv) -> linha = linha;
        (*Arv) -> esq = NULL;
        (*Arv) -> dir = NULL;
    }
    else
        if (strcmp(chave, (*Arv) -> chave) == -1)
            InserirChave((&(*Arv) -> esq), chave, linha);
        else
            InserirChave((&(*Arv) -> dir), chave, linha);
}

void BuscaChave(Arvore **Arv, char *chave){
    if(*Arv != NULL){
        if (strcmp(chave, (*Arv)->chave) == -1)
            BuscaChave((&(*Arv) -> esq), chave);
        else{
            if(strcmp(chave, (*Arv)->chave) == 1){
                BuscaChave((&(*Arv)-> dir), chave);
			}
            else{
                int linha, i;
                i = 0;
                linha = (*Arv)->linha;
                FILE *dados;
                dados = fopen("arquivo.txt", "r");

                if (dados == NULL){
                printf("Nao foi possivel Abrir o Arquivo!!\n");
                getchar();
                exit(0);
                }
                char aux[250];
                while((fgets(aux, sizeof(aux), dados))!=NULL ){
                    i++;
                    if (i == linha){
                        printf("Elemento encontrado...\n\n");

                        char *temp = strtok(aux,";");
                        printf("Codigo: %s\n", temp);

                        temp = strtok(NULL,";");
                        printf("Nome: %s\n", temp);

                        temp = strtok(NULL,"\n");
                        printf("Telefone: %s\n", temp);

                        break;
                    }
                }
                fclose(dados);
            }
        }
    }
    else
        printf("Elemento nao encontrado... \n");
}

void LerdoArquivo(Arvore **ArvoreCod, Arvore **ArvoreNome, Arvore **ArvoreTel){
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

        temp = strtok(NULL,";");
        strcpy(nome,temp);

		temp = strtok(NULL,"\n");
        strcpy(telefone,temp);

        InserirChave(&(*ArvoreCod), cod, linha);
        InserirChave(&(*ArvoreNome), nome, linha);
        InserirChave(&(*ArvoreTel), telefone, linha);
    }

    fclose(dados);

}

int main(){

    Arvore *ArvoreCod;
    ArvoreCod = ArvoreVazia();

    Arvore *ArvoreNome;
    ArvoreNome = ArvoreVazia();

    Arvore *ArvoreTel;
    ArvoreTel = ArvoreVazia();

    LerdoArquivo(&ArvoreCod, &ArvoreNome, &ArvoreTel);

    int m;
    char chave[30];
    do{
        printf("\n\n");
        printf("---------------         Menu Principal        ---------------\n");
        printf("1 - Codigo: \n");
        printf("2 - Nome: \n");
        printf("3 - Telefone: \n");
        printf("0 - Sair: \n");
        printf("--------------- Informe a opcao de pesquisa ---------------\n");
        printf("\n");
        scanf("%d", &m);
        printf("\n");
        switch(m){
            case 1:
                printf("Insira o Codigo para a busca: ");
                scanf(" %s", chave);
                BuscaChave(&ArvoreCod, chave);
                getchar();
                break;
            case 2:
                printf("Insira o Nome para a busca: ");
                scanf(" %s", chave);
                BuscaChave(&ArvoreNome, chave);
                getchar();
                break;
            case 3:
                printf("Insira o telefone para a busca: ");
                scanf(" %s", chave);
                BuscaChave(&ArvoreTel, chave);
                getchar();
                break;
            case 0:
                printf("Obrigado pela atencao, Volte sempre... Fim!\n\n");
                exit(0);
            default :
                printf(" Opcao invalida... \n");
                getchar();

        }
    }
    while(m != 0);
    return 0;
}
