/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: verifications.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a verificação dos problemas
 *            em questão e das soluções dos mesmos.
 * 
 ******************************************************************************/

#include "verifications.h"

/******************************************************************************
 * verify_full_tab ()
 *
 * ARGUMENTOS:  (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *              (FILE *) fp - Ficheiro a ser escrito 
 * 
 * RETORNO:      0 caso o tabuleiro não preencha qualquer um dos 2 requisitos
 * 
 * DESCRICAO:
 * 
 *****************************************************************************/
int verify_full_tab (Head_line *h_line, FILE *fp)
{
    int i, j;

    /* Verifica se a tabela é unicamente constituida pelo número pretendito */
    if (h_line -> flag == 1){
        h_line -> points = points (h_line -> L * h_line -> C);

        /* Escreve os resultados para este caso específico */
        /* Escreve o cabeçalho */
        fprintf (fp, "%d %d %d %d %d\n", h_line -> L, h_line -> C, h_line -> v, h_line -> l, h_line -> c);  

        /* Escreve o número de pontos no modo 1 */
        if (h_line -> v == 1) fprintf (fp, "%d\n\n", h_line -> points);                     
        
        /* Escreve o número da tabela no modo 2 */  
        if (h_line -> v == 2){                                                              
            for (i = 0; i < h_line -> L; i++){
                for (j = 0; j < h_line -> C; j++) fprintf (fp, "-1 ");     
                fprintf (fp, "\n");
            }                                  
        fprintf (fp, "\n");
        }
    }
    return h_line -> flag;
}

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
 * DESCRICAO: Verifica se o problema é válido.
 * 
 *****************************************************************************/
int verify_problem (Head_line *h_line, FILE *fp)
{
    if ((h_line -> l < 1) || (h_line -> l > h_line -> L) || (h_line -> c < 1) || (h_line -> c > h_line -> C) || ((h_line -> v != 1) && (h_line -> v != 2))){
        fprintf (fp, "%d %d %d %d %d\n\n", h_line -> L, h_line -> C, h_line -> v, h_line -> l, h_line -> c);
        return 1;
    }
    return 0;
}

/******************************************************************************
 * verify_isolation ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (FILE*) fp - Ficheiro a ser escrito
 * 
 * RETORNO:      (int) 0/1 - Retorna 0 caso o problema seja válido e 1 caso 
 *                          contrário
 * 
 * DESCRICAO: Verifica se a coordenada pretendida está ou não isolada.
 * 
 *****************************************************************************/
int verify_isolation (Head_line *h_line, FILE *fp)
{
    /* Verifica se existe adjacente está em baixo */
    if (h_line -> L - h_line -> l - 1 >= 0){            
        if (h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == h_line -> board[h_line -> L - h_line -> l - 1][h_line -> c - 1]) return 0;
    }
    /* Verifica se existe adjacente está em cima */
    if (h_line -> L - h_line -> l + 1 < h_line -> L){
        if (h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == h_line -> board[h_line -> L - h_line -> l + 1][h_line -> c - 1]) return 0;
    }
    /* Verifica se existe adjacente está à esquerda */
    if (h_line -> c - 2 >= 0){
        if (h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == h_line -> board[h_line -> L - h_line -> l][h_line -> c - 2]) return 0;
    }
    /* Verifica se existe adjacente está à direita */
    if (h_line -> c < h_line -> C){
        if (h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == h_line -> board[h_line -> L - h_line -> l][h_line -> c]) return 0;
    }
    print_wout_alt (h_line, fp);        /* Escreve o ficheiro de saída dando 0 pontos ou o tabuleiro dado à entrada */
    return 1;
}

/******************************************************************************
 * verify_numb ()
 *
 * ARGUMENTOS:   (Head_line*) h_line - Estrutura que contém toda a informação
 *                                    sobre os problemas a resolver
 *               (FILE*) fp - Ficheiro a ser escrito
 * 
 * RETORNO:      (int) 0/1 - Retorna 0 caso o problema seja válido e 1 caso 
 *                          contrário
 * 
 * DESCRICAO: Verifica se o número da coordenada pretendida é diferente de -1.
 * 
 *****************************************************************************/
int verify_numb (Head_line *h_line, FILE *fp)
{
    if (h_line -> board[h_line -> L - h_line -> l][h_line -> c - 1] == -1){
        print_wout_alt (h_line, fp);        /* Escreve o ficheiro de saída dando 0 pontos ou o tabuleiro dado à entrada */
        return 1;
    }
    return 0;
}
