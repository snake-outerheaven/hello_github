#include <stdio.h>

#define X 3
#define Y 4
#define Z 5

int linear_idx(int *indice, int *dims, int n);

int main(void) {
  int matrix[X][Y][Z];
  int val = 0;
  int valor[] = {1, 3, 2};
  int dims[] = {X, Y, Z};
  int ndim = sizeof(dims) / 4;
  int *p = &matrix[0][0][0];
  int idx;

  for (int x = 0; x < X; x++) {
    for (int y = 0; y < Y; y++) {
      for (int z = 0; z < Z; z++) {
        matrix[x][y][z] = val++;
      }
    }
  }
  for (int i = X - 1; i >= 0; i--) {
    int depth_offset = (X - 1 - i) * 3;

    for (int j = 0; j < Y; j++) {
      for (int s = 0; s < depth_offset; s++) {
        printf(" ");
      }

      for (int k = 0; k < Z; k++) {
        printf("%3d ", matrix[i][j][k]);
      }
      printf("\n");
    }
    printf("\n");
  }
  idx = linear_idx(valor, dims, ndim);

  printf("Valor na posição x = %d, y = %d, z = %d -> %d.\n", valor[0], valor[1],
         valor[2], *(p + idx));

  return 0;
}

/*
 * Esta implementação recebe um array dos índices, um array das dimensões e o
 * número das dimensões
 */
int linear_idx(int *indices, int *dims, int n) {
  int idx = 0;
  int stride = 1; // strides seriam saltos dimensionais.

  for (int d = n - 1; d >= 0; d--) {
    idx += indices[d] * stride; // salto dimensional é feito aqui
    stride *= dims[d]; // stride é multiplicado pelo valor numérico da dimensão
  }
  return idx;
}
