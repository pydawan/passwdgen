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
* Data criacao: 16/04/2011
* Data ultima alteracao: 19/02/2023
*
* Este programa tem como objetivo gerar senhas simples. Tenho plena certeza de que este
* codigo pode e deve ser melhorado. Respeito a criatividade dos outros e mantenha a autoria.
*
* OBS: Esse programa pode ser portado para Windows com pouco esforco.
*
* Compile com: gcc passwdgen.c -o passwdgen
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

/* Protótipo das funções */
void  validarComprimentoSenha(int len);
void  validarQuantidadeDeVezes(int vezes);
void  validarSeArgumentoNumerico(char* parametro, char* argumento);
void  mostrarAjuda(void);
void  mostrarVersao(void);
void  mensagemComandoInvalido(void);
void  gerarSenha(int len, char* opcoes, int linha);


int main(int argc, char* argv[]) {
	int len = 8; /* comprimento padrao da senha a ser gerada */
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
			gerarSenha(len, "", 0);
			break;

		case 2:
			if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
				mostrarAjuda();
			} else if ( (strcmp(argv[1], "-v") == 0) || (strcmp(argv[1], "--version") == 0) ) {
				mostrarVersao();
			} else if (strcmp(argv[1], "-ANS") == 0) {
				gerarSenha(len, "ANS", 0);
			} else if (strcmp(argv[1], "-AN") == 0 || strcmp(argv[1], "--alphanum") == 0) {
				gerarSenha(len, "AN", 0);
			} else if (strcmp(argv[1], "-AS") == 0) {
				gerarSenha(len, "AS", 0);
			} else if (strcmp(argv[1], "-A") == 0 || strcmp(argv[1], "--alpha") == 0) {
				gerarSenha(len, "A", 0);
			} else if (strcmp(argv[1], "-LNS") == 0) {
				gerarSenha(len, "LNS", 0);
			} else if (strcmp(argv[1], "-LN") == 0) {
				gerarSenha(len, "LN", 0);
			} else if (strcmp(argv[1], "-LS") == 0) {
				gerarSenha(len, "LS", 0);
			} else if (strcmp(argv[1], "-L") == 0 || strcmp(argv[1], "--lowercase") == 0) {
				gerarSenha(len, "L", 0);
			} else if (strcmp(argv[1], "-UNS") == 0) {
				gerarSenha(len, "UNS", 0);
			} else if (strcmp(argv[1], "-UN") == 0) {
				gerarSenha(len, "UN", 0);
			} else if (strcmp(argv[1], "-US") == 0) {
				gerarSenha(len, "US", 0);
			} else if (strcmp(argv[1], "-U") == 0 || strcmp(argv[1], "--uppercase") == 0) {
				gerarSenha(len, "U", 0);
			} else if (strcmp(argv[1], "-NS") == 0) {
				gerarSenha(len, "NS", 0);
			} else if (strcmp(argv[1], "-N") == 0 || strcmp(argv[1], "--numbers") == 0) {
				gerarSenha(len, "N", 0);
			} else if (strcmp(argv[1], "-S") == 0 || strcmp(argv[1], "--symbols") == 0) {
				gerarSenha(len, "S", 0);
			} else {
				mensagemComandoInvalido();
			}

			break;

		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:

			char* opcoes = "";

			for (i = 1; i < argc; i++) {
				if (strcmp(argv[i], "--alpha") == 0) {
					if (strstr(opcoes, "A") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "A");
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "--alphanum") == 0) {
					if (strstr(opcoes, "AN") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "AN");
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "--symbols") == 0) {
					if (strstr(opcoes, "S") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "S");
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "--lowercase") == 0) {
					if (strstr(opcoes, "L") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "L");
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "--uppercase") == 0) {
					if (strstr(opcoes, "U") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "U");
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "--numbers") == 0) {
					if (strstr(opcoes, "N") == NULL) {
						asprintf(&opcoes, "%s%s", opcoes, "N");
					} else {
						mensagemComandoInvalido();
					}
				}  else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--amount") == 0) {
					if (argc >= 3) {
						validarSeArgumentoNumerico("a", argv[i + 1]);
						vezes = atoi(argv[i + 1]);
						i++;
					} else {
						mensagemComandoInvalido();
					}
				} else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--length") == 0) {
					if (argc >= 3) {
						validarSeArgumentoNumerico("l", argv[i + 1]);
						len = atoi(argv[i + 1]);
						i++;
					} else {
						mensagemComandoInvalido();
					}
				} else if (strstr(argv[i], "-a") != NULL) {
					if (argc < 3) {
						mensagemComandoInvalido();
					}
					opcoes = argv[i];
					validarSeArgumentoNumerico("a", argv[i + 1]);
					vezes = atoi(argv[i + 1]);
					if (strstr(argv[i], "l") != NULL) {
						if (argc < 4) {
							mensagemComandoInvalido();
						}
						validarSeArgumentoNumerico("l", argv[i + 2]);
						len = atoi(argv[i + 2]);
						i++;
					}
					i++;
				} else if (strstr(argv[i], "-l") != NULL) {
					if (argc < 3) {
						mensagemComandoInvalido();
					}
					opcoes = argv[i];
					validarSeArgumentoNumerico("l", argv[i + 1]);
					len = atoi(argv[i + 1]);
					if (strstr(argv[i], "a") != NULL) {
						if (argc < 4) {
							mensagemComandoInvalido();
						}
						validarSeArgumentoNumerico("a", argv[i + 2]);
						vezes = atoi(argv[i + 2]);
						i++;
					}
					i++;
				} else if (strstr(argv[i], "-al") != NULL) {
					if (argc < 4) {
						mensagemComandoInvalido();
					}
					opcoes = argv[i];
					validarSeArgumentoNumerico("a", argv[i + 1]);
					vezes = atoi(argv[i + 1]);
					validarSeArgumentoNumerico("l", argv[i + 2]);
					len = atoi(argv[i + 2]);
					i += 2;
				} else if (strstr(argv[i], "-la") != NULL) {
					if (argc < 4) {
						mensagemComandoInvalido();
					}
					opcoes = argv[i];
					validarSeArgumentoNumerico("l", argv[i + 1]);
					len = atoi(argv[i + 1]);
					validarSeArgumentoNumerico("a", argv[i + 2]);
					vezes = atoi(argv[i + 2]);
					i += 2;
				} else {
					mensagemComandoInvalido();
				}
			}

			if (vezes <= 0) {
				vezes = 1;
			}

			validarQuantidadeDeVezes(vezes);
			validarComprimentoSenha(len);

			for (i = 0; i < vezes; i++) {
				gerarSenha(len, opcoes, i + 1);
			}

			break;

		default:
			mensagemComandoInvalido();
	}

	puts("");

	return 0;
}

void validarComprimentoSenha(int len) {
	if (len < 1 || len > 1000) {
		printf("\033[31mERRO: O comprimento da senha e invalido.\nComprimentos validos vao de 1 ate 1000 caracteres.\nParametro: -l\nArgumento: %d\033[0m\n\n", len);
		exit(1);
	}
}

void validarQuantidadeDeVezes(int vezes) {
	if (vezes < 1 || vezes > 1000) {
		printf("\033[31mERRO: A quantidade de senhas a serem geradas e invalida.\nA quantidade de vezes valida \
vai de 1 ate 1000.\nParametro: -a\nArgumento: %d\033[0m\n\n", vezes);
		exit(1);
	}
}

void validarSeArgumentoNumerico(char* parametro, char* argumento) {
	for (register int i = 0; argumento[i] != '\0'; i++) {
		if (isdigit(argumento[i]) == 0) {
			printf("\033[31mERRO: O valor informado nao e um numero!\nParametro: -%s\nArgumento: %s\033[0m\n\n", parametro, argumento);
			exit(1);
		}
	}
}

void mostrarAjuda(void) {
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

void mostrarVersao(void) {
	printf("\n\t\033[34mpasswdgen 1.0\n\n\tCopyright (C) 2009 Free Software Foundation, Inc. \
		\n\tLicense GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>. \
		\n\tThis is free software: you are free to change and redistribute it. \
		\n\tThere is NO WARRANTY, to the extent permitted by law.\033[0m\n\n");

	return;
}

void mensagemComandoInvalido(void) {
	printf("Comando inválido!\n\nPara consultar as opções disponíveis utilize o comando:\n  passwdgen --help\n\n");
	exit(1);
}

void gerarSenha(int len, char* opcoes, int linha) {

	// S - SYMBOLS
	char sb[] = {'*', '#'};

	// N - NUMBERS
	char num[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	// NS - NUMBERS AND SYMBOLS
	char numsb[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*', '#'};

	// L - LOWER CASE CHARS
	char alphalc[] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	// LS - LOWER CASE CHARS AND SYMBOLS
	char alphalcsb[] = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'*', '#'
	};

	// U - UPPER CASE CHARS
	char alphauc[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	// US - UPPER CASE CHARS AND SYMBOLS
	char alphaucsb[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'*', '#'
	};

	// A - LOWER CASE AND UPPER CASE CHARS
	char alpha[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	// AS - LOWER CASE CHARS, UPPER CASE CHARS AND SYMBOLS
	char alphasb[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'*', '#'
	};

	// AL - LOWER CASE CHARS AND NUMBERS
	char alphanumlc[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	// ALS - LOWER CASE CHARS AND NUMBERS
	char alphanumlcsb[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'*', '#'
	};

	// AU - UPPER CASE CHARS AND NUMBERS
	char alphanumuc[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
	};

	// AUS -UPPER CASE CHARS, NUMBERS AND SYMBOLS
	char alphanumucsb[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'*', '#'
	};

	// AN - LOWER CASE CHARS, UPPER CASE CHARS AND NUMBERS
	char alphanum[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
	};

	// LOWER CASE CHARS, UPPER CASE CHARS, NUMBERS AND SYMBOLS
	char alphanumsb[] = {
		'0', '1', '2', '3', '4', '5', '6', '7',
		'8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
		'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
		'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
		'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
		'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
		'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', '*', '#'
	};

	char senha[len + 1];

	/*    srand( time( NULL ) ); Definir a semente aqui faz com que a senha se repita */

	validarComprimentoSenha(len);

	for (int register i = 0; i < len; i++) {
		if (strchr(opcoes, 'A') != NULL) {
			if (strchr(opcoes, 'N') != NULL) {
				if (strchr(opcoes, 'S') != NULL) {
					// ANS
					senha[i] = alphanumsb[rand() % 64];
				} else {
					// AN
					senha[i] = alphanum[rand() % 62];
				}
			} else {
				if (strchr(opcoes, 'S') != NULL) {
					// AS
					senha[i] = alphasb[rand() % 54];
				} else {
					// A
					senha[i] = alpha[rand() % 52];
				}
			}
		} else if (strchr(opcoes, 'L') != NULL) {
			if (strchr(opcoes, 'N') != NULL) {
				if (strchr(opcoes, 'S') != NULL) {
					// LNS
					senha[i] = alphanumlcsb[rand() % 38];
				} else {
					// LN
					senha[i] = alphanumlc[rand() % 36];
				}
			} else {
				if (strchr(opcoes, 'S') != NULL) {
					// LS
					senha[i] = alphalcsb[rand() % 28];
				} else {
					// L
					senha[i] = alphalc[rand() % 26];
				}
			}
		} else if (strchr(opcoes, 'U') != NULL) {
			if (strchr(opcoes, 'N') != NULL) {
				if (strchr(opcoes, 'S') != NULL) {
					// UNS
					senha[i] = alphanumucsb[rand() % 38];
				} else {
					// UN
					senha[i] = alphanumuc[rand() % 36];
				}
			} else {
				if (strchr(opcoes, 'S') != NULL) {
					// US
					senha[i] = alphaucsb[rand() % 28];
				} else {
					// U
					senha[i] = alphauc[rand() % 26];
				}
			}
		} else if (strchr(opcoes, 'N') != NULL) {
			if (strchr(opcoes, 'S') != NULL) {
				// NS
				senha[i] = numsb[rand() % 12];
			} else {
				// N
				senha[i] = num[rand() % 10];
			}
		} else if (strchr(opcoes, 'S') != NULL) {
			// S
			senha[i] = sb[rand() % 2];
		} else {
			senha[i] = alphanumsb[rand() % 64];
		}
	}

	senha[len] = '\0'; /* terminador de string */

	if (linha > 0) {
		printf(" Senha %02d: %s\n\n", linha, senha);
	} else {
		printf("Senha: %s\n", senha);
	}

	return;
}

