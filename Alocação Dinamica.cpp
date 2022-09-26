/*Aloque dinamicamente espaço e receba ‘números’ digitados 
pelo usuário. O usuário poderá entrar com novos ‘números’, até 
que este escolha a opção N (Deseja continuar? (S/N)). Em 
seguida, determine a média e aloque espaço para os números 
menores e maiores que a média. Mostre na tela. Utilizar função 
para alocação dinâmica.*/
/*Exercice involving dinamic alocation on C++, perfomed with pointer - en-US*/

#include <stdio.h>
#include <stdlib.h>

void aloca(int **p, int tam);
void mostra(int *p, int tam);
void leitura(int *p);
void media(int *p, int **pm, int **pM, int *qm, int *qM, int tam);
main()
{
	char op;
	int *ptr=NULL, *pmenor=NULL, *pmaior=NULL, qmenor=0, qmaior=0, cont=0;
	do
	{
		aloca(&ptr, cont+1);
		leitura(ptr+cont);
		cont++;
		printf("\n\nDeseja continuar? S/N");
		scanf("%c", &op);
	}while(op!='N' && op!='n');
	printf("\nNumeros digitados:");
	mostra(ptr, cont);
	media(ptr,&pmenor,&pmaior, &qmenor, &qmaior, cont);
	printf("Numeros menores que a media:\n");
	mostra(pmenor, qmenor);
	printf("Numeros maiores que a media:\n");
	mostra(pmaior, qmaior);
	
}

void aloca(int **p, int tam)
{
	if((*p=(int*)realloc(*p, tam*sizeof(int)))==NULL)
	{
		printf("\nErro ao alocar\n");
		exit(1);
	}
}

void leitura(int *p)
{
	printf("\nNumero: ");
	scanf("%d", p);
	fflush(stdin);
}

void mostra(int *p, int tam)
{
	int i;
	for(i=0; i<tam; i++)
	{
		printf("%d\n", *(p+i));	
	}	
}

void media(int *p, int **pm, int **pM, int *qm, int *qM, int tam)
{
	int i=0;
	int med=0;
	for(i=0; i<tam; i++)
	{
		med+=*(p+i);
	}//media
	med/=tam;
	printf("%d", med);
	
	for(i=0; i<tam; i++)
	{
		if(*(p+i)<med)  //menores
			{
				aloca(pm, *qm+1);
				*(*pm+*qm)=*(p+i);
				(*qm)++;
			}
		if(*(p+i)>med) //maiores
		{
			aloca(pM, *qM+1);
			*(*pM+*qM)=*(p+i);
			(*qM)++;
		}	
	}
}
