// Trabalho 2 de programacao-caca palavras
//Luca Jacentink, Darue

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//define valores imutaveis no codigo como tamanho da matriz e do maximo da palavra
#define maximo 10
#define tamanho 15

//inicializa a struct que coordenara o jogo
typedef struct
{
	char nome[tamanho];
	int pontuacao;
}jogo;

//primeira das funcoes, gera os jogadores que vao brincar
void jogador(jogo *jogadores, int quantidade)
{
	if (jogadores == NULL)
	{
		exit(EXIT_FAILURE);//verifica se o ponteiro esta funcionando adequadamente
	}
	for (int i = 0; i < quantidade; i++)
	{
		printf("Insira um nome para o %d jogador: ", i + 1);
		scanf("%s", jogadores[i].nome);//pega do teclado os nomes dos jogadores que irao jogar

		jogadores[i].pontuacao = 0;//inicializa a pontuacao de todos eles em 0
	}
}

//printa o nome do vencedor
void ganhador(jogo *jogadores, int quantidade)
{
	jogo vencedor = {"", -999};//inicializa vencedor como uma string vazia

	for (int i = 0; i < quantidade; i++)
	{
		if (jogadores[i].pontuacao > vencedor.pontuacao)
		{
			strcpy(vencedor.nome, jogadores[i].nome);
			vencedor.pontuacao = jogadores[i].pontuacao;//caso a pontuacao do jogador for maior do que a do jogador anterior com maior pontuacao ele troca de lugar com o vencedor
		}
	    printf("\nVencedor: %s\n", vencedor.nome);
	    printf("Com : %d pontos!!!!!!!\n", vencedor.pontuacao);//printa quem foi o vencedor e com quantos pontos
	}
}

//funcao principal na qual funciona o jogo
void jogar (char palavra[maximo], char **matriz, jogo *jogador)
{
	int letra;
	int pontuou = 0;//inicializa as variaveis necessarias

	//comeca a procurar na horizontal
	for(int a = 0; a < maximo; a++)
	{
	    for(int b = 0; b < maximo; b++)
		{
			if (palavra[0] == matriz[a][b])
			{
				letra = 1;

				//loop para iterar o valor da coluna, de acordo com a posicao em que foi encontrada a primeira letra
				for(; letra <= strlen(palavra);)
				{
					//caso a letra seja igual ao valor encontrado na matriz busque a proxima letra na proxima posicao
					if (palavra[letra] == matriz[a][b + letra])
					{
						letra++;
					}
					else
					{
						break;
					}

					//se a letra chegou na ultima posicao do vetor palavra sem sair do loop, aumente pontuou
					if (letra >= strlen(palavra))
					{
	  					pontuou = 1;
					}
				}
			}
		}
	}

	//inicio da busca por palavras na vertical
	for(int b = 0; b < maximo; b++)
	{
		for(int a = 0; a < maximo; a++)
		{
			if (palavra[0] == matriz[a][b])
			{
				letra = 1;

				//loop para iterar o valor da coluna, de acordo com a posi��o em que foi encontrada a primeira letra
				for(; letra <= strlen(palavra);)
				{
					//caso a letra seja igual ao valor encontrado na matriz busque a proxima letra na proxima posicao
					if (palavra[letra] == matriz[a + letra][b])
					{
						letra++;
					}
					else
					{
						break;
					}

					//se a letra chegou na ultima posicao do vetor palavra sem sair do loop, aumente pontuou
					if (letra >= strlen(palavra))
					{
						pontuou = 1;
					}
				}
			}
		}
	}

	//inicio da busca por palavras na diagonal
	for(int a = 0; a < maximo; a++)
	{
		for(int b = 0; b < maximo; b++)
		{
			if (palavra[0] == matriz[a][b])
			{
				letra = 1;

				//loop para iterar o valor da coluna, de acordo com a posicao em que foi encontrada a primeira letra
				for(; letra <= strlen(palavra);)
				{
					//caso a letra seja igual ao valor encontrado na matriz busque a proxima letra na proxima posicao
					if (palavra[letra] == matriz[a + letra][b + letra])
					{
						letra++;
					}
					else
					{
						break;
					}

					//se a letra chegou na ultima posicao do vetor palavra sem sair do loop, aumente pontuou
					if (letra >= strlen(palavra))
					{
						pontuou = 1;
					}
				}
			}
		}
	}

	int ponto;
	ponto = 0;//inicializa a pontuacao do jogador

	//armazena a pontuacao do jogador do loop em .pontuacao positiva
	if (pontuou == 1)
	{
		ponto++;
		(*jogador).pontuacao += ponto;
	}

	//armazena a pontuacao do jogador do loop em .pontuacao negativa
	else
	{
		ponto=ponto-1;
		(*jogador).pontuacao += ponto;
	}

	//caso o jogador ja tenha 0 pontos impede que ele fique com pontuacao negativa
	if ((*jogador).pontuacao < 0)
	{
		(*jogador).pontuacao = 0;
	}

	//printa a quantidade de pontos do jogador
	printf("O jogador tem %d pontos\n", (*jogador).pontuacao);
}

//funcao utilizando biblioteca ctype, torna todas as letras da palavra maiusculas
void maiuscula(char palavra[maximo])
{
	for (int i = 0; i < strlen(palavra); i++)
	{
		palavra[i] = toupper(palavra[i]);
	}
}
int main()
{
	char palavra[maximo];
	int quantidade;
	int i;
	int linha, coluna;
	jogo *jogadores;//inicializa as variaveis do programa
	char **matriz;
	matriz = malloc(maximo * sizeof(char*));
	for (i = 0; i < maximo; i++)
	{
		matriz[i] = malloc(maximo* sizeof(char));
	}

	//aloca o espaco na memoria para a matriz
	for (int i = 0; i < maximo; i++)
	{
		//verifica se esta funcionando corretamente
		if (matriz[i] == NULL)
    	{
			exit(EXIT_FAILURE);
		}
	}

	FILE *arquivomatriz = NULL;
	arquivomatriz = fopen("matriz.txt", "r");//abre o arquivo da matriz para leitura

	//verifica se o arquivo existe ou nao
	if (arquivomatriz == NULL)
	{
		printf("Arquivo nao existe\n");
		exit(EXIT_FAILURE);
	}
    while (!feof(arquivomatriz))
	{
		char arquivo;
		for (int k = 0; k < maximo; k++)
		{
			//armazena as letras do arquivo
			for (int l = 0; l < maximo; l++)
			{
				fscanf(arquivomatriz, "%c", &arquivo);

				//e coloca elas maiusculas na matriz
				if (arquivo != '\n')
				{
					matriz[k][l] = toupper(arquivo);
				}
			}
		}

	}
	printf("voces estao em quantos?");
	scanf("%d", &quantidade);
	jogadores = malloc(quantidade* sizeof(jogo));//aloca o espaco na memoria para os jogadores de acordo com o struct
	jogador(jogadores, quantidade);//chama a funcao jogador

	for (int i = 0; i < quantidade; i++)
	{
		//printa a matriz na tela para o jogador
		for (linha =0; linha < maximo; linha++)
		{
			for (coluna = 0; coluna < maximo; coluna++)
			{
				printf("%c", matriz[linha][coluna]);
			}
		}
		printf("\nJogador %s\n", jogadores[i].nome);
		printf("Qual palavra voce vai chutar?\n");

		scanf("%s", palavra);//le a palavra digitada pelo jogador
		maiuscula(palavra);//chama a funcao maiuscula

		if (palavra[0] == '.')
		{
			printf("Muito obrigado por jogar)\n");
			ganhador(jogadores, quantidade);
			free(jogadores);
			for (i = 0; i < maximo; i++)
	{
               free (matriz[i]);
	}

			free(matriz);
			return 0;//condicional para caso o jogo acabe, ou seja o jogador pressione "." e de "enter"
		}
		jogar(palavra, matriz, &jogadores[i]);//chama a funcao que executa o jogo

		//quando o ultimo jogador joga reinicia o loop para o primeiro jogador
		if (i == quantidade - 1)
		{
			i = -1;
		}
	}
}
