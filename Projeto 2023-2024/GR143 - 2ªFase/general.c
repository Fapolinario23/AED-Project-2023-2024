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
 * ARGUMENTO:   (char*) name - Nome do ficheiro
 *              (char*) termination - Nome desejado para a extensão
 *              (char)  character - Primeiro carcater de "terminação"
 *
 * RETORNA:     (void)
 *
 * DESCRICAO: Verifica se tem a extensão correta.
 *
 *****************************************************************************/
void end_verification(char *name, char *termination, char character)
{
    /* Retorna um ponteiro para o caracter */
    char *pointer = strrchr(name, character);
    if (pointer == NULL)
        exit(0);
    /* verifica se o nome do file é igual À terminação */
    if (strcmp(pointer, termination) != 0)
        exit(0);
    return;
}

/******************************************************************************
 * file_out_name ()
 *
 * ARGUMENTO:   (char*) name - File
 *              (char*) termination - Terminacao pedida
 *
 * RETORNO:     (char*) strcat(name, termination) - Nome da file de output
 *
 * DESCRICAO: Altera a terminação do ficheiro de saída.
 *
 *****************************************************************************/
char *file_out_name(char *name, char *termination, int size)
{
    int lenght = strlen(name);
    name[lenght - size] = '\0';
    return strcat(name, termination);
}

/******************************************************************************
 * open_file ()
 *
 * ARGUMENTO:   (char*) name - Nome do FILE
 *              (char*) mode - Modo de cracteristica de file
 *
 * RETORNO:     (FILE*) file - File aberto
 *
 * DESCRICAO: Função que abre as files no modo pedido.
 *
 *****************************************************************************/
FILE *open_file(char *name, char *mode)
{
    FILE *file = fopen(name, mode);
    if (file == NULL)
        exit(0);
    return (file);
}

/******************************************************************************
 * close_file ()
 *
 * ARGUMENTO:   (char*) name - Nome do ficheiro
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função que fecha os ficheiros.
 *
 *****************************************************************************/
void close_file(FILE *file)
{
    fclose(file);
    return;
}

/******************************************************************************
 * create_board ()
 *
 * ARGUMENTOS:   (int) L - Número de linhas
 *               (int) C - Número de colunas
 *
 * RETORNO:      (int**) - Tabela
 *
 * DESCRICAO: Função para criar tabelas.
 *
 *****************************************************************************/
int **create_board(int L, int C)
{
    int **board, i, j;

    board = (int **)malloc(L * sizeof(int *));
    if (board == NULL)
        exit(0);
    for (i = 0; i < L; i++)
    {
        board[i] = (int *)malloc(C * sizeof(int));
        if (board[i] == NULL)
            exit(0);
        for (j = 0; j < C; j++)
            board[i][j] = 0;
    }
    return board;
}

/******************************************************************************
 * free_board ()
 *
 * ARGUMENTO:   (int) L - Nº de linhas da tabela
 *              (int**) table - Tabela a libertar memória
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função que liberta memória de tabelas.
 *
 *****************************************************************************/
void free_board(int L, int **table)
{
    int i;
    for (i = 0; i < L; i++)
        free(table[i]);
    free(table);
    return;
}

/******************************************************************************
 * create_vect ()
 *
 * ARGUMENTOS:  (int) N - Tamanho do vetor a alocar
 *
 * RETORNO:     (int*) v - Vetor criado
 *
 * DESCRICAO: Função para criar vetores.
 *
 *****************************************************************************/
int *create_vect(int N)
{
    int i;
    int *v = (int *)malloc(N * sizeof(int));
    if (v == NULL)
        exit(0);
    for (i = 0; i < N; i++)
        v[i] = 0;
    return v;
}

/******************************************************************************
 * copy_board ()
 *
 * ARGUMENTOS:  (int**) original - Tabela a ser copiada
 *              (int**) new - Tabela onde vai ser escrita a copia
 *              (int) L - Nº de linhas da tabela
 *              (int) C - Nº de colunas da tabela
 *
 * RETORNO:     (int**) new - Tabela onde vai ser escrita a copia
 *
 * DESCRICAO: Copia uma tabela para outra.
 *
 *****************************************************************************/
int **copy_board(int **original, int **new, int L, int C)
{
    int i, j;

    for (i = 0; i < L; i++)
    {
        for (j = 0; j < C; j++)
        {
            new[i][j] = original[i][j];
        }
    }
    return new;
}

/******************************************************************************
 * copy_vect ()
 *
 * ARGUMENTOS:  (int*) original - Vetor a ser copiada
 *              (int*) new - Vetor onde vai ser escrita a copia
 *              (int) N - Nº de elementos do vetor
 *
 * RETORNO:     (int*) new - Vetor onde vai ser escrita a copia
 *
 * DESCRICAO: Copia um vetor para outro.
 *
 *****************************************************************************/
int *copy_vect(int *new, int *original, int N)
{
    int i;
    for (i = 0; i < N; i++)
    {
        new[i] = original[i];
    }
    return new;
}