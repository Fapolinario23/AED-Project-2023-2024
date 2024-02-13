/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: table.h
 *
 * DESCRICAO: Contém as funções do table.c
 * 
 ******************************************************************************/

#ifndef _H_TABLE
#define _H_TABLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura que contém as informações relativas aos problemas */
typedef struct head_line {
    int L, C, v, l, c;          /* Informação do cabeçalho e pontos associados à mancha */
    int flag;                   /* Verifica se existe mais que um número na tabela */
    int points;                 /* Pontos associados à mancha */
    int **board;                /* Tabela/parede */
} Head_line;

Head_line *create_struct (Head_line*);
void free_struct (Head_line*);
void gravity_horizontal(Head_line*);
void gravity_vertical (Head_line*);
void update_board (Head_line*);
Head_line *save_h_line (Head_line*, int*);

#endif