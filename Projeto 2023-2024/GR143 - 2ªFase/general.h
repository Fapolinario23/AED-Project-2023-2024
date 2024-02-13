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

void end_verification(char *, char *, char);
char *file_out_name(char *, char *, int);
FILE *open_file(char *, char *);
void close_file(FILE *);
int **create_board(int, int);
void free_board(int, int **);
int *create_vect(int);
int **copy_board(int **, int **, int, int);
int *copy_vect(int *, int *, int);

#endif