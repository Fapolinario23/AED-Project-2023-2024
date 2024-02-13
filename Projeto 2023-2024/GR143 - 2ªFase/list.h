/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: list.h
 *
 * DESCRICAO: Contém as funções do list.c
 *
 ******************************************************************************/

#ifndef _H_LIST
#define _H_LIST

#include <stdio.h>
#include <stdlib.h>
#include "Item.h"

/* Estrutura com os nós da lista */
typedef struct _node
{
    Item content;       /* Informação guardada */
    struct _node *next; /* Pointer para o próximo nó */
} Node;

/* Estrutura com a LinkedList */
typedef struct _linkedList
{
    struct _node *head; /* Cabeça da lista */
    struct _node *tail; /* Último elemento da lista */
} List;

List *createList();
Node *createNode(Item);
void deleteList(List *, void (*freeItem)(Item));
void appendStart(List *, Item);
Item popHead(List *);
Node *getHead(List *);
Node *getNext(Node *);
Item getItem(Node *);

#endif