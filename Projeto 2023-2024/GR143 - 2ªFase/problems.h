/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: problems.h
 *
 * DESCRICAO: Contém as funções do problems.c
 *
 ******************************************************************************/

#ifndef _H_PROBLEMS
#define _H_PROBLEMS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "structs.h"
#include "general.h"
#include "connectivity.h"
#include "files.h"

void read_file(FILE *, FILE *);
void proceed_problem(Head_line *, Plays *, FILE *, FILE *);
void problems_solve(FILE *, FILE *, Head_line *, Plays *);
int connect_elements(Conect *, Head_line *, Plays *);
List *spots_identifier(Head_line *, Conect *, List *);
Plays *isConnected(Head_line *, Conect *, Plays *, int, int);
Plays *play_make(Head_line *, Plays *, Stack *, List *, Conect *);
List *best_score_historical(Stack *, Best_Score *, Head_line *);
bool ThereisHope(Head_line *, Plays *, Best_Score *);
int **help_hope(Head_line *h, Plays *p);
void gravity_vertical(Head_line *, Plays *);
void gravity_horizontal(Head_line *, Plays *);

#endif
