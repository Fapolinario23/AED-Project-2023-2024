/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: structs.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a alocação, libertações e 
 *            cópias.
 *
 ******************************************************************************/

#include "structs.h"

/******************************************************************************
 * create_headline ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre o problema a resolver.
 *
 * DESCRICAO: Cria e inicializa a estrutura onde será armazenada a informação
 *            sobre os problemas.
 *
 *****************************************************************************/
Head_line *create_headline()
{
    Head_line *h_line = (Head_line *)malloc(sizeof(Head_line));
    if (h_line == NULL)
        exit(0);
    h_line->element_count = NULL;
    h_line->flag = 1;
    h_line->points = 0;
    h_line->lances = 0;
    h_line->diff_numb = 0;
    return h_line;
}

/******************************************************************************
 * create_plays ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (Plays*) p - Estrutura que contém o tabuleiro de cada lance e
 *                           informações sobre o lance que lhe deu origem
 *
 * DESCRICAO: Cria e inicializa a estrutura onde será armazenada a informação sobre
 *            as jogadas/lances.
 *
 *****************************************************************************/
Plays *create_plays(Head_line *h)
{
    Plays *p = (Plays *)calloc(1, sizeof(Plays));
    if (p == NULL)
        exit(0);
    p->board = create_board(h->L, h->C); /* Cria a tabela com as dimensões pretendidas */
    p->vect = create_conect(h->L * h->C);   /* Estrutura com os vetores de conectividade */
    p->possible_p = NULL;
    p->l = 0;
    p->c = 0;
    p->L = h->L;
    p->lastplay_count = 0;
    p->lastplay_numb = 0;
    return p;
}

/******************************************************************************
 * create_best_score ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (Best_Score*) b - Estrutura que contém informações sobre a melhor
 *                                pontuação alcançada até ao momento
 *
 * DESCRICAO: Cria e inicializa a estrutura onde serão armazenadas informações
 *            sobre a sequencia de jogadas com melhor pontuação.
 *
 *****************************************************************************/
Best_Score *create_best_score()
{
    Best_Score *b = (Best_Score *)calloc(1, sizeof(Best_Score));
    if (b == NULL)
        exit(0);
    b->moves_max = 0;
    b->score_max = 0;
    b->sequence = createList();
    return b;
}

/******************************************************************************
 * create_move ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (Move*) m -Estrutura que contém informações sobre um lance
 *
 * DESCRICAO: Cria e inicializa a estrutura onde serão armazenadas informações
 *            sobre um dos lances possiveis para uma dada parede.
 *
 *****************************************************************************/
Move *create_move()
{
    Move *m = (Move *)calloc(1, sizeof(Move));
    if (m == NULL)
        exit(0);
    m->lance = 0;
    m->lance_points = 0;
    return m;
}

/******************************************************************************
 * create_coordenates ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (Coordenates*) c - Estrutura que contém informações sobre coordenadas
 *
 * DESCRICAO: Cria e inicializa a estrutura onde serão armazenadas informações
 *            sobre coordenadas da sequencia de lances que maximiza os pontos.
 *
 *****************************************************************************/
Coordenates *create_coordenates()
{
    Coordenates *c = (Coordenates *)calloc(1, sizeof(Coordenates));
    if (c == NULL)
        exit(0);
    return c;
}

/******************************************************************************
 * free_play_stuff ()
 *
 * ARGUMENTOS:   (Plays*) p - Estrutura com o tabuleiro de cada lance e
 *                            informações sobre o lance que lhe deu origem
 *
 * RETORNO:      (void)
 *
 * DESCRICAO: Liberta a memória associada ao tabuleiro e à lista que guarda os
 *            lances possíveis para esse tabuleiro.

 *****************************************************************************/
void free_play_stuff(Plays *p)
{
    int i;
    for (i = 0; i < p->L; i++)
    {
        free(p->board[i]);
    }
    free(p->board);
    free_conect(p->vect); /* Liberta a memória associada à conectividade */
    if (p->possible_p != NULL)
        deleteList(p->possible_p, freeListItem);
    free(p);
    return;
}

/******************************************************************************
 * free_best_score ()
 *
 * ARGUMENTOS:   (Best_Score*) b - Estrutura com informações sobre a sequencia
 *                                 de jogadas que maximiza a pontuação
 *
 * RETORNO:      (void)
 *
 * DESCRICAO: Liberta a memória associada à lista de sequência de movimentos
 *            que maximiza a pontuação.
 *
 *****************************************************************************/
void free_best_score(Best_Score *b)
{
    deleteList(b->sequence, freeListItem);
    free(b);
    return;
}

/******************************************************************************
 * freeListItem ()
 *
 * ARGUMENTOS:   (Item) i - Item a ser libertado
 *
 * RETORNO:      (void)
 *
 * DESCRICAO: Liberta a memória associada a um item numa lista.
 *
 *****************************************************************************/
void freeListItem(Item i)
{
    if (i != NULL)
        free(i);
    return;
}