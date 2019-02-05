#include <stdio.h>
#include <stdlib.h>

/*
  Ломачев С. PREP-12
  Вариант 11

  Алгоритм: d (L-норма)
  Формат хранения в файле: 1 (неразреженный)
  Внутреннее представление: 2 (разреженное)
*/

#include "matrix.h"

double calculateLNorm(const matrix_elem* matrix);

int testMatrixH(matrix_elem* matrix);


int main(int argc, char** argv) {
  if (argc != 2) {
    printf("Arguments invalid\n");
    return EXIT_FAILURE;
  }

  FILE* doc = fopen(argv[1], "r");
  if(!doc) {
    printf("Failure on file openning\n");
    return EXIT_FAILURE;
  }

  matrix_elem* new_matrix = loadMatrix(doc);
  if(!new_matrix) {
    printf("Failure on loading matrix\n");
    fclose(doc);
    return EXIT_FAILURE;
  }
  
  fclose(doc);

  if(!testMatrixH(new_matrix)){
    printf("Test Failed!\n");
    freeMatrix(new_matrix);
    return EXIT_FAILURE;
  }

  printf("L-norma: %lf\n", calculateLNorm(new_matrix));

  freeMatrix(new_matrix);

  return EXIT_SUCCESS;
}


double calculateLNorm(const matrix_elem* matrix) {
  int rows = getRows(matrix);
  int cols = getCols(matrix);

  double *sums = (double *)calloc(sizeof(double), cols);

  for (int j = 0; j < cols; j++)
    for (int i = 0; i < rows; i++)
      sums[j] = sums[j] + getElem(matrix, i, j);

  double max;
  for (int i = 0; i < cols; i++) {
    if (i == 0) { max = sums[i]; continue; }
    if (max < sums[i]) max = sums[i];
  }

  free(sums);

  return max;
}


int testMatrixH(matrix_elem* matrix) {
  int i_max = getRows(matrix);
  int j_max = getCols(matrix);

  double a = 5.0;

  if(i_max > 4 && j_max > 4) {
    if(!setElem(matrix, 3, 3, a)) return 0;
    if(getElem(matrix, 3, 3) != a) return 0;

    if(!setElem(matrix, 3, 3, 0)) return 0;
    if(getElem(matrix, 3, 3) != 0) return 0;
  }

  //printf("%d\n", setElem(matrix, 1, 1, 'a'));
  //printf("%f\n", getElem(matrix, 1, 1));

  if(i_max < 7 && j_max < 7) {
    if(setElem(matrix, 8, 8, a)) return 0;
    if(getElem(matrix, 8, 8)) return 0;
  }

  return 1; //OK
}
