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
#include "table.h"
#include "general.h"
#include "connectivity.h"
#include "verifications.h"

void read_file (FILE*, FILE*);
void problems_solve (FILE*, FILE*, Head_line*);
void print_wout_alt (Head_line*, FILE*);
void print_file (Head_line*, FILE*);


#endif
