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
 * initialize ()
 *
 * ARGUMENTO:   (Conect*) conected - Estrutura com o conjunto
 *              (int) N - Número de nós
 * 
 * RETORNA:     (Conect*) conected - Estrutura com o conjunto
 * 
 * DESCRICAO: Função para criar e inicializar o conjunto.
 * 
 *****************************************************************************/
Conect *initialize (Conect *conected, int N)
{
    int i;

    conected = (Conect*) malloc(sizeof(Conect));
    if (conected == NULL) exit(0);
    conected -> id = (int*) malloc (N*sizeof(int));
    if (conected -> id == NULL) exit (0);
    conected -> sz = (int*) malloc (N*sizeof(int));
    if (conected -> sz == NULL) exit (0);

    for (i = 0; i < N; i++) {
        conected -> id[i] = i;   /* Cada elemento é seu próprio representante inicialmente */
        conected -> sz[i] = 1;   /* Inicialmente, cada componente tem tamanho 1 */
    }
    return conected;
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
int find (int *id, int p)
{
    while (p != id[p]){
        /* Compressão de caminho: tornar o pai do nó o avô para encurtar a árvore */
        id[p] = id[id[p]];
        p = id[p];
    }
    return p;
}

/******************************************************************************
 * unionComponents ()
 *
 * ARGUMENTO:   (Conect*) conected - Estrutura com o conjunto
 *              (int) p - ID's das raizes das árvores a unir
 *              (int) q -
 * 
 * RETORNA:     (void)
 * 
 * DESCRICAO: Função para unir (conectar) dois componentes.
 * 
 *****************************************************************************/
void unionComponents (Conect *conected, int p, int q)
{
    int rootP = find(conected -> id, p);
    int rootQ = find(conected -> id, q);
    
    if (rootP == rootQ) return;     /* Os elementos já estão no mesmo componente */
    
    /* União por peso: conecte o menor componente ao maior componente */
    if (conected -> sz[rootP] < conected -> sz[rootQ]) {
        conected -> id[rootP] = rootQ;
        conected -> sz[rootQ] += conected -> sz[rootP];
    } else {
        conected -> id[rootQ] = rootP;
        conected -> sz[rootP] += conected -> sz[rootQ];
    }
    return;
}

/******************************************************************************
 * free_conect ()
 *
 * ARGUMENTO:   (Conect*) conected - Estrutura com o conjunto
 * 
 * RETORNA:     (void)
 * 
 * DESCRICAO: Função para libertar memória da estrutura com os componentes.
 * 
 *****************************************************************************/
void free_conect (Conect *conected)
{
    if (conected -> id != NULL) free (conected -> id);
    if (conected -> sz != NULL) free (conected -> sz);
    if (conected != NULL) free (conected);
    return;
}