#include <stdio.h>
#include <stdlib.h>
#define maximochar 256

int BMH(char *Texto, char *Palavra, int TamanhoTexto, int TamanhoPalavra){

    int tabela[maximochar];
    int j, k, i;

    for (j = 0; j < maximochar; j++)
        tabela[j] = TamanhoPalavra;
    for (j = 1; j < TamanhoPalavra; j++)
        tabela[Palavra[j-1]] = TamanhoPalavra - j;

    i = TamanhoPalavra;

    while(i <= TamanhoTexto){
        k = i;
        j = TamanhoPalavra;
        while(Texto[k-1] == Palavra[j-1] && j > 0){
            k = k - 1;
            j = j - 1;
        }
        if (j == 0)
            return k+1;
        i = i + tabela[Texto[i-1]];
    }
    return -1;
}

int main(){
    int TamanhoPalavra, TamanhoTexto;

/* ---------------------------- Informações do Texto ----------------------------------------*/
    printf("Informe o tamanho do texto que deseja realizar a buscar: ");
    scanf("%d", &TamanhoTexto);

    char Texto[TamanhoTexto];

    printf("Informe o texto de %d caracteres para definir o padrao : ", TamanhoTexto);
    scanf(" %[^\n]", Texto);

    printf("\n\n");
    printf("Seu texto e: %s", Texto);
    printf("\n\n");

/* ---------------------------- Informações da String ----------------------------------------*/
    printf("Informe o tamanho do padrao da palavra que deseja buscar: ");
    scanf("%d", &TamanhoPalavra);

    char Palavra[TamanhoPalavra];

    printf("Informe a palavra padrao de %d caracteres: ", TamanhoPalavra);
    scanf(" %[^\n]", Palavra);

    printf("\n\n");
    printf("Sua Palavra e: %s", Palavra);
    printf("\n\n");

    printf("%d", BMH(Texto, Palavra, TamanhoTexto, TamanhoPalavra));

    return 0;
}
