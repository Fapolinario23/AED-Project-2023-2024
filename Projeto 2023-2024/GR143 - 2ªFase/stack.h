/******************************************************************************
 * (C) Algoritmos e Estrutura de Dados 2023/2024
 *
 * AUTORES: Francisco Apolinário
 *          Neelam Visueshcumar
 *
 * NOME: stack.h
 *
 * DESCRICAO: Contém as funções do stack.c
 *
 ******************************************************************************/

#ifndef _H_STACK
#define _H_STACK

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Item.h"
#include "list.h"

typedef List Stack;

bool isEmpty(Stack *);
Stack *createStack();
void deleteStack(Stack *, void (*freeItem)(Item));
void push(Stack *, Item);
Item pop(Stack *);

#endif
