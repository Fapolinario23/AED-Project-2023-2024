/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: list.c
 *
 * DESCRICAO: Ficheiro com funções específicas para a utilização de uma linked
 *            list.
 *
 ******************************************************************************/

#include "list.h"

/******************************************************************************
 * createList ()
 *
 * ARGUMENTOS:
 *
 * RETORNO:     (List*) new - Ponteiro para a estrutura da lista criada
 *
 * DESCRICAO: Função para criar e inicializar uma nova linked list.
 *            Retorna um ponteiro para a lista recém-criada.
 *
 *****************************************************************************/
List *createList()
{
    List *new = (List *)calloc(1, sizeof(List));
    if (new == NULL)
        exit(0);
    new->head = NULL;
    new->tail = NULL;
    return new;
}

/******************************************************************************
 * createNode ()
 *
 * ARGUMENTOS:  (Item) i - Item que será armazenado no novo nó
 *
 * RETORNO:     (Node*) new - Um ponteiro para o novo nó criado
 *
 * DESCRICAO: Função para criar um novo nó com um item especificado.
 *            Retorna um ponteiro para o nó recém-criado.
 *
 *****************************************************************************/
Node *createNode(Item i)
{
    Node *new = (Node *)calloc(1, sizeof(Node));
    if (new == NULL)
        exit(0);
    new->content = i;
    return new;
}

/******************************************************************************
 * deleteList ()
 *
 * ARGUMENTOS:  (List*) l - Lista a ser deletada
 *              (void) (*freeItem)(Item i) - Função para liberar a memória
 *                                           de um item
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função para apagar uma linked list e os seus nós. A função
 *            freeItem é usada para libertar a memória de cada item na lista.
 *
 *****************************************************************************/
void deleteList(List *l, void (*freeItem)(Item i))
{
    Node *aux1 = NULL, *aux2 = NULL;
    aux1 = l->head;
    while (aux1 != NULL)
    {
        freeItem(aux1->content); /* Chama a função para liberar a memória do item */
        aux2 = aux1;
        aux1 = aux1->next;
        free(aux2);
        aux2 = NULL;
    }
    free(l);
    return;
}

/******************************************************************************
 * appendStart ()
 *
 * ARGUMENTOS:  (List*) l - Lista à qual o nó será anexado
 *              (Item) i - Item a ser armazenado no novo nó
 *
 * RETORNO:     (void)
 *
 * DESCRICAO: Função para adicionar um novo nó no início da lista.
 *
 *****************************************************************************/
void appendStart(List *l, Item i)
{
    Node *aux = NULL;
    if (l->head == NULL)
    {
        l->head = createNode(i);
        l->tail = l->head;
        return;
    }
    aux = createNode(i);
    aux->next = l->head;
    l->head = aux;
    return;
}

/******************************************************************************
 * popHead ()
 *
 * ARGUMENTOS:  (List*) l - Lista da qual o primeiro nó será removido
 *
 * RETORNO:     (Item) item_aux - Item armazenado no primeiro nó removido
 *
 * DESCRICAO: Função para remover o primeiro nó da lista e retornar o item
 *            armazenado nele.
 *
 *****************************************************************************/
Item popHead(List *l)
{
    Node *node_aux = NULL;
    Item item_aux = NULL;

    if (l->head == NULL)
        return NULL;

    node_aux = l->head;
    item_aux = node_aux->content;
    l->head = l->head->next;
    free(node_aux);
    node_aux = NULL;
    return item_aux;
}

/******************************************************************************
 * getHead ()
 *
 * ARGUMENTOS:  (List*) l - Lista da qual se deseja obter o primeiro nó
 *
 * RETORNO:     (Node*) l->head - Primeiro nó da lista
 *
 * DESCRICAO: Função para obter o primeiro nó de uma lista.
 *
 *****************************************************************************/
Node *getHead(List *l)
{
    if (l == NULL)
        return NULL;
    return l->head;
}

/******************************************************************************
 * getNext ()
 *
 * ARGUMENTOS:  (Node*) n - Nó do qual se deseja obter o próximo nó
 *
 * RETORNO:     (Node*) n->next - Próximo nó na lista após o nó fornecido
 *
 * DESCRICAO: Função para obter o próximo nó numa linked list.
 *
 *****************************************************************************/
Node *getNext(Node *n)
{
    if (n == NULL)
        return NULL;
    return n->next;
}

/******************************************************************************
 * getItem ()
 *
 * ARGUMENTOS:  (Node*) n - Nó do qual se deseja obter o item
 *
 * RETORNO:     (Item) n->content - Item armazenado no nó fornecido
 *
 * DESCRICAO: Função para obter o item armazenado num nó de uma linked list.
 *
 *****************************************************************************/
Item getItem(Node *n)
{
    if (n == NULL)
        return NULL;
    return n->content;
}