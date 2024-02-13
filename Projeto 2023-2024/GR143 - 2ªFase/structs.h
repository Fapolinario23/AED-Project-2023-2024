/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: struct.h
 *
 * DESCRICAO: Contém as funções do table.c
 *
 ******************************************************************************/

#ifndef _H_STRUCTS
#define _H_STRUCTS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "general.h"
#include "connectivity.h"
#include "list.h"

/* Estrutura que contém as informações relativas aos problemas */
typedef struct head_line
{
    int L, C, v;         /* Informação do cabeçalho e pontos associados à mancha */
    int flag;            /* Verifica se existe mais que um número na tabela */
    int points;          /* Pontos associados à mancha */
    int lances;          /* Nº de lances realizados */
    int diff_numb;       /* Número de elementos diferentes na tabela original */
    int **element_count; /* Tabela auxiliar à verificação do ThereIsHope */
} Head_line;

/* Estrutura que contém as informações relativas aos lances realizados */
typedef struct plays
{
    int **board;                       /* Tabela/parede por jogada */
    int l, c;                          /* Coordenada de um elemento da mancha que lhes deu origem */
    int L;                             /* Nº de linhas da tabela (utilizado para efeitos de libertação de memória) */
    int lastplay_numb, lastplay_count; /* Correspondente do id do vetor element_count (da estrutura a cima) e numero de elementos desses eliminados com a mancha */
    List *possible_p;                  /* Lista com id's da conectividade para as várias jogadas possiveis para cada tabuleiro */
    Conect *vect;                      /* Lista que possui os vetores utilizados na conectividade */
} Plays;

/* Estrutura que contém informação relativa a cada hipotese de jogada numa dada tabela */
typedef struct move
{
    int lance;        /* ID do lance no vetor de conectividade */
    int lance_points; /*  Pontos associados ao lance */
} Move;

/* Estrutura responsável por guardar as informações relativas à sequencia de jogadas que maximiza os pontos */
typedef struct best_score
{
    int score_max, moves_max; /* Máximo de pontos possiveis e número de lances associados */
    List *sequence;           /* Sequência de lances realizados */
} Best_Score;

/* Estrutura com as coordenadas de uma das jogadas da sequencia que maximiza os pontos */
typedef struct coordenates
{
    int l, c; /* Coordenadas do lance em questão */
} Coordenates;

Head_line *create_headline();
Plays *create_plays(Head_line *);
Best_Score *create_best_score();
Move *create_move();
Coordenates *create_coordenates();
void free_play_stuff(Plays *);
void free_best_score(Best_Score *);
void freeListItem(Item);

#endif