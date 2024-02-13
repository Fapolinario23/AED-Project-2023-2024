/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: problems.c
 *
 * DESCRICAO: Ficheiro com funções reponsáveis pela leitura e resolução dos ficheiros
 *            de entrada.
 *
 ******************************************************************************/

#include "problems.h"

/******************************************************************************
 * read_file ()
 *
 * ARGUMENTOS:   (FILE*) fp_in - Ficheiro a ser lido
 *                (FILE*) fp_out - Ficheiro a ser escrito
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função responsável pela leitura do ficheiro com os problemas
 *            e que chama as funções para a resolução dos mesmos.
 *
 *****************************************************************************/
void read_file(FILE *fp_in, FILE *fp_out)
{
    int i, j, aux = 0;
    Head_line *h_line = create_headline(); /* Cria a estrutura a ser utilizada para guardar informações sobre os problemas */
    Plays *current_play = NULL;

    /* Leitura dos vários cabeçalhos dos problemas */
    while (fscanf(fp_in, "%d %d %d", &h_line->L, &h_line->C, &h_line->v) == 3)
    {                                        /* Guarda a informação do cabeçalho na estrutura criada */
        current_play = create_plays(h_line); /* Cria a estrutura utilizada para guardar as jogadas correntes */
        /* Leitura dos vários elementos das tabelas/paredes caso o enunciado seja válido */
        for (i = 0; i < h_line->L; i++)
        {
            for (j = 0; j < h_line->C; j++)
            {
                if (fscanf(fp_in, "%d", &current_play->board[i][j]) != 1)
                    exit(0);

                /* Verifica a existência de mais de um número distinto na tabela */
                if (h_line->flag == 1)  /* Por absurdo a tabela é toda igual */
                {
                    if (i != 0 || j != 0)
                    {
                        if (aux != current_play->board[i][j])
                            h_line->flag = 0; /* Assim que verifica a existência de 2 números diferentes a tabela já não é toda igual */
                    }
                    aux = current_play->board[i][j];
                }
            }
        }
        proceed_problem(h_line, current_play, fp_in, fp_out); /* Procede-se com a resolução do problema */
    }
    free(h_line);
    return;
}

/******************************************************************************
 * proceed_problem ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Plays*) current_play - Estrutura com o tabuleiro de cada lance
 *                                      e informação sobre o lance que lhe deu
 *                                      origem
 *              (FILE*) fp_in - Ficheiro a ser lido
 *              (FILE*) fp_out - Ficheiro a ser escrito
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função responsável por proceder com verificação e resolução dos
 *            problemas.
 *
 *****************************************************************************/
void proceed_problem(Head_line *h_line, Plays *current_play, FILE *fp_in, FILE *fp_out)
{
    if (verify_problem(h_line, fp_out) == 1) /* Verifica se o problema é válido */
        return; 
    if (verify_prob_size(h_line, fp_out, h_line->L * h_line->C) > 1) /* Apenas resolve o problema se este tiver um tamanho superior a 1 */ 
    { 
        if (verify_full_tab(h_line, fp_out) == 0)   /* Verifica se a tabela está toda preenchida com o mesmo número */
        {                                                        
            problems_solve(fp_in, fp_out, h_line, current_play); /* Resolução de cada problema */
            if (h_line->v != -1 && h_line->v != 0)
                free_board(2, h_line->element_count); /* Liberta a memória de uma tabela com a contagem de número de elementos diferentes */
        }
    }
    /* Reseta todas as variáveis */
    h_line->flag = 1; 
    h_line->points = 0;
    h_line->lances = 0;
    return;
}

/******************************************************************************
 * problems_solve ()
 *
 * ARGUMENTOS:  (FILE*) fp_in - Ficheiro a ser lido
 *              (FILE*) fp_out - Ficheiro a ser escrito
 *              (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Plays*) current_play - Estrutura com o tabuleiro de cada lance
 *                                      e informação sobre o lance que lhe deu
 *                                      origem
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Resolve cada problema do ficheiro com recurso a outras funções.
 *
 *****************************************************************************/
void problems_solve(FILE *fp_in, FILE *fp_out, Head_line *h_line, Plays *current_play)
{
    List *recycling_play = NULL;   /* Estrutura utilizada para reciclar as estruturas com as jogadas, no modo 2 e 3 */
    Best_Score *best_score = NULL; /* Estrutura utilizada para guardar a melhor sequencia de jogadas (Modo 3) */
    Stack *st = NULL;
    int manchas = 0;

    if (h_line->v != -1 && h_line->v != 0)
    {                                    /* Nem a stack nem a lista de reciclagem são necessárias no modo 1, vamos poupar memória com esta verificação */
        st = createStack();              /* Stack com a sequência de jogadas feitas, sendo estas sempre introduzidas na cabeça */
        recycling_play = createList();   /* Lista para recilcar estrutura com tabuleiro e vetores de conectividade */
        help_hope(h_line, current_play); /* Identifica o número de elementos distintos na tabela inicial e conta-os */
    }
    else
        current_play->possible_p = createList(); /* No modo 1 apenas é necessária uma lista para guardar as jogadas */
    if (h_line->v == -3)
        best_score = create_best_score();
    manchas = connect_elements(current_play->vect, h_line, current_play);                              /* Procede à conectividade e verifica se ainda existe alguma mancha */
    current_play->possible_p = spots_identifier(h_line, current_play->vect, current_play->possible_p); /* Identifica todas as manchas possiveis para uma tabela */

    while (1)
    {
        if ((h_line->v <= h_line->points) && (manchas == 0) && (h_line->v != -3)) /* Se já se tiver atingido o objetivo do problema preparamo-nos para escrever a solução */
        { 
            if (h_line->v != -1 && h_line->v != 0)
                push(st, (Item)current_play); /* Coloca-se na stack a última jogada */
            break;                            /* Nota: esta verificação não abrange o modo 3 */
        }
        /* Se os pontos da sequência de jogadas atuais for superior à guardada esta é alterada */
        if ((h_line->v == -3) && (h_line->points > best_score->score_max) && (manchas == 0))
        {
            push(st, (Item)current_play);                                         /* Coloca-se a última jogada na stack para ser possivel a copia das coordenada */
            best_score->sequence = best_score_historical(st, best_score, h_line); /* Introduz a nova seuência de jogadas */
            current_play = (Plays *)pop(st);                                      /* Retira a última jogada da stack */
        }
        if ((h_line->v != -1 && h_line->v != 0) && (current_play->possible_p->head == NULL))
        {
            deleteList(current_play->possible_p, freeListItem); /* Apaga a lista com as jogadas possiveis */
            current_play->possible_p = NULL;
            appendStart(recycling_play, (Item)current_play); /* Coloca a estrutura da última jogada na lista de reciclagem das mesmas */
            if (isEmpty(st)) /* Verifica se ainda existe margem para recoar nas jogadas/stack */
            { 
                break;
            }
            h_line->points -= points(current_play->lastplay_count);                                /* Decrementa os pontos totais feitos */
            h_line->element_count[1][current_play->lastplay_numb] += current_play->lastplay_count; /* Anula o decremento do número de elementos que tinha sido removido */
            current_play = (Plays *)pop(st);                                                       /* Retira a última jogada "válida" da stack */
            h_line->lances--;                                                                      /* Decrementa o Nº de lances realizados */
        }
        else
        {
            if ((h_line->v != -1 && h_line->v != 0) && ThereisHope(h_line, current_play, best_score))
            {                                                       /* Verifica se por o atual caminho de jogadas ainda à esperança de chegar ao objetivo */
                deleteList(current_play->possible_p, freeListItem); /* Apaga a lista com as jogadas possiveis */
                current_play->possible_p = NULL;
                appendStart(recycling_play, (Item)current_play); /* Coloca a estrutura da última jogada na lista de reciclagem das mesmas */
                if (isEmpty(st)) /* Verifica se ainda existe margem para recoar nas jogadas/stack */
                { 
                    break;
                }
                h_line->points -= points(current_play->lastplay_count);                                /* Decrementa os pontos totais feitos */
                h_line->element_count[1][current_play->lastplay_numb] += current_play->lastplay_count; /* Anula o decremento do número de elementos que tinha sido removido */
                current_play = (Plays *)pop(st);                                                       /* Retira a última jogada "válida" da stack */
                h_line->lances--;                                                                      /* Decrementa o Nº de lances realizados */
            }
            else
            {
                current_play = play_make(h_line, current_play, st, recycling_play, current_play->vect);            /* Realiza a jogada */
                manchas = connect_elements(current_play->vect, h_line, current_play);                              /* Procede à conectividade e verifica se ainda existe alguma mancha */
                current_play->possible_p = spots_identifier(h_line, current_play->vect, current_play->possible_p); /* Identifica todas as manchas */
            }
        }
    }
    print_file(h_line, fp_out, st, best_score, current_play); /* Escreve o ficheiro de saída */
    if (h_line->v != -1 && h_line->v != 0)
    {
        deleteStack(st, freeItem);            /* Liberta a Stack */
        deleteList(recycling_play, freeItem); /* Liberta a memória da lista de jogadas */
    }
    else
        free_play_stuff(current_play); /* Liberta a memória necessária no modo 1 */
    if (h_line->v == -3)
        free_best_score(best_score); /* Liberta a memória da estrutura com a melhor sequência de jogada */
    return;
}

/******************************************************************************
 * best_score_historical()
 *
 * ARGUMENTOS:  (Stack*) s - Pilha com histórico de jogadas
 *              (Best_Score*) hist - Lista de histórico de jogadas com coordenadas
 *              (Head_line*) h_line - Estrutura que contém as informações relativas aos problemas
 *
 * RETORNO:     (List*) hist - Lista de histórico de jogadas com coordenadas
 *
 * DESCRICAO: Esta função cria uma lista de coordenadas históricas (uma cópia
 *            do histórico de jogadas), copiando os elementos da pilha em ordem
 *            reversa. As coordenadas são utilizadas para manter o histórico de
 *            lances realizados.
 *
 *****************************************************************************/
List *best_score_historical(Stack *s, Best_Score *hist, Head_line *h_line)
{
    Node *aux = s->head;
    Coordenates *coord = NULL;
    Plays *temp = NULL;

    hist->score_max = h_line->points;         /* Atualiza-se os pontos maximos */
    hist->moves_max = h_line->lances;         /* Atualiza-se os lances */
    deleteList(hist->sequence, freeListItem); /* Liberta a memória da lista de reciclagem de coordenadas */
    hist->sequence = createList();            /* Cria a lista de lances novamente */

    while (aux != NULL)
    {                                 /* Enquanto houver lances a registar */
        coord = create_coordenates(); /* Cria-se a estrutura com as coordenadas */
        temp = (Plays *)getItem(aux); /* Obtém-se o nó da stack */
        coord->l = temp->l;           /* Copia-se as informações */
        coord->c = temp->c;
        appendStart(hist->sequence, (Item)coord); /* Guarda a informação na lista com a melhor jogada */
        aux = getNext(aux);
    }
    return hist->sequence;
}

/******************************************************************************
 * ThereisHope()
 *
 * ARGUMENTOS: (Head_line*) h_line - Estrutura com informações sobre o problema
 *             (Plays*) current_play - Estrutura com o tabuleiro de cada lance
 *             (Best_Score*) best - Estrutura com a melhor sequência de jogadas
 *
 * RETORNO: (bool) 0/1 - Valor booleano que indica se há esperança (1) ou não (0)
 *
 * DESCRICAO: Esta função calcula os pontos associados à mancha no tabuleiro e
 *            verifica se há esperança de vencer o jogo. Ela conta a quantidade
 *            de elementos em cada mancha e calcula os pontos com base nesse número.
 *            Se a pontuação atual acrescida dos pontos da mancha for maior ou igual
 *            à pontuação alvo, retorna 0 (sem esperança), caso contrário,
 *            retorna 1 (esperança).
 *
 *****************************************************************************/
bool ThereisHope(Head_line *h_line, Plays *current_play, Best_Score *best)
{
    int i, pontos = 0;

    for (i = 0; i < h_line->diff_numb; i++)
    { /* Vê os pontos associados à tabela restante, assumindo todos os números iguais na mesma mancha */
        pontos += points(h_line->element_count[1][i]);
        if (h_line->element_count[0][i] == 0)
            break;
    }
    if ((h_line->v <= h_line->points + pontos) && (h_line->v != -3))
        return 0; /* Existe esperança */
    if ((h_line->v == -3) && (h_line->points + pontos > best->score_max))
        return 0;
    return 1; /* Sem esperança */
}

/******************************************************************************
 * help_hope()
 *
 * ARGUMENTOS: (Head_line*) h - Estrutura com informações sobre o problema
 *             (Plays*) p - Estrutura com o tabuleiro de cada lance
 *
 * RETORNO: (int**) h->element_count - Retorna a tabela a ser utilizada para
 *                                     verificar o There Is Hope
 *
 * DESCRICAO: Esta função calcula os pontos associados à mancha no tabuleiro e
 *            verifica se há esperança de vencer o jogo. Ela conta a quantidade
 *            de elementos em cada mancha e calcula os pontos com base nesse número.
 *            Se a pontuação atual acrescida dos pontos da mancha for maior ou igual
 *            à pontuação alvo, retorna 0 (sem esperança), caso contrário,
 *            retorna 1 (esperança).
 *
 *****************************************************************************/
int **help_hope(Head_line *h, Plays *p)
{
    int i, j, k;
    int **aux = create_board(2, h->L * h->C);

    /* Corre a tabela toda e verifica a quantidade de números iguais de cada elemento */
    for (i = 0; i < h->L; i++)
    {
        for (j = 0; j < h->C; j++)
        {
            for (k = 0; k < h->L * h->C; k++)
            {
                if (aux[0][k] == p->board[i][j])
                {
                    aux[1][k]++;
                    break;
                }
                else
                {
                    if (aux[0][k] == 0)
                    {
                        aux[0][k] = p->board[i][j];
                        h->diff_numb++;
                        aux[1][k]++;
                        break;
                    }
                }
            }
        }
    }
    /* Guarda numa tabela o valor do elemento e número destes que existe na tabela toda */
    h->element_count = create_board(2, h->diff_numb);
    for (i = 0; i < h->diff_numb; i++)
    {
        h->element_count[0][i] = aux[0][i];
        h->element_count[1][i] = aux[1][i];
    }
    free_board(2, aux);
    return h->element_count;
}

/******************************************************************************
 * play_make()
 *
 * ARGUMENTOS:  (Head_line*) h - Estrutura com informações sobre o problema
 *              (Plays*) p - Estrutura de jogadas atual
 *              (Stack*) st - Pilha com histórico de jogadas
 *              (List*) recycling - Lista de estruturas para reciclar
 *              (Conect*) vect - Estrutura de conexões entre elementos
 *
 * RETORNO:     (Plays*) p - Estrutura de jogadas atualizada
 *
 * DESCRICAO: Esta função realiza um lance e atualiza a estrutura de jogadas.
 *            Ela encontra a raiz de um elemento conectado, atribui os pontos do
 *            lance, faz a união dos elementos, atualiza o histórico de jogadas
 *            e realiza a verificação da conectividade.
 *
 *****************************************************************************/
Plays *play_make(Head_line *h, Plays *p, Stack *st, List *recycling, Conect *vect)
{
    int root = 0;
    Plays *new = NULL;
    Move *places = (Move *)popHead(p->possible_p); /* Tira a cabeça da lista de jogadas para identificar qual tem que fazer */

    root = find(vect->id, places->lance); /* Procura a raiz do número (conectividade) */
    h->points += places->lance_points;    /* Aumenta os pontos totais obtidos */
    h->lances++;                          /* Aumenta os lances */
    if (h->v != -1 && h->v != 0)
    {
        if (recycling->head != NULL)
            new = (Plays *)popHead(recycling); /* Se a estrutura de reciclagem tiver elementos vai buscar essa memória já alocada */
        else
            new = create_plays(h);                                       /* Caso contrário aloca a memória */
        new->board = copy_board(p->board, new->board, h->L, h->C);       /* Copia o tabuleiro para a estrutura onde vai ser efetuada a jogada */
        new->vect->id = copy_vect(new->vect->id, vect->id, h->L * h->C); /* Copia o vetor dos id para depois conseguir identificar a jogada */
        push(st, (Item)p);                                               /* Volta a colocar a antiga ultima jogada na stack */
        new = isConnected(h, vect, new, root, places->lance);            /* Elimina a mancha */
        free(places);
        return new;
    }
    else
    {
        appendStart(p->possible_p, places);               /* No modo 1 queremos que a jogada permaneça na lista para depois podermos dar print */
        p = isConnected(h, vect, p, root, places->lance); /* Elimina a mancha */
        return p;
    }
    return NULL;
}

/******************************************************************************
 * spots_identifier()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura com informações sobre o problema
 *              (Conect*) vect - Estrutura de conexões entre elementos
 *              (List*) place - Lista de movimentos possíveis
 *
 * RETORNO:     (List*) place - Lista de movimentos possíveis
 *
 * DESCRICAO: Esta função identifica os movimentos possíveis no tabuleiro, considerando
 *            a conectividade dos elementos. Ela cria uma lista de movimentos possíveis
 *            com base no número de manchas no tabuleiro.
 *
 *****************************************************************************/
List *spots_identifier(Head_line *h_line, Conect *vect, List *place)
{
    int i, j, k = 0;
    Move *moves = NULL;
    int root = 0, *aux = aux = create_vect(h_line->L * h_line->C);
    ;

    if (h_line->v != -1 && h_line->v != 0)
        place = createList();

    for (i = h_line->L - 1; i >= 0; i--)
    {
        for (j = 0; j < h_line->C; j++)
        {
            root = find(vect->id, i * h_line->C + j); /* Encontra a raiz de cada elemento a ser visto */
            if ((root <= i * h_line->C + j) && (vect->sz[root] > 1) && (aux[root] == 0))
            { /* Verifica se tem uma mancha e se é a primeira vez a que é acedida */
                moves = create_move();
                moves->lance = i * h_line->C + j;             /* Guarda o id do vetor de conectividade da mancha */
                moves->lance_points = points(vect->sz[root]); /* Guarda o pontos associados à mancha */
                appendStart(place, (Item)moves);              /* Coloca a jogada no inicio da lista */
                if (h_line->v == -1 || h_line->v == 0)
                {
                    free(aux);
                    return place;
                }
                aux[root]++;
                k++;
            }
        }
    }
    free(aux);
    return place;
}

/******************************************************************************
 * isConnected()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém informações sobre o problema
 *              (Conect*) vect - Estrutura com o conjunto de conexões
 *              (Plays*) moves - Estrutura com o tabuleiro de cada lance e informações
 *                               sobre o lance que lhe deu origem
 *              (int) root - Raiz do conjunto de elementos conectados
 *              (int) spot - Elemento que deu origem à mancha
 *
 * RETORNO:     (Plays*) moves - Estrutura de jogadas atualizada
 *
 * DESCRICAO: Esta função atualiza a estrutura de jogadas, marcando os elementos que pertencem
 * à mancha com -1, identificando a coordenada do elemento de origem da mancha e aplicando efeitos
 * gravitacionais ao tabuleiro (vertical e horizontal).
 *
 *****************************************************************************/
Plays *isConnected(Head_line *h_line, Conect *vect, Plays *moves, int root, int spot)
{
    int i, j;

    if (h_line->v != -1 && h_line->v != 0)
    {
        for (i = 0; i < h_line->diff_numb; i++)
        {
            if (moves->board[spot / h_line->C][spot % h_line->C] == h_line->element_count[0][i])
                break;
        }
        moves->lastplay_numb = i; /* Inicialização das variáveis referentes à mancha eliminada na última jogada */
        moves->lastplay_count = 0;
    }

    for (i = h_line->L - 1; i >= 0; i--)
    {
        for (j = 0; j < h_line->C; j++)
        {
            if ((find(vect->id, i * h_line->C + j) == root))
            {
                moves->board[i][j] = -1; /* Colocar a -1 caso pertença à mancha */
                if (h_line->v != -1 && h_line->v != 0)
                {
                    moves->lastplay_count++;
                    h_line->element_count[1][moves->lastplay_numb]--;
                }
                if (i * h_line->C + j == spot) /* Identifica a coordenada de um elemento da mancha */
                { 
                    moves->l = h_line->L - i;
                    moves->c = j + 1;
                }
            }
        }
    }
    gravity_vertical(h_line, moves);   /* Efeito gravitacional vertical */
    gravity_horizontal(h_line, moves); /* Efeito gravitacional horizontal */
    return moves;
}

/******************************************************************************
 * connect_elements()
 *
 * ARGUMENTOS:  (Conect*) vect - Estrutura com o conjunto de conexões
 *              (Head_line*) h_line - Estrutura com informações sobre o problema
 *              (Plays*) move - Estrutura com o tabuleiro de cada lance e informações
 *                              sobre o lance que lhe deu origem
 *
 * RETORNO:     (int) manchas - Número de manchas no tabuleiro
 *
 * DESCRICAO: Esta função conecta os elementos do tabuleiro, determinando quantas "manchas" existem.
 *            Ela inicializa os representantes de cada elemento e o tamanho das componentes.
 *            Em seguida, itera sobre os elementos do tabuleiro, verificando a conectividade
 *            e unindo componentes. Finalmente, conta o número de manchas identificando
 *            os elementos raiz de cada componente conectada.
 *
 *****************************************************************************/
int connect_elements(Conect *vect, Head_line *h_line, Plays *move)
{
    int i, j, ID, manchas = 0;

    for (i = h_line->L - 1; i >= 0; i--)
    {
        for (j = 0; j < h_line->C; j++)
        {
            ID = i * h_line->C + j;
            vect->id[ID] = ID; /* Cada elemento é seu próprio representante inicialmente */
            vect->sz[ID] = 1;  /* Inicialmente, cada componente tem tamanho 1 */

            /* Verifica se o elemento pretendido é diferente de -1 para não realizar manchas destes */
            /* Verificando depois se o elemento atual pertence à mesma mancha do pretendido */
            if (move->board[i][j] != -1)
            {

                /* Coloca na lista de adjacências se o vértice for igual ao de cima */
                if (i < h_line->L - 1)
                {
                    if (move->board[i][j] == move->board[i + 1][j])
                    {
                        unionComponents(vect, ID, ID + h_line->C); /* Realiza a união dos elementos */
                        manchas = 1;
                    }
                }

                /* Coloca na lista de adjacências se o vértice for igual ao da esquerda */
                if (j >= 1)
                {
                    if (move->board[i][j] == move->board[i][j - 1])
                    {
                        unionComponents(vect, ID, ID - 1); /* Realiza a união dos elementos */
                        manchas = 1;
                    }
                }
            }
        }
    }
    return manchas;
}

/******************************************************************************
 * gravity_vertical ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre o problema a resolver
 *              (Plays*) p - Estrutura com o tabuleiro de cada lance e
 *                           informações sobre o lance que lhe deu origem
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função responsável pela gravidade vertical.
 *
 *****************************************************************************/
void gravity_vertical(Head_line *h_line, Plays *p)
{
    int x, y, k;

    /* Verifica a existência de -1 */
    for (y = 0; y < h_line->C; y++)
    {
        for (x = h_line->L - 1; x >= 0; x--)
        {
            if (p->board[x][y] == -1)
            {
                k = 0;
                while (k <= x)
                {
                    if (p->board[x - k][y] != -1)
                    { /* Equanto encontra -1 na coluna shifta os elementos para baixo */
                        p->board[x][y] = p->board[x - k][y];
                        p->board[x - k][y] = -1;
                        break;
                    }
                    k++;
                }
            }
        }
    }
    return;
}

/******************************************************************************
 * gravity_horizontal ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre o problema a resolver
 *              (Plays*) p - Estrutura com o tabuleiro de cada lance e
 *                           informações sobre o lance que lhe deu origem
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função responsável pela gravidade horizontal.
 *
 *****************************************************************************/
void gravity_horizontal(Head_line *h_line, Plays *p)
{
    int x, y, j, zero_column_found, numb_cols = 0;

    /* Verifica se há colunas totalmente com -1 e realiza o deslocamento */
    for (y = h_line->C - 1; y >= numb_cols;)
    {
        zero_column_found = 1; /* Por absurdo assume-se que a coluna contém apenas -1 inicialmente */

        /* Verifica se efetivamente a coluna apenas contém -1 */
        for (x = 0; x < h_line->L; x++)
        {
            if (p->board[x][y] != -1)
            {
                zero_column_found = 0; /* A coluna contém pelo menos um número diferente de -1 */
                y--;
                break;
            }
        }

        /* Se uma coluna contiver apenas -1, faz um shift para a direita de todas as colunas à sua esquerda */
        if (zero_column_found == 1)
        {
            numb_cols++;
            for (j = y; j >= 0; j--)
            {
                for (x = 0; x < h_line->L; x++)
                {
                    if (j >= 1)
                    {
                        p->board[x][j] = p->board[x][j - 1];
                    }
                }
            }
        }
    }

    /* O número de colunas que existiam apenas com -1 são colocadas no início da tabela */
    for (y = 0; y < numb_cols; y++)
    {
        for (x = 0; x < h_line->L; x++)
        {
            p->board[x][y] = -1;
        }
    }
    return;
}