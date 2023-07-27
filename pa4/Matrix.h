/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#4
 * Matrix.h
 * The '.h' file for all of the Matrix functions.
 *********************************************************************************/
#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_
#include "List.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct MatrixObj *Matrix;

// constructors/desctructors
Matrix newMatrix(int n);

void freeMatrix(Matrix *pM);

// ACCESSORS
// returns the size of M
int size(Matrix M);

// returns the number of non zero numbers in the matrix
int NNZ(Matrix M);

// returns wheter or not matrix A and B are equal
int equals(Matrix A, Matrix B);

// MANIPULATORS
// reset M to the zero matrix state
void makeZero(Matrix M);

// changes the entry at row i, col j to double x
void changeEntry(Matrix M, int i, int j, double x);

// ARITHMETIC
// copy matrix A to a new matrix which is returned
Matrix copy(Matrix A);

// returns the transpose of matrix A
Matrix transpose(Matrix A);

// returns a reference to Matrix A -> xA
Matrix scalarMult(double x, Matrix A);

// returns a new matrix representing A,B -> A + B
Matrix sum(Matrix A, Matrix B);

// returns a new matrix representing A,B -> A - B
Matrix diff(Matrix A, Matrix B);

// returns a new matrix prepresenting A,B -> A*B
Matrix product(Matrix A, Matrix B);

// returns the sum of two lists. used in product()
double sumLists(List A, List B, int length);

// EXTRA
// prints the matrix
void printMatrix(FILE *out, Matrix M);

#endif
