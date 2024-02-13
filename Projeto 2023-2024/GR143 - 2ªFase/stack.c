/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 * 
 * AUTORES: Francisco Apolinário 
 *          Neelam Visueshcumar
 * 
 * NOME: stack.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a utilização de uma stack.
 * 
 ******************************************************************************/

#include "stack.h"

/******************************************************************************
 * isEmpty ()
 *
 * ARGUMENTOS:  (Stack*) s - Stack com as jogadas
 * 
 * RETORNO:     (bool) - Retorna verdadeiro se a pilha estiver vazia, senão, 
 *                       retorna falso.
 * 
 * DESCRICAO: Função para verificar se a pilha está vazia.

 *****************************************************************************/
bool isEmpty(Stack* s)
{
    return s->head == NULL;
}

/******************************************************************************
 * createStack ()
 *
 * ARGUMENTOS:  
 * 
 * RETORNO:     (Stack*) s - Ponteiro para a pilha de jogadas recém-criada
 * 
 * DESCRICAO: Função para criar e inicializar uma nova pilha de jogadas.
 * 
 *****************************************************************************/
Stack *createStack()
{
    return (Stack*) createList();
}

/******************************************************************************
 * deleteStack ()
 *
 * ARGUMENTOS:  (Stack*) s - Pilha a ser apagada
 *              (void) (*freeItem)(Item i) - Função para libertar a memória 
 *                                           de um item
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função para excluir uma pilha de jogadas e seus nós.
 *            A função freeItem é usada para libertar a memória de cada item na 
 *            pilha.
 * 
 *****************************************************************************/
void deleteStack(Stack *s, void (*freeItem)(Item i))
{
    deleteList((List*)s, freeItem);
    return;
}

/******************************************************************************
 * push ()
 *
 * ARGUMENTOS:  (Stack*) s - Pilha à qual o item será adicionado
 *              (Item) i - Item a ser armazenado na pilha
 * 
 * RETORNO:     (void)
 * 
 * DESCRICAO: Função para adicionar um item no topo da pilha.
 * 
 *****************************************************************************/
void push(Stack *s, Item i)
{
    appendStart((List*)s, i);
    return;
}

/******************************************************************************
 * pop ()
 *
 * ARGUMENTOS:  (Stack*) s - Pilha da qual o item no topo será removido
 * 
 * RETORNO:     (Item) i - Item no topo da pilha
 * 
 * DESCRICAO: Função para remover o item no topo da pilha e retorná-lo.
 * 
 *****************************************************************************/
Item pop(Stack *s)
{
    return popHead((List*)s);
}