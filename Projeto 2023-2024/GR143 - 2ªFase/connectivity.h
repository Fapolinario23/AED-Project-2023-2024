/******************************************************************************
 * (C) Algoritmo e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: connectivity.h
 *
 * DESCRICAO: Contém as funções do connectivity.c
 *
 ******************************************************************************/

#ifndef _H_CONNECTIVITY
#define _H_CONNECTIVITY

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura utilizada para verificar as conexões através da conectividade */
typedef struct conect
{
    int *sz; /* Tamanho das árvores, para a otimização por peso */
    int *id; /* Array para representar os elementos e suas conexões */
} Conect;

Conect *create_conect(int);
void free_conect(Conect *);
void unionComponents(Conect *, int, int);
int find(int *, int);

#endif