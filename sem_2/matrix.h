#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <string.h>

#define MATRIX_BUFFER_SIZE 10
//минимальное - 2, для инициализации нулевого и завершающего элемента

/*

  Разреженное предстваление матрицы

  функции:
  matrix_elem* loadMatrix(FILE *fp)
  Выполняет загрузку матрицы из файла. По мере загрузки проверяет корректность записанной матрицы.

  matrix_elem* configureMatrix(
    matrix_elem* matrix,
    int* p_size,
    const int i, const int j
  )
  Создает нулевую матрицу заданной длины.

  int getRows(const matrix_elem* matrix)
  Возвращает количество строк.

  int getCols(const matrix_elem* matrix)
  Возвращает количество столбцов.

  double getElem(const matrix_elem* matrix, const int i, const int j)
  Возвращает значение по индексам i и j.

  int freeMatrix(matrix_elem* matrix)
  Освобождает память, выделенную под матрицу.


  внутренние:
  static int getMemorySize(const matrix_elem* matrix)
  Вычисляет, сколько структур на данный момент должны занимать память

  static int setArrayElement(
    matrix_elem* matrix, const double val,
    const int i, const int j,
    const int c
  )
  Устанавливает в поня элмента matrix[c] заданные заданные значения

*/


/*
   для реализации разреженного представления необходимо
   где-то хранить информацию о количестве строк и столбцов
   а также как-то определять конец массива ненулевых элментов
   matrix[0] и matrix[c] - нулевые элементы, в первом хранится col_n и lin_n
   во втором - только нули. Нужен для определения конца.
*/


typedef struct lfloat_matrix_elem {
  double val;
  int i; // line
  int j; // column
} matrix_elem;



static int setArrayElement(
    matrix_elem* matrix, const double val,
    const int i, const int j,
    const int c
) {
  if (!matrix) return 0;

  matrix[c].val = val;
  matrix[c].i = i;
  matrix[c].j = j;

  return 1;
}

static int getMemorySize(const matrix_elem* matrix) {
  if(!matrix) return 0;

  int i;
  for(i = 1; matrix[i].val != 0; i++);
  return i;
}



matrix_elem* configureMatrix(
    matrix_elem* matrix,
    int* p_size,
    const int i, const int j
) {
  if(!matrix) {
    *p_size = MATRIX_BUFFER_SIZE;
    matrix = (matrix_elem*)malloc(sizeof(matrix_elem) * (*p_size));
    if(!matrix) return NULL;

    //инициализация нулевого элемента
    if(!setArrayElement(matrix, 0, i, j, 0)) return NULL;

    return matrix;
  }

  *p_size = *p_size + MATRIX_BUFFER_SIZE;
  
  matrix  = (matrix_elem *)realloc(matrix, sizeof(matrix_elem) * (*p_size));
  if (!matrix) return NULL;

  return matrix;
}

int getRows(const matrix_elem* matrix) {
  if(!matrix) return 0;
  return matrix[0].i;
}

int getCols(const matrix_elem* matrix) {
  if(!matrix) return 0;
  return matrix[0].j;
}

double getElem(const matrix_elem* matrix, const int i, const int j) {
  if ((i >= getRows(matrix)) || (j >= getCols(matrix))) return 0;
  if ((i < 0) || (j < 0)) return 0;

  for (int k = 1; matrix[k].val != 0; k++)
    if ((matrix[k].i == i) && (matrix[k].j == j)) return matrix[k].val;

  return 0;
}

int setElem(matrix_elem* matrix, const int i, const int j, double val) {
  if (!matrix) return 0;
  if ((i >= getRows(matrix)) || (j >= getCols(matrix))) return 0;
  if ((i < 0) || (j < 0)) return 0;

  int k;
  for (k = 1; matrix[k].val != 0; k++) {
    if ((matrix[k].i == i) && (matrix[k].j == j)) {
      if(val == 0) {
        int l = getMemorySize(matrix);
        memmove(matrix + k, matrix + k + 1, sizeof(matrix_elem) * (l - k));

        //matrix[k].i = -1; // таким образом, выкидываем элемент из области поиска ненулевых чисел
        return 1;
      }
      matrix[k].val = val;
      return 1;
    }
  }

  int matrix_size = getMemorySize(matrix);
  // на всякий сучай увеличиваем количество памяти, чтобы новый элмент наверняка уместился
  if(!configureMatrix(matrix, &matrix_size, 0, 0)) return 0;

  setArrayElement(matrix, val, i, j, k);
  setArrayElement(matrix, 0,   0, 0, k+1);
  return 1;
}

// Функция, читающая файл и создающая представление матрицы (массив структур)
matrix_elem* loadMatrix(FILE *fp) {
  int lin_n, col_n;
  if (!fscanf(fp, "%d", &lin_n) || !fscanf(fp, "%d", &col_n)) return NULL;

  int matrix_size;
  matrix_elem* matrix = configureMatrix(NULL, &matrix_size, lin_n, col_n);
  if (!matrix) return NULL;

  double val_buf;
  int c = 1; // counter

  for (int i = 0; i < lin_n; i++) {
    for (int j = 0; j < col_n; j++) {
      if (!fscanf(fp, "%lf", &val_buf)) { free(matrix); return NULL; }

      if(j == col_n - 1) {
        if (i == lin_n - 1) {
	  int c = fgetc(fp);
          if (c != -1) { free(matrix); return NULL; }
        } else {
          if (fgetc(fp) != '\n') { free(matrix); return NULL; }
	}
      }

      if (val_buf == 0) continue; // разреженное представление, поэтому опускаем нули
      if(!setArrayElement(matrix, val_buf, i, j, c)) { free(matrix); return NULL; }

      // сброс буффера, увеличение счетчика
      val_buf = 0; c++;

      if (c == matrix_size) {
	       matrix = configureMatrix(matrix, &matrix_size, lin_n, col_n);
	       if(!matrix){ free(matrix); return NULL; }
      }
    }
  }

  // делаем замыкающий элемент
  if(!setArrayElement(matrix, 0, 0, 0, c)) { free(matrix); return NULL; }

  return matrix;
}

int freeMatrix(matrix_elem* matrix) {
  if(!matrix) return 1;
  free(matrix);
  return 0;
}

#endif //_MATRIX_H_
