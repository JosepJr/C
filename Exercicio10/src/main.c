#include <stdio.h>

	int soma_serie(int i, int j, int k){
		if (i / j == 1)
				return j;
		else if (i > j)
			return 0;
		else
			return i + soma_serie(i+k, j, k);
	}

int main(void){
	int i,j,k;
	scanf("%d %d %d", &i, &j, &k);
	printf("%d", soma_serie(i, j, k));
	return 0;
}
