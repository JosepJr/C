#include <stdio.h>
#include <stdlib.h>

int ForcaBruta(char *Texto, char *Palavra, int TamanhoTexto, int TamanhoPalavra){
    int i, k, j;

    for ( i = 0; i < TamanhoTexto; i++){
        j = 0;
        k = i;
        while(Texto[k] == Palavra[j] && j < TamanhoPalavra){
            j++;
            k++;
            if (j == TamanhoPalavra)
                return i;
        }
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

    printf("Informe uma String de %d caracteres para definir o padrao : ", TamanhoPalavra);
    scanf(" %[^\n]", Palavra);

    printf("\n\n");
    printf("Sua Palavra e: %s", Palavra);
    printf("\n\n");

    printf("%d", ForcaBruta(Texto, Palavra, TamanhoTexto, TamanhoPalavra));

    return 0;
}
