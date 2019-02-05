#include <stdio.h>

#include "bintree.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "Incorrect arguments\n");
    return EXIT_FAILURE;
  }

  FILE* f_from = fopen(argv[1], "r");
  if(!(f_from)) {
    fprintf(stderr, "Error while openning imput file\n");
    return EXIT_FAILURE;
  }

  FILE* f_to = fopen(argv[2], "w");

  if(!(f_to)) {
    fprintf(stderr, "Error while creating\\openning output file\n");
    fclose(f_from);
    return EXIT_FAILURE;
  }

  node* head = fgrowTree(f_from);
  if(!head) {
    fprintf(stderr, "Error while creating a tree\n");
    return EXIT_FAILURE;
  }
  fclose(f_from);

  if(!fwriteNodeSorted(f_to, head)) {
    fprintf(stderr, "Error while writing file\n");
    return EXIT_FAILURE;
  }
  fclose(f_to);

  freeTree(head);
  return EXIT_SUCCESS;
}
