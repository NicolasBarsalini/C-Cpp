#include <stdio.h> // necess�rio p trabalhar c arquivo
#include <stdlib.h> //necessario p aloca��o din�mica

typedef struct dados{
	int reg;
	char produto[20];
	int qtde;
	float preco;
}dados;

void aloca(dados **p, int tam);
int verifica();//abre o arquivo posiciona o ponteiro no fim fseek, ftell e descobre a qtde de bytes q tem
void cadastro(dados *p, int numreg);
void grava(dados *p); //passa o ponteiro da memoria
void mostra(dados *p);
void altera(dados *p, int op);
void busca(dados *p, int numreg);
void atualiza(dados *p, int pos);
void buscavago(dados *p, int qtde, int a);
main()
{
	char op;
	int qtde;
	dados *pd=NULL; //ponteiro p dados dentro da fun��o file, n crio agr
	aloca(&pd, 1);
	qtde=verifica();
	do{
		system("CLS");
		cadastro(pd,qtde+1); //se retorna 0, j� manda cadastrar no registro 1, se for 5 � 6 e por ai vai;
		qtde++;//se deixar o verifica fora do do-while a qtde n mudou, portanto deve-se incrementar a qtde
		printf("\nDeseja continuar? <S/N>\n");
		scanf("%c", &op);
		fflush(stdin);
	}while(op!='n' && op!='N');//main
	system ("CLS");
	printf("\nDados Cadastrados\n");
	mostra(pd);
}/*
case 2: altera(pd);
		break;*/

void aloca(dados **p, int tam)
{
	if((*p=(dados*)realloc(*p, tam*sizeof(dados)))==NULL)
		exit(1);
}//aloca dados

int verifica()
{
	FILE *fptr=NULL;
	long int pos; //criar um long int p receber o retorno de ftell;
	if((fptr=fopen("estoque.bin", "rb"))==NULL)//verifica se o arquivo existe, se n colocar diretorio, cria o arquivo na mesma pasta do arquivo fonte, rb=read bin�rio
		return 0; //se o arquivo n existir, ou seja = null, retorne 0;
	else
	{
		fseek(fptr, 0, 2); //offset = deslocamento(quanto de deslocamento ap�s o fim nesse caso), e posiciona o fptr no final do arquivo;
		pos=ftell(fptr)/sizeof(dados); //pega a qtde total de bytes, dividiu pelo tamanho da estrutura e descobre a qtde de estruturas q tem.
		fclose(fptr); //dentro do else, por conta do rb;
		return pos;
	}//else
}

void cadastro(dados *p, int numreg)
{
	//pos=buscavago(p, qtde, -1);
	if(pos===-1)
	printf("N�o encontrou rg vago");
	p->reg=qtde+1
	else
	p->reg=pos+1;
	p->reg=numreg;
	printf("\nRegistro: %i\nProduto: ", p->reg);
	gets(p->produto);
	fflush(stdin);
	printf("\nQtde: ");
	scanf("%i", &(p->qtde));
	fflush(stdin);
	printf("\nPreco: ");
	scanf("%f", &(p->preco));
	fflush(stdin);
	if(pos==-1)
		grava(p);
	else
		atualiza(p, pos);
}//numreg

void grava(dados *p)
{
	FILE *fptr=NULL;
	if((fptr=fopen("estoque.bin", "ab"))==NULL) //ab abre o arquivo no disco, e joga o ponteiro no fim do arquivo, OBS: n�o utilizar wb
		printf("\nErro no arquivo\n");
	else
	{
		fwrite(p, sizeof(dados), 1, fptr); //escreve as informa��es no arquivo
		printf("\nCadastrado com sucesso!\n\n");
		system("PAUSE");
	}
	fclose(fptr); //fora do else por conta do ab
}

void mostra(dados *p)
{
	FILE *fptr=NULL;
	int qtde, i;
	
	qtde=verifica(); //diz quantos elementos tem dentro do arquivo
	
	if((fptr=fopen("estoque.bin", "rb"))==NULL) //le o arquivo
		printf("\nErro no arquivo\n");
	else
	{
		for(i=0; i<qtde; i++) //n por p++, vc tem um espa�o pra p, iria pegar lixo da mem�ria
		{
			fseek(fptr, i*sizeof(dados), 0); //movimenta o ptr de arquivos, sempre a partir do inicio
			fread(p, sizeof(dados), 1, fptr); //p recebe a leitura de dados em 1 qtde de fptr
			printf("\nRegistro: %i\nProduto: %s\nQtde: %i\nPreco: %.2f\n\n", p->reg, p->produto, p->qtde, p->preco);
		}//for
		fclose(fptr); //dentro do else, porque � rb
	}//else
}//mostra
/*
void altera(dados *p, int op)
{
	int numreg, pos;
	mostra(p);
	printf("\nDigite o registro a ser alterado: );
	scanf("%d", &numreg);
	fflush(stdin);
	pos = busca(p, numreg);
	if (pos==-1)
		printf("\nRegistro Inv�lido\n");
	else
	{
		printf("Registro: %i\nProduto: %s\nQtde: %i\nPreco: %.2f\n\n", p->reg....);
		if(op==2)
		{
			printf("\nNovo preco: );
			scanf("%f", &(p->preco));
			fflush(stdin);
		}
		else
			p->qtde=-1; //fica vago
		atualiza(p, pos);
	}
}

void busca(dados *p, int numreg)
{
	FILE *fptr=NULL;
	int i, qtde, pos=-1;
	qtde = verifica() //abre o arquivo ve os elementos e fecha
	if((fptr=fopen("estoque.bin", "rb"))==NULL)
		return pos; // error
	else
		{
			for(i=0; i<qtde; i++)
			{
				fseek(fptr, i*sizeof(dados), 0);
				fread(p, sizeof(dados), 1, fptr);
				if(p->reg==numreg)
				{
					pos=i;
					i=qtde; //for�a a sa�da do for, deve sair do for, se n vai se alterar a informa��o da mem�ria
				}//if
			}//for
			fclose(fptr); //rb fecha dentro else, ab fecha-se fora
		}
	return pos;
}

void atualiza(dados *p, int pos)
{
	FILE *fptr=NULL;
	if((fptr=fopen("estoque.bin", "rb+"))==NULL) //rb abre s� p leitura, ab adiciona, atualizar:rb+
		printf("Error");
	else
	{
		fseek(fptr, pos*sizeof(dados), 0); //posicionar o ponteiro no arquivo a partir do zero
		fwrite(p, sizeof(dados), 1, fptr); //pont p memoria, tam da informa��o, qtde da informa��o, ponteiro do arquivo
	} // qualquer um q permita grava��o dentro do c�digo, fecha o programa fora do else, unico q fecha dentro � op rb
	fclose(fptr);
}


void buscavago(dados *p, int qtde, int a)
{
	int i, pos=-1;
	FILE *fptr=NULL;
	if((fptr=fopen("esgoque.bin", "rb"))==NULL)
		exit(1)
	else
	{
		for(i=0; i<qtde; i++)
		{
			fseek(fptr, i*sizeof(dados), 0);
			fread(p, sizeof(dados), 1, fptr);
			if(p->qtde==a)
				pos=i;
				i=qtde;
		}
		fclose(fptr);
	}	
	return pos;
}
