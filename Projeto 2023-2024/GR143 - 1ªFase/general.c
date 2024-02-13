/******************************************************************************
 * (C) Algortimo e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: general.c
 *
 * DESCRICAO: Ficheiro com funções básicas de uso comum.
 ******************************************************************************/

#include "general.h"

/******************************************************************************
 * end_verification ()
 *
 * ARGUMENTO:   (char*) nome - nome do ficheiro
 *              (char*) terminação - nome desejado para a extensão
 *              (char)  character - o primeiro carcater de "terminação"
 * 
 * RETORNA:     (void)
 * 
 * DESCRICAO: Verifica se tem a extensão.
 * 
 *****************************************************************************/
void end_verification (char *name, char *termination, char character)
{
    /* retorna um ponteiro para o caracter */
    char *pointer = strrchr(name, character);
    if (pointer == NULL) exit(0);
    /* verifica se o nome do file é igual À terminação */
    if (strcmp (pointer, termination) != 0) exit(0);
    return;
}

/******************************************************************************
 * open_file ()
 *
 * ARGUMENTO:   (char*) name - Nome do FILE
 *              (char*) mode - Modo de cracteristica de file
 * 
 * RETORNO:     (FILE*)  file - file aberta
 * 
 * DESCRICAO: Função que abre as files no modo pedido.
 * 
 *****************************************************************************/
FILE *open_file (char *name, char *mode)
{
    FILE *file = fopen (name, mode);
    if (file == NULL) exit(0);
    return (file);
}

/******************************************************************************
 * close_file ()
 *
 * ARGUMENTO:   (char*) name - Nome do ficheiro
 *             
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função que fecha os ficheiros.
 * 
 *****************************************************************************/
void close_file (FILE *file)
{
    fclose (file);
    return;
}

/******************************************************************************
 * file_out_name ()
 *
 * ARGUMENTO:   (char*) name - File 
 *              (char*) termination - terminacao pedida
 * 
 * RETORNO:     (char*) strcat(name, termination) - nome da file de output
 * 
 * DESCRICAO: Altera a terminação do ficheiro de saída.
 * 
 *****************************************************************************/
char *file_out_name (char *name, char *termination, int size)
{
    int lenght = strlen(name);
    name [lenght - size] = '\0';
    return strcat(name, termination);
} 

/******************************************************************************
 * points ()
 *
 * ARGUMENTOS:   (int) numb - Tamanho da mancha
 * 
 * RETORNO:      (int) * - Pontos associados à mancha 
 * 
 * DESCRICAO: Calcula os pontos associados à mancha
 * 
 *****************************************************************************/
int points (int numb)
{
    return numb*(numb - 1);
}

/******************************************************************************
 * create_board ()
 *
 * ARGUMENTOS:   (int) L - Número de linhas
 *               (int) C - Número de colunas
 * 
 * RETORNO:      (int**) - Tabuleiro
 * 
 * DESCRICAO: Cria o tabuleiro/parede do jogo.
 * 
 *****************************************************************************/
int **create_board (int L, int C)
{
    int **board, i;

    board = (int**) malloc (L*sizeof(int*));
    if (board == NULL) exit (0);
    for (i = 0; i < L; i++){
        board[i] = (int*) malloc (C*sizeof(int));
        if (board[i] == NULL) exit (0);
    }
    return board;
}