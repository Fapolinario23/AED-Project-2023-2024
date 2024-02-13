/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: files.h
 *
 * DESCRICAO: Contém as funções do files.c
 *
 ******************************************************************************/

#ifndef _H_FILES
#define _H_FILES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "structs.h"

int verify_problem(Head_line *, FILE *);
int verify_full_tab(Head_line *, FILE *);
int verify_prob_size(Head_line *, FILE *, int);
int points(int);
void print_file(Head_line *, FILE *, Stack *, Best_Score *, Plays *);
void print_list_plays(FILE *, Node *, Head_line *);
void print_stack_reverse(Stack *, FILE *);
void print_best_score(FILE *, Best_Score *);
void freeItem(Item);

#endif