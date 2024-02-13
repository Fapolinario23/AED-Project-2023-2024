/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: main.c
 *
 * DESCRICAO: Programa Main
 * 
 ******************************************************************************/

#include "general.h"
#include "problems.h"

/******************************************************************************
 * main ()
 *
 * ARGUMENTOS:  (int)   argc - Número de argumentos na linha de comandos
 *              (char*) argv - Tabela de ponteiros para os argumentos
 * 
 * RETORNOS:    (int)   0
 *
 * DESCRICAO: Programa main
 *****************************************************************************/
int main (int argc, char **argv)
{
    /* Verifica se é dado o número correto de argumentos */
    if (argc != 2) exit(0);

    FILE *fp_in = NULL, *fp_out = NULL; 
    end_verification (argv[1], ".tilewalls", '.');                          /* Verifica a terminação do ficheiro dado */
    fp_in = open_file (argv[1], "r");                                       /* Abre o ficheiro de entrada em modo de leitura */
    fp_out = open_file (file_out_name (argv[1], ".tileblasts", 10), "w");   /* Abre o ficheiro de saída em formato escrita */
    read_file(fp_in, fp_out);                                               /* Lê o ficheiro de entrada e dá a solução no ficheiro de saída */
    close_file (fp_in);                                                     /* Fecha o ficheiro de entrada */
    close_file (fp_out);                                                    /* Fecha o ficheiro de saídas */
    return 0;
}