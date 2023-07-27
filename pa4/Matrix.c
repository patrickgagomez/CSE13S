/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#4
 * Matrix.c
 *  The '.c' file for all of the Matrix functions.
 *********************************************************************************/

#include "Matrix.h"
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// --------------------------------- structs vvv

typedef struct EntryObj *Entry;

typedef struct EntryObj {
  int column;
  double value;
} EntryObj;

// === entry ^ ====
// === matrix v ===

typedef struct MatrixObj {
  int size;
  int nnz;
  List *entryArray;

} MatrixObj;

// --------------------------------- constructors/destructors vvv

// constructors for entry
Entry newEntry(int col, double val) {
  Entry E = malloc(sizeof(EntryObj));

  assert(E != NULL);
  E->column = col;
  E->value = val;

  return E;
}

void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// === entry ^ ====
// === matrix v ===

// constructors for matrix
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));

  M->entryArray = calloc(n + 1, sizeof(Entry));
  for (int i = 1; i < n + 1; i++) {
    M->entryArray[i] = newList();
  }

  M->size = n;
  M->nnz = 0;
  return M;
}

void freeMatrix(Matrix *pM) {
  int n = size(*pM);

  for (int i = 0; i < n + 1; i++) {
    freeList(&((*pM)->entryArray[i]));
  }
  free((*pM)->entryArray);

  free(*pM);
  (*pM) = NULL;
}

// ---------------------------------

// returns the size of the matrix
int size(Matrix M) { return M->size; }

// returns the number of non-zero elements in a matrix
int NNZ(Matrix M) { return M->nnz; }

// returns whether or not a matrix A is equal to matrixB
int equals(Matrix A, Matrix B) {

  // check if the sizes are the same
  if (size(A) != size(B)) {
    return false;
  }

  // go through each row and check their lengths. if they arent equal,
  // the matrix arent equal
  for (int i = 1; i <= size(A); i++) {
    if (length(A->entryArray[i]) != length(B->entryArray[i])) {
      return false;
    }
  }

  // create temp matrix A and B to not alter them
  Matrix tempA = copy(A);
  Matrix tempB = copy(B);

  // create to buffer entries
  Entry grabA = NULL;
  Entry grabB = NULL;

  // go through each matrix's entryArray and check for equality
  for (int i = 1; i <= size(tempA); i++) {
    moveFront(tempA->entryArray[i]);
    moveFront(tempB->entryArray[i]);
    for (int j = 1; j <= length(tempA->entryArray[i]); j++) {
      if (length(tempA->entryArray[i]) != 0 &&
          index(tempA->entryArray[i]) >= 0) {
        grabA = get(tempA->entryArray[i]);
        grabB = get(tempB->entryArray[i]);
        // if a non-match is found, not equal
        if (grabA->value != grabB->value) {
          return false;
        }
        moveNext(tempA->entryArray[i]);
        moveNext(tempB->entryArray[i]);
      }
    }
  }
  // free temp matrix
  freeMatrix(&tempA);
  freeMatrix(&tempB);

  return true;
}

// ---------------------------------

// clears a matrix
void makeZero(Matrix M) {

  // move through each row in the matrix and clear their entries out
  for (int i = 1; i <= size(M); i++) {
    moveFront(M->entryArray[i]);
    if (length(M->entryArray[i]) > 0) {
      for (int j = 1; j <= length(M->entryArray[i]); j++) {
        if (length(M->entryArray[i]) != 0 && index(M->entryArray[i]) >= 0) {
          changeEntry(M, i, j, 0);
        }
      }
    }
  }

  // the last loop leaves the first values in the Matrix, this deletes the last
  // element that wasnt cleared in the previous loop
  for (int i = 1; i <= size(M); i++) {
    if (length(M->entryArray[i])) {
      deleteFront(M->entryArray[i]);
    }
  }

  // sets the nnz of the matrix back to 0
  M->nnz = 0;
  return;
}

void changeEntry(Matrix M, int i, int j, double x) {
  // create an entry to hold the new data and one to grab the entries in the
  // matrix list[i]
  Entry nE = newEntry(j, x);
  Entry grab = NULL;

  // add entry if theres nothing yet
  if (length(M->entryArray[i]) == 0) {
    if (x != 0) {
      M->nnz++;
      append(M->entryArray[i], nE);
      return;
    } else {
      return;
    }
  }

  moveFront(M->entryArray[i]);
  // while the index is not undefined...
  while (index(M->entryArray[i]) >= 0) {

    // grab the entry at row i and...
    grab = get(M->entryArray[i]);

    // check if the column data from the Entry you grabbed is equal to j
    // if it is, check the value of x to see what needs to be done
    if ((grab)->column == j && x != 0) {
      grab->value = x;
      return;

    } else if ((grab)->column > j && x != 0) {
      insertBefore(M->entryArray[i], nE);
      M->nnz++;
      return;

    } else if ((grab)->column == j && x == 0) {
      delete (M->entryArray[i]);
      M->nnz--;
      return;
    }

    moveNext(M->entryArray[i]);
  }

  // if you get to the end and x is not zero, it needs to be appended
  if (x != 0) {
    M->nnz++;
    append(M->entryArray[i], nE);
    return;
  }
  // otherwise M[i, j] == 0 and x == 0 so you dont need to do anything
  return;
}

Matrix copy(Matrix A) {
  // create a new matrix with the same size and a buffer entry
  Matrix B = newMatrix(size(A));
  Entry grab = NULL;

  // go through and changeEntry() in B for every index in A
  for (int i = 1; i <= size(A); i++) {
    moveFront(A->entryArray[i]);
    for (int j = 1; j <= length(A->entryArray[i]); j++) {
      if (length(A->entryArray[i]) != 0 && index(A->entryArray[i]) >= 0) {
        grab = get(A->entryArray[i]);
        changeEntry(B, i, j, grab->value);
        moveNext(A->entryArray[i]);
      }
    }
  }

  // return the created graph
  return B;
}

// returns the transpose of a passed matrix
Matrix transpose(Matrix A) {

  // create a new matrix and entry buffer
  Matrix B = newMatrix(size(A));
  Entry grab = NULL;

  // go through A and assigned a new opposite element into B
  for (int i = 1; i <= size(A); i++) {
    moveFront(A->entryArray[i]);
    for (int j = 1; j <= length(A->entryArray[i]); j++) {
      if (length(A->entryArray[i]) != 0 && index(A->entryArray[i]) >= 0) {
        grab = get(A->entryArray[i]);
        changeEntry(B, grab->column, i, grab->value);
        moveNext(A->entryArray[i]);
      }
    }
  }

  // return the new graph
  return B;
}

// ---------------------------------

// a simple function to print out the data of each entry in each row
// of a passed in matrix
void printMatrix(FILE *out, Matrix M) {
  Entry grab = NULL;
  for (int i = 1; i <= size(M); i++) {
    if (length(M->entryArray[i]) != 0) {
      moveFront(M->entryArray[i]);
      fprintf(out, "%d: ", i);
      while (index(M->entryArray[i]) >= 0) {
        grab = get(M->entryArray[i]);
        fprintf(out, "(%d, %.1f) ", grab->column, grab->value);
        moveNext(M->entryArray[i]);
      }
      fprintf(out, "\n");
    }
  }
  fprintf(out, "\n");
  return;
}

// ---------------------------------

// multiply one matrix by a stated number
Matrix scalarMult(double x, Matrix A) {
  // create a new matrix and entry buffer
  Matrix B = newMatrix(size(A));
  Entry grab = NULL;

  // go through and change each entry to the same data multiplied
  // by the supplied number
  for (int i = 1; i <= size(A); i++) {
    moveFront(A->entryArray[i]);
    for (int j = 1; j <= length(A->entryArray[i]); j++) {
      if (length(A->entryArray[i]) != 0 && index(A->entryArray[i]) >= 0) {
        grab = get(A->entryArray[i]);
        changeEntry(B, i, j, (grab->value * x));
        moveNext(A->entryArray[i]);
      }
    }
  }
  // return the new matrix
  return B;
}

Matrix sum(Matrix A, Matrix B) {
  // check that the sizes are the same
  if (size(A) != size(B)) {
    fprintf(stderr, "Matrix Error: calling sum on different sized lists.\n");
    exit(EXIT_FAILURE);
  }

  // create a new matrix and check if the ones passed in
  // are equal to eachother...
  Matrix nM = newMatrix(size(A));

  if (equals(A, B) == true) {
    // if they are equal, we just have to multiply
    // one matrix by 2.
    nM = scalarMult(2, A);
    return nM;
  }

  // otherwise create buffers
  Entry grabA = NULL;
  Entry grabB = NULL;
  // and a static empty entry
  Entry empty = newEntry(0, 0);

  // move to the front of all rows
  for (int i = 1; i <= size(A); i++) {
    moveFront(A->entryArray[i]);
    moveFront(B->entryArray[i]);

    // grab the A value and move next if applicable
    for (int j = 1; j <= length(A->entryArray[i]); j++) {
      if (index(A->entryArray[i]) >= 0) {
        grabA = get(A->entryArray[i]);
        moveNext(A->entryArray[i]);
      }

      // grab the B value and move next if applicable
      if (index(B->entryArray[i]) >= 0) {
        grabB = get(B->entryArray[i]);
        moveNext(B->entryArray[i]);
      } else if (index(B->entryArray[i]) < 0) {
        grabB = empty;
      }
      // if a is less than b
      if (grabA->column < grabB->column) {
        // change the entry in the new matrix
        changeEntry(nM, i, grabA->column, grabA->value);

        // we possibly need to fix the row in B
        if (index(B->entryArray[i]) < 0) {
          moveBack(B->entryArray[i]);
          continue;
        } else if (index(B->entryArray[i]) >= 0) {
          movePrev(B->entryArray[i]);
          continue;
        }
      }

      // otherwise change entry
      changeEntry(nM, i, grabA->column, (grabA->value + grabB->value));
    }
  }

  // fix the nnz in the new matrix
  nM->nnz = B->nnz;
  return nM;
  // return new matrix
}

//@@@@@		this function works basically the same as sum, except we
//subtract instead of add!!     @@@@@@
Matrix diff(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    fprintf(stderr, "Matrix Error: calling diff on different sized lists.\n");
    exit(EXIT_FAILURE);
  }

  Matrix nM = newMatrix(size(A));

  if (equals(A, B) == true) {
    return nM;
  }

  Entry grabA = NULL;
  Entry grabB = NULL;
  Entry empty = newEntry(0, 0);

  for (int i = 1; i <= size(A); i++) {
    moveFront(A->entryArray[i]);
    moveFront(B->entryArray[i]);

    for (int j = 1; j <= length(A->entryArray[i]); j++) {
      if (index(A->entryArray[i]) >= 0) {
        grabA = get(A->entryArray[i]);
        moveNext(A->entryArray[i]);
      }

      if (index(B->entryArray[i]) >= 0) {
        grabB = get(B->entryArray[i]);
        moveNext(B->entryArray[i]);
      } else if (index(B->entryArray[i]) < 0) {
        grabB = empty;
      }
      // if a is less than b
      if (grabA->column < grabB->column) {
        changeEntry(nM, i, grabA->column, grabA->value);

        if (index(B->entryArray[i]) < 0) {
          moveBack(B->entryArray[i]);
          continue;
        } else if (index(B->entryArray[i]) >= 0) {
          movePrev(B->entryArray[i]);
          continue;
        }
      }

      changeEntry(nM, i, grabA->column, (grabA->value - grabB->value));
    }
  }

  nM->nnz = B->nnz;
  return nM;
}

// to get the product, we transpose B and then
// call the helper function sumLists in order to get the
// true product of a matrix
Matrix product(Matrix A, Matrix B) {
  if (size(A) != size(B)) {
    return NULL;
  }

  Entry checkLength = NULL;
  Matrix nB = transpose(B);
  Matrix M = newMatrix(size(A));
  int sum = 0;
  int counter = 0;
  int lengthRow = 0;

  List aL = A->entryArray[1];
  List bL = NULL;

  moveBack(aL);
  checkLength = get(aL);
  lengthRow = (checkLength->column);
  moveFront(aL);

  for (int i = 1; i <= size(A); i++) {
    aL = A->entryArray[i];
    for (int j = 1; j <= lengthRow; j++) {
      bL = nB->entryArray[j];
      if (length(aL) > 0 && length(bL) > 0) {
        sum = sumLists(aL, bL, lengthRow);
        changeEntry(M, i, j, sum);
        counter++;
      }
    }
  }
  M->nnz = counter;
  return M;
}

// sum lists takes two lists (rows) and adds them together
double sumLists(List A, List B, int length) {
  double sum = 0;
  int i = 1;
  Entry getA = NULL;
  Entry getB = NULL;
  Entry holdA = NULL;
  Entry holdB = NULL;

  moveFront(B);
  moveFront(A);
  for (int y = 1; y <= length; y++) {
    if (index(A) >= 0) {
      getA = get(A);
      holdA = getA;
    }

    if (index(B) >= 0) {
      getB = get(B);
      holdB = getB;
    }

    if (index(A) >= 0) {
      moveNext(A);
    } else {
      moveFront(A);
    }

    if (index(B) >= 0) {
      moveNext(B);
    } else {
      moveFront(B);
    }

    Entry empty = newEntry(i, 0);

    if (getA->column != i) {
      getA = empty;
      if (index(A) > 0) {
        movePrev(A);
      } else if (index(A) == 0) {
        moveFront(A);
      } else {
        moveBack(A);
      }
    }
    if (getB->column != i) {
      getB = empty;
      if (index(B) > 0) {
        movePrev(B);
      } else if (index(B) == 0) {
        moveFront(B);
      } else {
        moveBack(B);
      }
    }

    sum += (getA->value * getB->value);
    getA = holdA;
    getB = holdB;
    i++;
  }
  return sum;
}
