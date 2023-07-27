/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#4
 * Sparse.c
 * Main function to handle Matrix functionality
 *********************************************************************************/
#include "List.h"
#include "Matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // check if we got infile and outfile...
  if (argc != 3) {
    fprintf(stderr, "Program Error: No infile/outfile specified.\n");
    exit(EXIT_FAILURE);
  }

  // open infile
  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Could not open file: %s", argv[1]);
    return 0;
  }

  // open outfile
  FILE *outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    printf("Could not open file: %s", argv[2]);
    return 0;
  }

  int n, a, b;
  fscanf(infile, "%d %d %d\n", &n, &a, &b);

  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);

  fscanf(infile, "\n");

  int row, col;
  double val;
  for (int i = 0; i < a; i++) {
    fscanf(infile, "%d %d %lf", &row, &col, &val);
    changeEntry(A, row, col, val);
  }

  fscanf(infile, "\n");

  for (int i = 0; i < b; i++) {
    fscanf(infile, "%d %d %lf", &row, &col, &val);
    changeEntry(B, row, col, val);
  }

  fprintf(outfile, "A has %d non-zero entries:\n", NNZ(A));
  printMatrix(outfile, A);

  fprintf(outfile, "B has %d non-zero entries:\n", NNZ(B));
  printMatrix(outfile, B);

  Matrix sA = scalarMult(1.5, A);
  fprintf(outfile, "(1.5)*A = \n");
  printMatrix(outfile, sA);

  Matrix aAB = sum(A, B);
  fprintf(outfile, "A+B =\n");
  printMatrix(outfile, aAB);

  Matrix aAA = sum(A, A);
  fprintf(outfile, "A+A =\n");
  printMatrix(outfile, aAA);

  Matrix dBA = diff(B, A);
  fprintf(outfile, "B-A =\n");
  printMatrix(outfile, dBA);

  Matrix dAA = diff(A, A);
  fprintf(outfile, "A-A =\n");
  printMatrix(outfile, dAA);

  Matrix tA = transpose(A);
  fprintf(outfile, "Transpose(A) =\n");
  printMatrix(outfile, tA);

  Matrix pAB = product(A, B);
  fprintf(outfile, "A*B =\n");
  printMatrix(outfile, pAB);

  Matrix pBB = product(B, B);
  fprintf(outfile, "B*B =\n");
  printMatrix(outfile, pBB);

  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&sA);
  freeMatrix(&aAB);
  freeMatrix(&aAA);
  freeMatrix(&dBA);
  freeMatrix(&dAA);
  freeMatrix(&tA);
  freeMatrix(&pAB);
  freeMatrix(&pBB);

  return 0;
}
