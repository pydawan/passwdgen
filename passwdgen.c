#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
*
* passwdgen 1.0
*
* Copyright (C) 2009 Free Software Foundation, Inc.
* License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>.
* This is free software: you are free to change and redistribute it.
* There is NO WARRANTY, to the extent permitted by law.
*
* Autor: Thiago Alexandre Martins Monteiro
* Local: Goiania/Goias/Brasil
* Data: 16/04/2011
*
* Este programa tem como objetivo gerar senhas simples. Tenho plena certeza de que este
* codigo pode e deve ser melhorado. Respeito a criatividade dos outros e mantenha a autoria.
*
* OBS: Esse programa pode ser portado para Windows com pouco esforco.
*
* Compile com: gcc passwdgen.c -o passwdgen
*/

/* Protótipo das funções */
int validarComprimentoSenha(int len);
int validarQuantidadeDeVezes(int vezes);
void mostrarAjuda(void);
void mostrarVersao(void);
void gerarSenha(int len);

int main(int argc, char *argv[])
{
	int len = 8; /* comprimento da palavra */
	int vezes;
	int register i = 0;

	system("clear"); /* no RuWindows use system(“cls”); */
	puts("\033[32m\tPASSWDGEN (Gerador de Senhas)\033[0m\n");

	/* Inicializa gerador de números randômicos com a hora atual do sistema */
	srand(time(NULL));
	
	if (argc != 2) {
		puts("\033[34mProcessando...\033[0m\n");
		sleep(2);
	}

	switch (argc) {
		case 1:
			gerarSenha(len);
			break;

		case 2:
			if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
				mostrarAjuda();
			}

			if ( (strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0) ) {
				mostrarVersao();
			}
			break;

		case 3:
			/* -l de length (comprimento da senha) */
			if ( (strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--length") == 0) ) {
				/* Converte de string para inteiro */
				len = atoi(argv[2]);
				gerarSenha(len);
			}

			/* -a de amount (quantas senhas devem ser geradas) */
			if ( (strcmp(argv[1], "-a") == 0) || (strcmp( argv[1], "--amount") == 0) ) {
				vezes = atoi(argv[2]);
				if ( validarQuantidadeDeVezes(vezes ) )
					exit(1);

				for (i = 0; i < vezes; i++) {
					gerarSenha(len);
				}
			}
			break;

		case 4:
			if (strcmp(argv[1], "-al") == 0) {
				vezes = atoi(argv[2]);
				len = atoi(argv[3]);
			}

			if (strcmp(argv[1], "-la") == 0) {
				len = atoi(argv[2]);
				vezes = atoi(argv[3]);
			}

			if ( validarQuantidadeDeVezes(vezes) ) {
				exit(1);
			}

			for (i = 0; i < vezes; i++) {
				gerarSenha(len);
			}
			break;

		case 5:
			/* -l de length (comprimento da senha) */
			if ( (strcmp(argv[1], "-l") == 0) || (strcmp(argv[1], "--length") == 0) ) {
				/* Converte de string para inteiro */
				len = atoi(argv[2]);
			} else {
				/* -a de amount (quantas senhas devem ser geradas) */
				if ( (strcmp(argv[1], "-a") == 0) || (strcmp( argv[1], "--amount") == 0) ) {
					vezes = atoi(argv[2]);
					if ( validarQuantidadeDeVezes(vezes ) )
						exit(1);
				}
			}

			/* -l de length (comprimento da senha) */
			if ( (strcmp(argv[3], "-l") == 0) || (strcmp(argv[3], "--length") == 0) ) {
				/* Converte de string para inteiro */
				len = atoi(argv[4]);
			} else {
				/* -a de amount (quantas senhas devem ser geradas) */
				if ( (strcmp(argv[3], "-a") == 0) || (strcmp( argv[3], "--amount") == 0) ) {
					vezes = atoi(argv[4]);
					if ( validarQuantidadeDeVezes(vezes ) )
						exit(1);
				}
			}

			for (i = 0; i < vezes; i++) {
				gerarSenha(len);
			}
			break;
		default:
			printf("\n\033[32m\tDigite: passwdgen --help para obter ajuda.\033[0m\n\n");
	}
	puts("");
	return 0;
}

int validarComprimentoSenha(int len)
{
	if (len < 1 || len > 50) {
		printf("\t\033[31mErro: O comprimento da senha e invalido.\n\tComprimentos validos vao de 1 ate 50 caracteres.\033[0m\n\n");
		return 1;
	} else return 0;
}

int validarQuantidadeDeVezes(int vezes) 
{
	if (vezes < 1 || vezes > 1000) {
		printf("\t\033[31mErro: A quantidade de senhas a serem geradas e invalida.\n\tA quantidade de vezes valida \
vai de 1 ate 1000.\033[0m\n\n");
		return 1;
	} else return 0;
}

void mostrarAjuda(void) 
{	
	printf("\n\t\033[34mPASSWDGEN\033[32m\n");
	printf("\n\t\033[34mNOME: passwdgen - gera senhas simples e imprime na saida padrao.\n\033[0m");
	printf("\n\t\033[34mSINOPSE: passwdgen [OPTION] … [NUMBER] …\n\033[0m");
	printf("\n\t\033[34mDESCRICAO: Gera senhas simples e imprime na saida padrao.\033[0m\n");
	printf("\n\t\033[34m -a, --amount\n\t\t Define a quantidade de senhas a serem geradas.\033[0m");
	printf("\n\n\t\033[34m -h, --help\n\t\t Apresenta a tela de ajuda do sistema.\033[0m");
	printf("\n\n\t\033[34m -l, --length\n\t\t Define o comprimento (quantidade de caracteres) da senha.\033[0m");
	printf("\n\n\t\033[34m -v, --version\n\t\t Apresenta o numero de versao do programa.\033[0m");
	printf("\n\n\t\033[34m EXEMPLOS:\033[0m");
	printf("\n\n\t\t\033[34mpasswdgen -a 5\n\t\tGera 5 senhas de 8 caracteres.\033[0m");
	printf("\n\n\t\t\033[34mpasswdgen -l 20\n\t\tGera uma senha de 20 caracteres.\033[0m");
	printf("\n\n\t\t\033[34mpasswdgen -al 3 5\n\t\tGera 3 senhas de 5 caracteres.\033[0m");
	printf("\n\n\t\t\033[34mpasswdgen -la 3 5\n\t\tGera 5 senhas de 3 caracteres.\033[0m");
	printf("\n\n\t\033[34m AUTOR: Thiago Alexandre M. Monteiro\033[0m\n");
	
	return;
}

void mostrarVersao(void) 
{
	printf("\n\t\033[34mpasswdgen 1.0\n\n\tCopyright (C) 2009 Free Software Foundation, Inc. \
		\n\tLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>. \
		\n\tThis is free software: you are free to change and redistribute it. \
		\n\tThere is NO WARRANTY, to the extent permitted by law.\033[0m\n\n");

	return;
}

void gerarSenha(int len) 
{
	int register i;

	char alfabeto[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'X', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', '*', '#'
	};

	char palavra[len];

	/*    srand( time( NULL ) ); Definir a semente aqui faz com que a senha se repita */

	if ( validarComprimentoSenha(len ) )
		exit(1);

	for (i = 0; i < len; i++) {
		palavra[i] = alfabeto[rand() % 64]; /* 64 é o tamanho do alfabeto */
	}

	palavra[i] = '\0'; /* terminador de string */
	printf("\t%s\n", palavra);

	return;
}
