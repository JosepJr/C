#include <stdio.h>

int Potencia(int x, int y){
	if(y>1){	
	
		x = x * Potencia(x, y-1);
	}
	return x;
}

int main(){
	printf("%d", Potencia(2,3));

	return 0;
}