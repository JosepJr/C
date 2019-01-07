#include <stdio.h>


int soma_serie(int i, int j, int k){

	if(i<j)
	{
	   i = i + soma_serie(i+k, j, k);
	}

	return i;
}

int main(){

	printf("%d", soma_serie(2,8,3));

}