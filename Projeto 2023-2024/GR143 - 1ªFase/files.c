/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: files.c
 *
 * DESCRICAO: Ficheiro com funções reponsáveis pela leitura, resolução e escrita
 *            dos ficheiros de entrada/saída.
 * 
 ******************************************************************************/

#include "files.h"

/******************************************************************************
 * read_file ()
 *
 * ARGUMENTOS:   (FILE*) fp_in - Ficheiro a ser lido
*                (FILE*) fp_out - Ficheiro a ser escrito
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função responsável pela leitura do ficheiro com os problemas 
 *              e que chama as funções para a resolução dos mesmos.
 * 
 *****************************************************************************/
void read_file (FILE *fp_in, FILE *fp_out)
{
    int  i, j, aux = 0, cabecalho[5];
    Head_line *h_line = NULL;

    /* Leitura dos vários cabeçalhos dos problemas */
    while (fscanf(fp_in, "%d %d %d %d %d", &cabecalho[0],&cabecalho[1],&cabecalho[2],&cabecalho[3],&cabecalho[4]) == 5){
        h_line = create_struct (h_line);            /* Cria a estrutura a ser utilizada para guardar informações sobre os problemas */
        h_line = save_h_line (h_line, cabecalho);   /* Guarda a informação do cabeçalho na estrutura criada */
        h_line -> board = create_board (cabecalho[0], cabecalho[1]);    /* Cria a tabela com as dimenções pretendidad */

        /* Leitura dos vários elementos das tabelas/paredes */
        for (i = 0; i < cabecalho[0]; i++){
            for (j = 0; j < cabecalho[1]; j++){
                if (fscanf(fp_in, "%d", &h_line -> board[i][j]) != 1) exit (0);
                /* Verifica a existência de mais de um número distinto na tabela */
                if (h_line -> flag == 1){           /* Por absurdo a tabela é toda igual */
                    if (i != 0 || j != 0){
                        if (aux != h_line -> board[i][j]) h_line -> flag = 0;
                    }
                    aux = h_line -> board[i][j];
                }
            } 
        }
        problems_solve (fp_in,fp_out,h_line);        /* Resolve os problemas */
    }
    return;
}

/******************************************************************************
 * isConnected ()
 *
 * ARGUMENTOS:  (Head_line *) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Conect *) conected - Estrutura com o conjunto
 *              (int) start - ID do ponto cujas coordenada são dadas 
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função identifica a mancha.
 * 
 *****************************************************************************/
void isConnected (Head_line *h_line, Conect *vect, int start)
{
    int i, j;
    int rootP = find (vect -> id , start);
    
    for (i = 0; i < h_line -> L; i++) {
        for (j = 0; j < h_line -> C; j++){
            if (find(vect -> id, i*h_line -> C + j) == rootP && i*h_line -> C + j != start) {
                h_line -> board[i][j] = -1;                     /* Colocar a -1 caso pertença à mancha */
            }
        }
    }
    h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] = -1;   /* Colocar o elemento pedido a -1 */
    update_board (h_line);
    return;
}

/******************************************************************************
 * print_file ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Graph *)  graph - Grafo que possui a lista de adjacências
 *              (FILE *) fp - Ficheiro a ser escrito 
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função geral de escrita do ficheiro de saída.
 * 
 *****************************************************************************/
void print_file (Head_line *h_line , FILE *fp)
{
    int i, j;

    /* Escreve o cabeçalho */
    fprintf (fp, "%d %d %d %d %d\n", h_line -> L, h_line -> C, h_line -> v, h_line -> l, h_line -> c);

    /* Escreve o número de pontos no modo 1 */
    if (h_line -> v == 1) fprintf (fp, "%d\n\n", h_line -> points);   

    /* Escreve o número da tabela no modo 2 */  
    if (h_line -> v == 2){
        /* update_board (graph, h_line); */       /* Atualiza a tabela após a remoção da mancha */
        for (i = 0; i < h_line -> L; i++){
            for (j = 0; j < h_line -> C; j++){
                fprintf (fp, "%d ", h_line -> board[i][j]);
            }
            fprintf (fp, "\n");
        }
        fprintf (fp, "\n");
    }
    return;
}

/******************************************************************************
 * other_cases ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (Graph *)  graph - Grafo que possui a lista de adjacências
 * 
 * RETORNO:     (int) start - ID do vértice a começar (coordenadas pretendidas)
 * 
 * DESCRICAO: Adiciona os vários elementos da tabela cujo número seja igual ao
 *            da cordenada inicial à lista de adjacências.
 * 
 *****************************************************************************/
void other_cases (Conect *vect, Head_line *h_line)
{
    int i, j, ID = 0;
    
    for (i = 0; i < h_line -> L; i++){
        for (j = 0; j < h_line -> C; j++){
            /* Verifica se o elemento da tabela em questão é igual ao pretendido */
            if ((h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == h_line -> board[i][j])){

                /* Coloca na lista de adjacências se o vértice for igual ao de cima */
                if (i >= 1){
                    if (h_line -> board[i][j] == h_line -> board[i - 1][j]) unionComponents(vect, ID, ID - h_line -> C);
                }

                /* Coloca na lista de adjacências se o vértice for igual ao da esquerda */
                if (j >= 1){
                    if (h_line -> board[i][j] == h_line -> board[i][j - 1]) unionComponents(vect, ID, ID - 1);
                }
            }
            ID++;
        }
    }
    return;               
}

/******************************************************************************
 * problems_solve ()
 *
 * ARGUMENTOS:  (FILE*) fp_in - Ficheiro a ser lido
 *              (FILE*) fp_out - Ficheiro a ser escrito
 *              (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Resolve cada problema do ficheiro com recurso a outras funções.
 * 
 *****************************************************************************/
void problems_solve (FILE *fp_in, FILE *fp_out, Head_line *h_line)
{
    Conect *vect = NULL;
    int c_init = (h_line -> L - h_line -> l)*h_line -> C + h_line -> c - 1;         /* ID das coordendas dadas inicialmente */
      
    if (verify_problem (h_line, fp_out) == 0){                                      /* Verifica se o problema é válido */
        if (verify_numb (h_line, fp_out) == 0){                                     /* Verifica se a posição dada contém um número e não -1 */
            if (verify_isolation (h_line, fp_out) == 0){                            /* Verifica se a coordenada está isolada (não tem adjacências) */
                if (verify_full_tab (h_line, fp_out) == 0){                         /* Verifica se a tabela está toda preenchida com o mesmo número */
                    vect = initialize (vect, h_line -> L*h_line -> C);              /* Cria e inicializa a estrutura utilizada para a conectividade */
                    other_cases(vect, h_line);                                      /* No caso de não ser um problema flagrante procede-se à conectividade */
                    isConnected (h_line, vect, c_init);                             /* Verifica a mancha e coloca-a a -1 */
                    h_line -> points = points (vect -> sz[vect -> id[c_init]]);     /* Cálcula o número de pontos associados à mancha */
                    print_file (h_line, fp_out);                                    /* Escreve o ficheiro de saída */
                    free_conect (vect);                                             /* Liberta a memória associada à conectividade */            
                }
            }
        }
    }
    free_struct (h_line);                                                           /* Liberta a memória alocada para a estrutura que contém a informação do problema */
    return;
}

/******************************************************************************
 * print_wout_alt ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (FILE*) fp - Ficheiro a ser escrito
 * 
 * RETORNO:      (void)
 * 
 * DESCRICAO: Escreve o ficheiro de saída em casos especificos, escrevendo 0
 *            pontos ou o ficheiro de entrada dependendo do modo de jogo.
 * 
 *****************************************************************************/
void print_wout_alt (Head_line *h_line, FILE *fp)
{
    int i, j;

    /* Escreve o cabeçalho */
    fprintf (fp, "%d %d %d %d %d\n", h_line -> L, h_line -> C, h_line -> v, h_line -> l, h_line -> c);

    /* Escreve o número de pontos no modo 1 */
    if (h_line -> v == 1) fprintf (fp, "0\n\n");

    /* Escreve o número da tabela no modo 2 */
    if (h_line -> v == 2){
        for (i = 0; i < h_line -> L; i++){
            for (j = 0; j < h_line -> C; j++){
                fprintf (fp, "%d ", h_line -> board[i][j]);
            }
            fprintf (fp, "\n");
        }
        fprintf (fp, "\n");
    }
    return;
}