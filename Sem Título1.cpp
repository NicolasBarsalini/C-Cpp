//Exercício 5
#include <stdio.h>

int main()
{
	char string1[6],stringrev[6];
	int i,j;
	printf("Digite uma palavra com 6 letras:");
	gets(string1);
	for(j=5,i=0;j<0,i<6;j--,i++)
			stringrev[i]=string1[j];
	printf("%s", stringrev);
}
