#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 250

int RetornaGrupo(){
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

    char auxiliar[MAX];
    char lixo[MAX];
    int GrupoAmigos, cont;
    GrupoAmigos = 0;
    cont = 0;

    while((fgets(auxiliar, sizeof(auxiliar), dados))!= NULL ){
        if(cont == 0){
            char *temp = strtok(auxiliar," ");
            strcpy(lixo,temp);
            GrupoAmigos = atoi(lixo);
            break;
        }
        cont ++;
    }

    fclose(dados);

    return GrupoAmigos;
}

int RetornaQtdMesas(){
    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }

    char auxiliar[MAX];
    char lixo[MAX];
    int QuantidadeMesas, cont;
    QuantidadeMesas = 0;
    cont = 0;

   while((fgets(auxiliar, sizeof(auxiliar), dados))!= NULL ){
        if(cont == 0){
            char *temp = strtok(auxiliar," ");
            temp = strtok(NULL,"\n");
            strcpy(lixo,temp);
            QuantidadeMesas = atoi(lixo);

            break;
        }
        cont ++;
    }

    fclose(dados);

    return QuantidadeMesas;
}

void PreencherVets(int *VetGrupos, int *VetMesas){

    int linha = 0;
    int i = 0;
    int j = 0;

    FILE *dados;
    dados = fopen("arquivo.txt", "r");

    if (dados == NULL){
        printf("Nao foi possivel Abrir o Arquivo!!\n");
        getchar();
        exit(0);
    }
    char buffer[MAX];
    while (fgets(buffer, sizeof(buffer), dados)!= NULL){
        if(linha == 1){
            char *temp = strtok(buffer," ");
            while(temp != NULL){
                VetGrupos[i] = atoi(temp);
                i++;
                temp = strtok(NULL," ");
            }
        }
        if(linha == 2){
            char *temp = strtok(buffer," ");
            while(temp != NULL){
                VetMesas[j] = atoi(temp);
                j++;
                temp = strtok(NULL," ");
            }

        }
        linha++;;
    }
    fclose(dados);
}

void OrdenaMesas(int* VetMesas, int mesas){
	int i,j, aponta;
	for(i=mesas-1;i>=1;i--){
		for(j=0;j<i;j++){
			if(VetMesas[j]<VetMesas[j+1]){
				aponta=VetMesas[j];
				VetMesas[j]=VetMesas[j+1];
				VetMesas[j+1]=aponta;
			}
		}
	}
}
void Ordena(int *vet, int size){
    int i , j , value;
    int gap = 1;
    while(gap < size) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i - gap;
            while (j >= 0 && value < vet[j]) {
                vet [j + gap] = vet[j];
                j -= gap;
            }
            vet [j + gap] = value;
        }
    }




}

void ResultadoProblema(int *VetGrupos, int Grupos, int *VetMesas, int Mesas){
  int i,j=0;
  //SE TEM ALGUM GRUPO COM MAIS INTEGRANTES QUE O NUMERO DE MESAS O SECOMP FRACASSOU
  for(i=0;i<Grupos;i++){
	if(VetGrupos[i]>Mesas){
		printf("FRACASSOU... \n");
		getchar();
		exit(0);
	}
  }

 for(i=0;i<Mesas;i++){
	if(VetGrupos[j]!=0){
		if(VetMesas[i]!=0){
			 VetGrupos[j]=VetGrupos[j]-1;
			VetMesas[i]=VetMesas[i]-1;
		}
		else{
			printf("FRACASSOU... \n");
			getchar();
			exit(0);
		}

	}
	 else if((VetGrupos[j]==0) && j!=(Grupos-1)){
		 j++;
		 i=-1;
		}

	}
		//SE O PROGRAMA AINDA NAO FRACASSOU E J APONTA PRA ULTIMA POSIÇÃO SIGNIFICA QUE FOI POSSIVEL ESVAZIAR O VETOR DE GRUPOS
		//INCLUSIVE O VETOR DE GRUPOS NA POSIÇÃO J É 0 PORTANDO PARABENS SECOMP:)
	if(j==Grupos-1){
			printf("PARABENS SECOMP... \n");
		}
}
int main(){

    int Grupos;
    int Mesas;
    int i;

    Grupos = RetornaGrupo();
    Mesas = RetornaQtdMesas();

    int VetMesas[Mesas];
    int VetGrupos[Grupos];

    PreencherVets(VetGrupos, VetMesas);

    Ordena(VetGrupos, Grupos);
    OrdenaMesas(VetMesas, Mesas);

    ResultadoProblema(VetGrupos, Grupos, VetMesas, Mesas);

    return 0;
}
