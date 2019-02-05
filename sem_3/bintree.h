#ifndef _BINTREE_H
#define _BINTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree_node {
  int val;
  int counter;
  struct binary_tree_node* l;
  struct binary_tree_node* r;
} node;

// Делает дерево. Прининимает указатель на файл с исходными данными, возвращает указатель на корень
node* fgrowTree(FILE* fp);

// Добавляет ноду в дерево. Если нода с val уже была в дереве, увеличивает counter на 1
// 1 - allocated, 2 - incremented, 0 - error
int addNode(node* head, int value);

// Выделяет память под одну новую ноду и инициализирует значениями поля
node* allocNode(int value);

// Просматривает дерево и возвращает либо указатель на нужную ноду, либо, если не нашел, на ноду, после которой может идти нода с искомым val
node* findNode(node* current, int target);

// Рекурсивно просматривает дерево по порядку (левая ветвь) - (значение) - (правая ветвь) и печатает
int fwriteNodeSorted(FILE *fp, node* head);

// Освобождение памяти, занятой нодами
void freeTree(node* head);

#endif
