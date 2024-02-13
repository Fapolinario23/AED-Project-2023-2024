/******************************************************************************
 * (C) Algoritmo e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: connectivity.c
 *
 * DESCRICAO: Funções que implementam o algoritmo de união rápida equilibrada
 *            com compressão de caminho.
 *
 ******************************************************************************/

#include "connectivity.h"

/******************************************************************************
 * create_connect ()
 *
 * ARGUMENTO:   (int) N - Número de elementos na tabela
 *
 * RETORNA:     (Conect*) conected - Estrutura com o conjunto de conexões
 *
 * DESCRICAO: Função para criar a estrutura Conect.
 *
 *****************************************************************************/
Conect *create_conect(int N)
{
    Conect *conected = (Conect *)malloc(sizeof(Conect));
    if (conected == NULL)
        exit(0);
    conected->id = (int *)malloc(N * sizeof(int));
    if (conected->id == NULL)
        exit(0);
    conected->sz = (int *)malloc(N * sizeof(int));
    if (conected->sz == NULL)
        exit(0);

    return conected;
}

/******************************************************************************
 * free_conect ()
 *
 * ARGUMENTO:   (Conect*) conected - Estrutura com o conjunto de conexões
 *
 * RETORNA:     (void)
 *
 * DESCRICAO: Função para libertar memória da estrutura Conect.
 *
 *****************************************************************************/
void free_conect(Conect *conected)
{
    if (conected->id != NULL)
        free(conected->id);
    if (conected->sz != NULL)
        free(conected->sz);
    if (conected != NULL)
        free(conected);
    return;
}

/******************************************************************************
 * unionComponents ()
 *
 * ARGUMENTO:   (Conect*) conected - Estrutura com o conjunto de conexões
 *              (int) p - ID's dos elementos a unir
 *              (int) q -
 *
 * RETORNA:     (void)
 *
 * DESCRICAO: Função para unir (conectar) dois elementos.
 *
 *****************************************************************************/
void unionComponents(Conect *conected, int p, int q)
{
    int rootP = find(conected->id, p); /* Encontra o representante do element pretendido */
    int rootQ = find(conected->id, q); /* Encontra o representante do element pretendido */

    if (rootP == rootQ) /* Os elementos já estão ligados? Se sim, retorna */
        return; 

    /* Se não, proceede-se à união por peso: conecta o menor componente ao maior componente */
    if (conected->sz[rootQ] < conected->sz[rootP])
    {
        conected->id[rootQ] = rootP;
        conected->sz[rootP] += conected->sz[rootQ];
    }
    else
    {
        conected->id[rootP] = rootQ;
        conected->sz[rootQ] += conected->sz[rootP];
    }
    return;
}

/******************************************************************************
 * find ()
 *
 * ARGUMENTO:   (int*) id - Vetor de ID's
 *              (int) p - Antigo nó pai
 *
 * RETORNA:     (int) p - Novo nó avô
 *
 * DESCRICAO: Função para encontrar o representante (raiz) de um componente.
 *
 *****************************************************************************/
int find(int *id, int p)
{
    while (p != id[p])
    {
        p = id[p];
    }
    return p;
}