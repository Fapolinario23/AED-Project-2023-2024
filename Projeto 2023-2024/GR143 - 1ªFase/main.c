/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTHORS: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NAME: main.c
 *
 * DESCRIPTION: Programa Main
 ******************************************************************************/

#include "general.h"
#include "files.h"

/******************************************************************************
 * main ()
 *
 * ARGUMENTS:   (int)   argc - número de argumentos na linha de comandos
 *              (char*) argv - tabela de ponteiros para os argumentos
 * 
 * RETURNS:     (int)   0
 *
 * DESCRIPTION: Programa main
 *****************************************************************************/
int main (int argc, char **argv)
{
    /* Verifica se é dado o número correto de argumentos */
    if (argc != 2) exit(0);

    FILE *fp_in = NULL, *fp_out = NULL; 
    end_verification (argv[1], ".tilewalls1", '.');
    fp_in = open_file (argv[1], "r");
    fp_out = open_file (file_out_name (argv[1], ".singlestep", 11), "w");
    read_file(fp_in, fp_out);
    close_file (fp_in);
    close_file (fp_out);
    return 0;
}