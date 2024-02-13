/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: table.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a alocação e alteração do
 *            tabuleiro.
 * 
 ******************************************************************************/

#include "table.h"

/******************************************************************************
 * gravity_horizontal ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função responsável pela gravidade horizontal na atualização do
 *              ficheiro.
 * 
 *****************************************************************************/
void gravity_horizontal (Head_line *h_line)
{
    int x, y, j, zero_column_found, numb_cols = 0;

    /* Verifica se há colunas totalmente com -1 e faça o deslocamento */
    for (y = h_line -> C - 1; y >= numb_cols;){
        zero_column_found = 1;                  /* Supondo que a coluna contém apenas -1 inicialmente */

        /* Verifica se efetivamente a coluna apenas contém -1 */
        for (x = 0; x < h_line -> L; x++){
            if (h_line -> board[x][y] != -1){
                zero_column_found = 0;          /* A coluna contém pelo menos um número diferente de -1 */
                y--;
                break;
            }
        }

        /* Se uma coluna contiver apenas -1, faz o shift para a direita de todas as colunas */
        if (zero_column_found == 1){
            numb_cols++;
            for (j = y; j >= 0; j--){
                for (x = 0; x < h_line -> L; x++){
                    if (j >= 1){
                        h_line -> board[x][j] = h_line -> board[x][j - 1];
                    }
                }
            }
        }
    }

    /* O número de colunas que existiam apenas com -1 são colocadas no inicio da tabela */
    for (y = 0; y < numb_cols; y++){
        for (x = 0; x < h_line -> L; x++){
            h_line -> board[x][y] = -1;
        } 
    }
    return;
}

/******************************************************************************
 * gravity_vertical ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função responsável pela gravidade vertical na atualização do
 *            ficheiro.
 * 
 *****************************************************************************/
void gravity_vertical (Head_line *h_line)
{
    int x, y, k;

    /* Verifica a existência de -1 */
    for (x = 0; x < h_line -> L; x++){
        for (y = 0; y < h_line -> C; y++){
            if (h_line->board[x][y] == -1){

                /* Desloca os números acima para baixo */
                for (k = x; k > 0; k--) {
                    h_line->board[k][y] = h_line->board[k - 1][y];
                }
                /* Defina a posição superior como -1 */
                h_line->board[0][y] = -1;
            }
        }
    }
    return;
}

/******************************************************************************
 * update_board ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Graph *)  graph - Grafo que possui a lista de adjacências
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Atualiza o tabuleiro após os efeitos gravitacionais
 * 
 *****************************************************************************/
void update_board (Head_line *h_line)
{
    gravity_vertical (h_line);                  /* Efeito gravitacional vertical */                 
    gravity_horizontal (h_line);                /* Efeito gravitacional horizontal */
    return;
}

/******************************************************************************
 * free_struct ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                     sobre os problemas a resolver
 * 
 * RETORNO:      (void)
 * 
 * DESCRICAO: Liberta a memória associada à estrutura com a informação sobre
 *            os problemas.
 * 
 *****************************************************************************/
void free_struct (Head_line *h_line)
{
    int i;

    for (i = 0; i < h_line -> L; i++){ 
        if (h_line -> board != NULL) free(h_line -> board[i]);
    }
    if (h_line -> board != NULL) free(h_line -> board);
    free (h_line);
    return;
}

/******************************************************************************
 * create_struct ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                     sobre os problemas a resolver
 *               (int) max_numb - Número de números distintos
 * 
 * RETORNO:      (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 * 
 * DESCRICAO: Cria a estrutura onde irá ser guardada a informação sobre os 
 *            problemas
 * 
 *****************************************************************************/
Head_line *create_struct (Head_line *h_line)
{
    h_line = (Head_line*) malloc(sizeof(Head_line));
    if (h_line == NULL) exit (0);
    h_line -> board = NULL;
    h_line -> flag = 1;
    h_line -> points = 0;
    return h_line;
}

/******************************************************************************
 * save_h_line ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (int*) cabecalho - Vetor com cabeçalho dado em cada problema.
 * 
 * RETORNO:      (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 * 
 * DESCRICAO: Guarda a informação do cabeçalho de cada problema
 * 
 *****************************************************************************/
Head_line *save_h_line (Head_line *h_line, int *cabecalho)
{
    h_line -> L = cabecalho[0];
    h_line -> C = cabecalho[1];
    h_line -> v = cabecalho[2];
    h_line -> l = cabecalho[3];
    h_line -> c = cabecalho[4];
    return h_line;
}