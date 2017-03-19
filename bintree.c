#include "bintree.h"

node* fgrowTree(FILE* fp) {
  int a;

  // создание корня дерева
  if(!fscanf(fp, "%d", &a)) return NULL;
  node* head = allocNode(a);
  if(!head) return NULL;

  // заполнение нодами
  while((int)fgetc(fp) != -1) {
    if(fscanf(fp, "%d", &a)) {
      if(!addNode(head, a)) {
        freeTree(head);
        return NULL;
      }
    }
  }

  return head;
}

node* allocNode(int value) {
  node* new = (node*)malloc(sizeof(node));
  if(!new) return NULL;

  new->val = value;
  new->counter = 1;
  new->r = NULL;
  new->l = NULL;

  return new;
}

int addNode(node* head, int value) {
  node *p_new, *p_near;
  p_near = findNode(head, value);

  if(p_near->val == value) {
    p_near->counter++;
    return 2;
  } else {
    p_new = allocNode(value);

    // printf("%d %d\n", p_near->r, p_near->l);
    if(p_near->val < value) {
      p_near->r = p_new;
    } else {
      p_near->l = p_new;
    }
  }

  return 1;
}

node* findNode(node* current, int target) {
  while (1) {
    if(current->val == target) break;

    if(current->val < target) {
      if(!current->r) break;
      current = current->r;
    } else {
      if(!current->l) break;
      current = current->l;
    }
  }

  return current;
}

int fwriteNodeSorted(FILE* fp, node* head) {
  if(head->l) fwriteNodeSorted(fp, head->l);

  for(int i = 0; i < head->counter; i++)
    if(!fprintf(fp, "%d ", head->val)) return 0;

  if(head->r) fwriteNodeSorted(fp, head->r);

  return 1;
}

void freeTree(node* head) {
  if(head->l) freeTree(head->l);
  if(head->r) freeTree(head->r);
  free(head);

  return;
}
