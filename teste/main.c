#include <stdio.h>
#include <stdlib.h>
#define DIM 2650
int main(){

    int i, j;
    int mat[DIM][DIM];

    for (i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            mat[i][j] = i+1;
        }
    }

   for (i = 0; i < DIM; i++){
        for(j = 0; j < DIM; j++){
            printf("%d ", mat[i][j]);
        }
    }
    return 0;
}
