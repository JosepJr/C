/*
 * main.c
 *
 *  Created on: Dec 5, 2013
 *      Author: felipe
 */

#include <stdio.h>
#include<stdlib.h>

void shift_string(char *str){
	int i;
	for(i=0; str[i]!='\0'; i++){
		if(str[i] == 'Z')
			str[i] = 'A';
		else if(str[i] == 'z')
			str[i] = 'a';
		else
		str[i] = str[i] + 1;
	}
}

int main(){
	char string[81];
	printf("Digite uma string: ");
	fflush(stdout);
	scanf("%s", string);

	shift_string(string);
	printf("\n%s", string);
           
        system("pause");
	return 0;
}



