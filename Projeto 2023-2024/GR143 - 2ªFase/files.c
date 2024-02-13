/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: files.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a verificação de problemas
 *            e escrita de ficheiros de saída.
 *
 ******************************************************************************/

#include "files.h"

/******************************************************************************
 * verify_problem ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (FILE*) fp - Ficheiro a ser escrito
 *
 * RETORNO:      (int) 0/1 - Retorna 0 caso o problema seja válido e 1 caso
 *                          contrário
 *
 * DESCRICAO: Verifica se o problema é válido, isto é, está bem posto.
 *
 *****************************************************************************/
int verify_problem(Head_line *h_line, FILE *fp)
{
    /* Verifica se o problema é válido */
    if ((h_line->L > 0) && (h_line->C > 0) && ((h_line->v >= 0) || (h_line->v == -1) || (h_line->v == -3)))
        return 0;
    fprintf(fp, "%d %d %d\n\n", h_line->L, h_line->C, h_line->v);
    return 1;
}

/******************************************************************************
 * verify_full_tab ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (FILE *) fp - Ficheiro a ser escrito
 *
 * RETORNO:     (int) h_line -> flag - 1/0 se a tabela é/não é constituida por
 *                                     uma só mancha
 *
 * DESCRICAO: Função responsável por verificar se toda a tabela é uma só mancha
 *            e apresentar a respetiva solução, caso isto se verifique.
 *
 *****************************************************************************/
int verify_full_tab(Head_line *h_line, FILE *fp)
{
    /* Verifica se a tabela é unicamente constituida por uma mancha */
    if (h_line->flag == 1)
    {
        h_line->points = points(h_line->L * h_line->C); /* Pontos máximos associados à tabela */
        /* Escreve os resultados para este caso específico */
        fprintf(fp, "%d %d %d\n", h_line->L, h_line->C, h_line->v); /* Escreve o cabeçalho */
        if (h_line->v > h_line->points)
            fprintf(fp, "%d %d\n\n", 0, -1); /* Apenas se verifica no Modo 2, quando a tabela no total não tem os pontos mínimos */
        else
            fprintf(fp, "%d %d\n\n", 1, h_line->points); /* A mancha elimina-se apenas num lance e tem os pontos associados à tabela */
        return h_line->flag;
    }
    return h_line->flag;
}

/******************************************************************************
 * verify_prob_size ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (FILE*) fp - Ficheiro a ser escrito
 *               (int) i - Tamanho da tabela
 *
 * RETORNO:      (int) i - Tamanho da tabela
 *
 * DESCRICAO: Verifica se a tabela tem tamanho unitário, se sim não há manchas
 *            a avaliar e escreve a solução no ficheiro de saída.
 *
 *****************************************************************************/
int verify_prob_size(Head_line *h_line, FILE *fp, int i)
{
    /* Verifica se a tabela têm tamanho unitário */
    if (i == 1)
    {
        /* Escreve os resultados para este caso específico */
        fprintf(fp, "%d %d %d\n", h_line->L, h_line->C, h_line->v); /* Escreve o cabeçalho */
        fprintf(fp, "%d %d\n\n", 0, 0);                             /* Printa o nº de lances e pontos, neste caso 0, pois não existem manchas */
    }
    return i;
}

/******************************************************************************
 * points ()
 *
 * ARGUMENTOS:   (int) numb - Tamanho da mancha
 *
 * RETORNO:      (int*) - Pontos associados à mancha -> numb*(numb - 1)
 *
 * DESCRICAO: Calcula os pontos associados à mancha.
 *
 *****************************************************************************/
int points(int numb)
{
    return numb * (numb - 1);
}

/******************************************************************************
 * print_file ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Stack *) st - Stack com o conjunto de lances
 *              (FILE *) fp - Ficheiro a ser escrito
 *              (Best_Score*) best - Estrutura que guarda as informações 
 *                                   relativas à sequencia de jogadas que 
 *                                   maximiza os pontos
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função de escrita do ficheiro de saída em caso de o problema
 *            ser resolvido através de algoritmia.
 *
 *****************************************************************************/
void print_file(Head_line *h_line, FILE *fp, Stack *st, Best_Score *best, Plays *play)
{
    fprintf(fp, "%d %d %d\n", h_line->L, h_line->C, h_line->v); /* Escreve o cabeçalho */
    if (h_line->v == -1 || h_line->v == 0)
    {                                                           /* Modo 1 */
        fprintf(fp, "%d %d\n", h_line->lances, h_line->points); /* Printa o nº de lances e pontos */
        print_list_plays(fp, play->possible_p->head, h_line);   /* Printa a lista de jogadas do fim para o início */
    }
    if (h_line->v > 0)                                          /* Modo 2 */
    { 
        if (h_line->v > h_line->points)
            fprintf(fp, "%d %d\n", 0, -1);                      /* Diz que não existe solução */
        else
        {
            fprintf(fp, "%d %d\n", h_line->lances, h_line->points); /* Printa os lances e pontos feitos caso haja solução */
            print_stack_reverse(st, fp);                            /* Printa a Stack do fim para o início */
        }
    }
    if (h_line->v == -3)
    {                                                             /* Modo 3 */
        fprintf(fp, "%d %d\n", best->moves_max, best->score_max); /* Printa os lances e pontos feitos na melhor solução */
        print_best_score(fp, best);                               /* Printa a sequência de lances que proporciona a melhor jogada */
    }
    fprintf(fp, "\n");
    return;
}

/******************************************************************************
 * print_list_plays ()
 *
 * ARGUMENTOS:  (Node*) node - Estrutura com os nós da lista
 *              (FILE*) fp - Ponteiro para o arquivo onde a pilha será impressa
 *              (Head_line*) h - Estrutura que contém as informações relativas aos problemas
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função para imprimir os elementos da lista em ordem reversa num
 *            ficheiro.
 *
 *****************************************************************************/
void print_list_plays(FILE *fp, Node *node, Head_line *h)
{
    Move *move = NULL;
    if (node == NULL)
    {
        return;
    }

    print_list_plays(fp, node->next, h); /* Printa a lista de jogadas em ordem inversa */
    move = (Move *)getItem(node);
    if ((h->L - move->lance / h->C != 0) && (move->lance % h->C + 1 != 0))
    {                                                                              /* Para não imprimir o primeiro elemento a ser colocado na pilha (informação do tabuleiro original) */
        fprintf(fp, "%d %d\n", h->L - move->lance / h->C, move->lance % h->C + 1); /* Imprime apenas os lances que surgiram de outro lance */
    }
    return;
}

/******************************************************************************
 * print_stack_reverse ()
 *
 * ARGUMENTOS:  (Stack*) s - Pilha a ser impressa em ordem reversa
 *              (FILE*) fp - Ponteiro para o arquivo onde a pilha será impressa
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função para imprimir os elementos da pilha em ordem reversa num
 *            ficheiro.
 *
 *****************************************************************************/
void print_stack_reverse(Stack *s, FILE *fp)
{
    if (isEmpty(s))
    {
        return;
    }
    Plays *element = (Plays *)pop(s); /* Remove o elemento do topo da pilha */
    print_stack_reverse(s, fp);       /* Chama-se recursivamente */
    if ((element->l != 0) && (element->c != 0))
    {                                                   /* Para não imprimir o primeiro elemento a ser colocado na pilha (informação do tabuleiro original) */
        fprintf(fp, "%d %d\n", element->l, element->c); /* Imprime apenas os lances que surgiram de outro lance */
    }
    push(s, (Item)element); /* Coloca o elemento de volta na pilha */
    return;
}

/******************************************************************************
 * print_best_score()
 *
 * ARGUMENTOS: (FILE*) fp - Ficheiro a ser escrito
 *             (Best_Score*) best - Estrutura com a melhor sequência de jogadas
 *
 * RETORNO: (void)
 *
 * DESCRICAO: Esta função imprime a melhor sequência de jogadas em um arquivo,
 *            representando as coordenadas (linhas e colunas) das jogadas. Ela
 *            itera sobre a lista de coordenadas na estrutura `Best_Score` e
 *            escreve as coordenadas no arquivo, linha por linha.
 *
 *****************************************************************************/
void print_best_score(FILE *fp, Best_Score *best)
{
    Node *aux = best->sequence->head;
    Coordenates *temp = NULL;

    while (aux != NULL)
    {
        temp = (Coordenates *)getItem(aux);
        if ((temp->l != 0) || (temp->c != 0))
        {                                             /* Para não imprimir o primeiro elemento a ser colocado na pilha (informação do tabuleiro original) */
            fprintf(fp, "%d %d\n", temp->l, temp->c); /* Imprime apenas os lances que surgiram de outro lance */
        }
        aux = getNext(aux);
    }
    return;
}

/******************************************************************************
 * freeItem ()
 *
 * ARGUMENTOS:  (Item) i - O item a ser libertado
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função para libertar a memória de um item da pilha.
 *
 *****************************************************************************/
void freeItem(Item i)
{
    free_play_stuff((Plays *)i);
    return;
}