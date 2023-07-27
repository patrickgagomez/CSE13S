//-----------------------------------------------------------------------------
//  MatrixClient.c
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
  int n = 10;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  Matrix C, D, E, F, G, H;

  changeEntry(A, 1, 1, 1);
  changeEntry(B, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(B, 1, 2, 0);
  changeEntry(A, 1, 3, 3);
  changeEntry(B, 1, 3, 1);
  changeEntry(A, 2, 1, 4);
  changeEntry(B, 2, 1, 0);
  changeEntry(A, 2, 2, 5);
  changeEntry(B, 2, 2, 1);
  changeEntry(A, 2, 3, 6);
  changeEntry(B, 2, 3, 0);
  changeEntry(A, 3, 1, 7);
  changeEntry(B, 3, 1, 1);
  changeEntry(A, 3, 2, 8);
  changeEntry(B, 3, 2, 1);
  changeEntry(A, 3, 3, 9);
  changeEntry(B, 3, 3, 1);

  printf("%d\n", NNZ(A));
  printMatrix(stdout, A);
  printf("\n");

  printf("%d\n", NNZ(B));
  printMatrix(stdout, B);
  printf("\n");

  C = scalarMult(1.5, A);
  printf("%d\n", NNZ(C));
  printMatrix(stdout, C);
  printf("\n");

  D = sum(A, B);
  printf("%d\n", NNZ(D));
  printMatrix(stdout, D);
  printf("\n");

  E = diff(A, A);
  printf("%d\n", NNZ(E));
  printMatrix(stdout, E);
  printf("\n");

  F = transpose(B);
  printf("%d\n", NNZ(F));
  printMatrix(stdout, F);
  printf("\n");

  G = product(B, B);
  printf("%d\n", NNZ(G));
  printMatrix(stdout, G);
  printf("\n");

  H = copy(A);
  printf("%d\n", NNZ(H));
  printMatrix(stdout, H);
  printf("\n");

  printf("%s\n", equals(A, H) ? "true" : "false");
  printf("%s\n", equals(A, B) ? "true" : "false");
  printf("%s\n", equals(A, A) ? "true" : "false");

  makeZero(A);
  printf("%d\n", NNZ(A));
  printMatrix(stdout, A);

  /*
freeMatrix(&A);
freeMatrix(&B);
freeMatrix(&C);
freeMatrix(&D);
freeMatrix(&E);
freeMatrix(&F);
freeMatrix(&G);
freeMatrix(&H);
  */

  return EXIT_SUCCESS;
}

/*
#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 10;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);

  changeEntry(A, 1, 1, 1);
  changeEntry(B, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(B, 1, 2, 0);
  changeEntry(A, 1, 3, 3);
  changeEntry(B, 1, 3, 1);
  changeEntry(A, 2, 1, 4);
  changeEntry(B, 2, 1, 0);
  changeEntry(A, 2, 2, 5);
  changeEntry(B, 2, 2, 1);
  changeEntry(A, 2, 3, 6);
  changeEntry(B, 2, 3, 0);
  changeEntry(A, 3, 1, 7);
  changeEntry(B, 3, 1, 1);
  changeEntry(A, 3, 2, 8);
  changeEntry(B, 3, 2, 1);
  changeEntry(A, 3, 3, 9);
  changeEntry(B, 3, 3, 1);

  printf("================================\n");
  printMatrix(stdout, A);
  printMatrix(stdout, B);

  printf("================================\n");
  printf("Testing transpose on A:\n");
  printMatrix(stdout, A);
  Matrix C = transpose(A);
  printMatrix(stdout, C);

  printf("================================\n");
  printf("Testing transpose on B:\n");
  printMatrix(stdout, B);
  Matrix D = transpose(B);
  printMatrix(stdout, D);

  printf("================================\n");
  printf("Testing copyMatrix on A:\n");
  printMatrix(stdout, A);
  Matrix E = copy(A);
  printMatrix(stdout, E);

//printf("================================\n");
//printf("Testing makeZero on A:\n");
//printMatrix(stdout, A);
//makeZero(A);
//printMatrix(stdout, A);

  printf("================================\n");
  printf("Testing equals on A -> E and A -> B:\n");

  printMatrix(stdout, A);
  printMatrix(stdout, E);
  if (equals(A, E) == true) {
    printf("A is equal to E\n");
  }

  printf("//////////\n");

  printMatrix(stdout, B);
  if (equals(A, B) == false) {
    printf("A is not equal to B!\n");
  }

  printf("================================\n");

  printf("Testing scalarMult on A:\n");
  printMatrix(stdout, A);
  Matrix F = scalarMult(1.5, A);
  printMatrix(stdout, F);

        printf("================================\n");
        printf("Testing sum:\n");
        printMatrix(stdout, A);
  printMatrix(stdout, E);
        Matrix G = sum(A, E);
        printMatrix(stdout, G);

        printf("Testing sum with different matrix:\n");
        printMatrix(stdout, A);
  printMatrix(stdout, C);
  Matrix H = sum(A, C);
  printMatrix(stdout, H);

        printf("Testing sum with diff size matrixs:\n");
  printMatrix(stdout, A);
  printMatrix(stdout, B);
  Matrix K = sum(A, B);
  printMatrix(stdout, K);

        printf("================================\n");
  printf("Testing diff:\n");
        printMatrix(stdout, A);
  printMatrix(stdout, E);
        Matrix I = diff(A, E);
        printMatrix(stdout, I);


        printf("Testing diff with different matrix:\n");
  printMatrix(stdout, A);
  printMatrix(stdout, C);
  Matrix J = diff(A, C);
  printMatrix(stdout, J);


  return EXIT_SUCCESS;
}
*/
