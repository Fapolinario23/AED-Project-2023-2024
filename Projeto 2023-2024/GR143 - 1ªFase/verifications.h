/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: verifications.h
 *
 * DESCRICAO: Contém as funções do verifications.c
 * 
 ******************************************************************************/

#ifndef _H_VERIFICATIONS
#define _H_VERIFICATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "general.h"
#include "files.h"

int verify_full_tab (Head_line*, FILE*);
int verify_numb (Head_line*, FILE*);
int verify_problem (Head_line*, FILE*);
int verify_isolation (Head_line*, FILE*);

#endif