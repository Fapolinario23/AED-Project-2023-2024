/******************************************************************************
 * (C) Algoritmo e Estrutura de Dados 2023/2024
 * 
 * AUTORE: Francisco Apolinário 
 *         Neelam Visueshcumar
 * 
 * NOME: general.h
 *
 * DESCRICAO: Contém as funções do general.c
 ******************************************************************************/

#ifndef _H_GENERAL
#define _H_GENERAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void end_verification (char*, char*, char);
FILE *open_file (char*, char*);
void close_file (FILE*);
char *file_out_name (char*, char*, int);
int points (int);
int **create_board (int, int);

#endif