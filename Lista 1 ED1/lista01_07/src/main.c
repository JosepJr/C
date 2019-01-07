/*
 * main.c
 *
 *  Created on: Dec 5, 2013
 *      Author: felipe
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* shift_string(char *str){
	int i;
	char *nova = malloc(strlen(str)*sizeof(char));
	for(i=0; str[i]!='\0'; i++){
		if(str[i] == 'Z')
			nova[i] = 'A';
		else if(str[i] == 'z')
			nova[i] = 'a';
		else
			nova[i] = str[i] + 1;
	}

	return nova;
}

int main(){
	char string[81];
	printf("Digite uma string: ");
	fflush(stdout);
	scanf("%s", string);

	char string2[81];
	*string2 = (int)shift_string(string);

	printf("\n%s", string);
	fflush(stdout);
	printf("\n%s", string2);
	return 0;
}



