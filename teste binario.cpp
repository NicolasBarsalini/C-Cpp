/*
Dada a estrutura abaixo, implementar uma rotina de cadastro com alocação dinâmica,
deve-se consultar o usuário para continuar. Caso não deseje mais cadastrar, salve
todos os itens no arquivo (modo binário). O registro deve ser gerado automaticamente
pelo sistema. Não esquecer de conferir se já existem elementos armazenados em
arquivo, se sim, calcular o número do próximo registro. 
-->> Agora implemente uma função que permite alterar o nome ou a nota na agenda, ou
 deletar um registro (ou seja, substituir reg por -1) - assim, a partir de então, quando
surgir um novo cadastro, substituir no cadastro deletado (no arquivo).
Atenção: continue utilizando uma única alocação de espaço na memória.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct agenda{
int reg;
char nome[80];
float nota;
}agenda;

void alocaagenda(agenda **p, int tam);
void cadastraproduto(agenda *p);
int verifica();
void grava(agenda *p);
void mostra(agenda *p);
void altera(agenda *p, int op);
int busca(agenda *p, int numreg);
void atualiza(agenda *p, int pos);

main()
{
	agenda *p=NULL;
	int op;
	alocaagenda(&p, 1);
	do{
		system("cls");
		printf("Digite a opcao desejada:\n[1]Cadastro\n[2]Alterar\n[3]Deletar\n[4]Mostra\n[5]Fim\n");
		scanf("%d", &op);
		fflush(stdin);
		switch(op)
		{
			case 1:
				cadastraproduto(p);
				printf("Registro cadastrado com sucesso!\n\n");
				system("PAUSE");
				break;
			case 2:
				altera(p, op);
				break;
			case 3:
				altera(p, op);
				break;
			case 4:
				mostra(p);
				printf("\n\n");
				system("PAUSE");
				break;
		}
	}while(op!=5);
}//main

void alocaagenda(agenda **p, int tam)
{
	if((*p=(agenda*)realloc(*p, tam*sizeof(agenda)))==NULL)
		exit(1);
}//aloca

void cadastraproduto(agenda *p)
{
	int qtde = verifica();
	p->reg=qtde+1;
	printf("\nRegistro: %i\n", p->reg);
	printf("Nome: ");
	gets(p->nome);
	fflush(stdin);
	printf("\nNota: ");
	scanf("%f", &(p->nota));
	fflush(stdin);
	grava(p);
}//cadastra agenda

void grava(agenda *p)
{
	FILE *fptr = NULL;
	if((fptr = fopen("agenda.bin", "ab"))==NULL)
		printf("Erro\n");
	else
	{
		fwrite(p, sizeof(agenda), 1, fptr);
	}
	fclose(fptr);
}//grava

void mostra(agenda *p)
{
	FILE *fptr = NULL;
	int qtde, i;
	qtde = verifica();
	if((fptr = fopen("agenda.bin", "rb"))==NULL)
		printf("Erro ao abrir o arquivo\n");
	else
	{
		for(i=0; i<qtde; i++)
		{
			fseek(fptr, i*sizeof(agenda), 0); //zero significa a partir do inicio
			fread(p, sizeof(agenda), 1, fptr);
			if(p->reg==-1)
				printf("\n");
			else
				printf("Registro: %d\nNome: %s\nNota: %.2f\n\n", p->reg, p->nome, p->nota);
		}//for
		fclose(fptr);
	}
}//mostra

void altera(agenda *p, int op)
{
	int numreg, pos;
	if(op==2)
	{
		mostra(p);
		printf("\nDigite o Numero do Registro a ser alterado: ");
		scanf("%d", &numreg);
		fflush(stdin);
		pos = busca(p, numreg);
		if(pos==-1)
		{
			printf("Registro Inválido!\n\n");
			system("PAUSE");
		}
		else
		{
			printf("Registro Encontrado!\nRegistro: %d\nNome: %s\nNota: %.2f", p->reg, p->nome, p->nota);
			printf("\nDigite a nova nota: ");
			scanf("%f", &(p->nota));
			fflush(stdin);
			printf("Registro Atualizado!");
			atualiza(p, pos);
		}
	}
	if(op==3)
	{
		printf("Digite o numero do registro a ser deletado:\n");
		mostra(p);
		scanf("%d", &numreg);
		fflush(stdin);
		pos = busca(p, numreg);
		if(pos == -1)
		{
			printf("Registro Inválido!\n\n");
			system("pause");
		}
		else
			printf("Registro Deletado!");
			p->reg=-1;
			atualiza(p, pos);
	}
}//altera

void atualiza(agenda *p, int pos)
{
	FILE *fptr = NULL;
	if((fptr = fopen("agenda.bin", "rb+"))==NULL) //fecha-se fora do else
		printf("Erro ao ler o arquivo!\n");
	else
	{
		fseek(fptr, pos*sizeof(agenda), 0);
		fwrite(p, sizeof(agenda), 1, fptr);
	}//else
	fclose(fptr);
}//atualiza

int busca(agenda *p, int numreg)
{
	int i, qtde;
	int pos = -1;
	qtde = verifica();
	FILE *fptr = NULL;
	if((fptr = fopen("agenda.bin", "rb"))==NULL)
		printf("Erro ao abrir o arquivo\n");
	else
	{
		for(i=0; i<qtde; i++)
		{
			fseek(fptr, i*sizeof(agenda), 0);
			fread(p, sizeof(agenda), 1, fptr);
			if(p->reg==numreg)
			{
				pos = i;
				i = qtde; //sai do for
			}//if
		}//for
		fclose(fptr);
	}
	return pos;
}//busca

int verifica()
{
	FILE *fptr = NULL;
	long int cont=0;
	if((fptr=fopen("agenda.bin", "rb"))==NULL)
		return cont;
	else
	{
		fseek(fptr, 0, 2);
		cont = ftell(fptr)/sizeof(agenda);
		fclose(fptr); //dentro do else por conta do rb
		return cont;
	}
}//verifica
