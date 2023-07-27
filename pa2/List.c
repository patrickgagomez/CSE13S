#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// structs----------------------
typedef struct NodeObj *Node;

typedef struct NodeObj {
  ListElement data;
  Node next;
  Node prev;
} NodeObj;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;
//-----------------------------

Node newNode(ListElement data) {
  // malloc a new node
  Node N = malloc(sizeof(NodeObj));

  // assert that it is not null and set it's data accordingly
  assert(N != NULL);
  N->data = data;
  N->next = NULL;
  N->prev = NULL;

  // return the created node
  return (N);
}

void freeNode(Node *pN) {
  // making sure the node isnt null before freeing
  if (pN != NULL && *pN != NULL) {
    // free the node and set to null
    free(*pN);
    *pN = NULL;
  }
}

List newList(void) {
  // create a new list and allocate memory for it
  List L;
  L = malloc(sizeof(ListObj));

  // assert that it isnt null and set data accordingly
  assert(L != NULL);
  L->front = L->back = L->cursor = NULL;
  L->index = -1;
  L->length = 0;
  return (L);
}

void freeList(List *pL) {
  // same principle as free node, check base statement and then call clear()
  // which does all the free'ing necessary for the List.
  if (pL != NULL && *pL != NULL) {
    if (length(*pL) > 0) {
      clear(*pL);
    }
    free(*pL);
    (*pL) = NULL;
  }
}

// simple return length
int length(List L) { return L->length; }

// simple return index
int index(List L) { return L->index; }

int front(List L) {
  // check that L isnt null and has a length above zero...
  if (L == NULL) {
    printf("List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling front() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  // then return the data at the front of the list
  return (L->front->data);
}

int back(List L) {
  // check that L isnt null and has a length above zero...
  if (L == NULL) {
    printf("List Error: calling back() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling back() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  // then return the data at the back of the list
  return (L->back->data);
}

// simple return of cursor data
int get(List L) { return (L->cursor->data); }

bool equals(List A, List B) {
  // check the the lists arent null...
  if (A == NULL || B == NULL) {
    printf("List Error: calling equals() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  // create two new nodes
  bool eq;
  Node N, M;

  // check that their length is the same
  eq = (A->length == B->length);
  // set the temp nodes to the front of the lists
  N = A->front;
  M = B->front;
  // loop through the lists to check status of sameness
  while (eq && N != NULL) {
    eq = (N->data == M->data);
    N = N->next;
    M = M->next;
  }
  // return the final boolean value
  return eq;
}

void clear(List L) {
  // create a counter and a temp length (to not destroy)
  int counter = 0;
  int lengthTemp = length(L);
  // while loop to delete the back of the list until reaching the front
  while (counter != lengthTemp) {
    deleteBack(L);
    counter++;
  }
  return;
}

void set(List L, int x) {
  // check the base case...
  if (length(L) != 0 && L->index >= 0) {
    // create a new node and set the cursor to that new node
    Node new = newNode(x);
    L->cursor = new;
  }
  return;
}

void moveFront(List L) {
  // if null there is no front...
  if (L == NULL) {
    printf("List Error: called moveFront on a null list\n");
    exit(EXIT_FAILURE);
  }

  // if the length is over 1...
  if (length(L) >= 1) {
    // set the cursor to the front and index to zero, then return
    L->cursor = L->front;
    L->index = 0;
  }
  return;
}

void moveBack(List L) {
  // same principle as moveFront, except move the cursor to the back
  if (L == NULL) {
    printf("List Error: called moveBack on a null list\n");
    exit(EXIT_FAILURE);
  }

  if (length(L) >= 1) {
    L->cursor = L->back;
    L->index = (length(L) - 1);
  }
  return;
}

void movePrev(List L) {
  // check the base case...
  if (L->index == 0) {
    L->cursor = NULL;
    L->index = -1;
    // otherwise move the cursor to it's previous node and
    // set index accordingly (-1)
  } else if (L->index > 0) {
    L->cursor = L->cursor->prev;
    L->index--;
  }
  return;
}

void moveNext(List L) {
  // same principle as movePrev, but with the NEXT node
  if (L->index == (length(L) - 1)) {
    L->cursor = NULL;
    L->index = -1;
  } else if (L->index < length(L)) {
    L->cursor = L->cursor->next;
    L->index++;
  }
  return;
}

void prepend(List L, int x) {
  // create the new node and check base cases...
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if (index(L) >= 0) {
    L->index++;
  }

  // if there is no elements yet, set this new node
  // as the first (only) element
  if (length(L) == 0) {
    L->front = L->back = N;
  } else {
    // otherwise set the links in the doubly linked list
    // accordingly and increment the length of the list
    N->next = L->front;
    N->prev = NULL;
    L->front->prev = N;
    L->front = N;
  }
  L->length++;

  return;
}

void append(List L, int x) {
  // append has the same principle as prepend, but with
  // swapped direction, adding at the back instead
  Node N = newNode(x);

  if (L == NULL) {
    printf("List Error: calling append() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }

  if (length(L) == 0) {
    L->back = L->front = N;
  } else {
    N->prev = L->back;
    N->next = NULL;
    L->back->next = N;
    L->back = N;
  }
  L->length++;

  return;
}

void insertBefore(List L, int x) {
  // check base cases...
  if (length(L) < 0) {
    printf("List Error: calling insertBefore() on an null list\n");
    exit(EXIT_FAILURE);
  }

  if (index(L) < 0) {
    printf("List Error: calling insertBefore() when List index is undefined\n");
    exit(EXIT_FAILURE);
  }

  // create the new node
  Node N = newNode(x);
  Node A = L->cursor->prev;
  Node B = L->cursor;

  N->prev = A;
  N->next = B;
  B->prev = N;
  if (A != NULL) {
    A->next = N;
  } else {
    L->front = N;
  }

  L->length++;
  L->index++;
  int move = index(L);
  moveFront(L);
  for (int i = 0; i < move; i++) {
    moveNext(L);
  }

  return;
}

void insertAfter(List L, int x) {
  // same principle as insertBefore, except
  // doing it in the reverse order
  if (length(L) < 0) {
    printf("List Error: calling insertAfter() on an list with length < 0\n");
    exit(EXIT_FAILURE);
  }

  if (L->index < 0) {
    printf("List Error: calling insertAfter() when the List index is less than "
           "0\n");
    exit(EXIT_FAILURE);
  }

  Node N = newNode(x);
  Node A = L->cursor;
  Node B = L->cursor->next;

  A->next = N;
  N->prev = A;
  N->next = B;
  if (B != NULL) {
    B->prev = N;
  } else {
    L->back = N;
  }

  L->length++;
  int move = index(L);
  moveFront(L);
  for (int i = 0; i < move; i++) {
    moveNext(L);
  }

  return;
}

void deleteFront(List L) {
  // create a new null node and check base cases...
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteFront() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  // set the new node to the front
  N = L->front;

  // move the nodes up
  if (length(L) > 1) {
    L->front = L->front->next;
    // if the list has one node just delete it (NULL)
  } else {
    L->front = L->back = NULL;
  }
  // decrement the length
  L->length--;
  L->index--;
  // free the node
  freeNode(&N);

  return;
}

void deleteBack(List L) {
  // same principle as deleteFront, but in the back :P
  Node N = NULL;

  if (L == NULL) {
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if (length(L) == 0) {
    printf("List Error: calling deleteBack() on an empty List\n");
    exit(EXIT_FAILURE);
  }
  N = L->back;
  if (length(L) > 1) {
    L->back = L->back->prev;
    L->back->next = NULL;
  } else {
    L->back = L->front = NULL;
  }
  if (index(L) == length(L) - 1) {
    L->index = -1;
  }
  L->length--;
  freeNode(&N);
  return;
}

void delete (List L) {
  // check base cases...

  if (length(L) < 0) {
    printf("List Error: calling delete() on an empty List\n");
    exit(EXIT_FAILURE);
  }

  if (L->index < 0) {
    printf("List Error: calling delete() when index is negative\n");
    exit(EXIT_FAILURE);
  }

  // create a new node at the cursor
  Node N = L->cursor;
  // if the length is > 1, set the cursor's new links
  // accordingly
  if (length(L) > 1 && index(L) == 0) {
    deleteFront(L);
    return;

  } else if (length(L) > 1 && index(L) == length(L) - 1) {
    deleteBack(L);
    return;

  } else if (length(L) > 1 && index(L) != 0) {
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;

  } else if (length(L) == 0) {
    // otherwise just null the node
    L->back = L->front = NULL;
  }

  // decrement the length
  if (index(L) == length(L) - 1) {
    L->index = -1;
  } else if (index(L) == 0) {
    L->index = -1;
  }
  L->length--;
  // free the node
  freeNode(&N);
  L->cursor = NULL;

  return;
}

void printList(FILE *out, List L) {

  // check that there are actually
  // elements in the list...
  if (length(L) == 0) {
    printf("Printing Error: Empty List!\n");
    exit(EXIT_FAILURE);
  }

  // dont print if the adj[] is cleared (has NIL)
  if (length(L) == 1) {
    if (L->front->data == -1) {
      return;
    }
  }

  // save the cursors spot and create a counter
  int cursorSpot = index(L);
  int counter = 0;
  // move the cursor to the front
  moveFront(L);
  // loop through the list and print the data
  while (counter != L->length) {

    fprintf(out, "%d ", get(L));
    moveNext(L);
    counter++;
  }

  // move back to the front
  moveFront(L);

  // moveNext() the counter until its back in the
  // original spot specified above
  for (int i = 0; i < cursorSpot; i++) {
    moveNext(L);
  }
  // newline for clarity
  fprintf(out, "\n");

  return;
}

List copyList(List L) {

  // create a new list and save the cursor
  // location for later
  List new = newList();
  int cursorSpot = index(L);
  int counter = 0;

  // move through the old list and append the data
  // to the new list
  moveFront(L);
  while (counter != length(L)) {
    append(new, get(L));
    counter++;
    moveNext(L);
  }

  // reset the cursor in the old list to its
  // original location
  moveFront(L);
  for (int i = 0; i < cursorSpot; i++) {
    moveNext(L);
  }
  // set the new list's cursor to null
  new->cursor = NULL;

  // return the new list!
  return new;
}
