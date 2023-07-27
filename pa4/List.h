/*********************************************************************************
 * Patrick Gomez, pggomez
 * 2022 Spring CSE101 PA#3
 * List.h
 * The '.h' file for all of the List functions.
 *********************************************************************************/
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>
#include <stdio.h>

// defining the structures.
typedef struct ListObj *List;

// constructors/destructors
List newList(void);
void freeList(List *pL);

// accessors
int length(List L);
int index(List L);
void *front(List L);
void *back(List L);
void *get(List L);

// manipulators
void clear(List L);
void set(List L, void *x);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, void *x);
void append(List L, void *x);
void insertBefore(List L, void *x);
void insertAfter(List L, void *x);
void deleteFront(List L);
void deleteBack(List L);
void delete (List L);

// void printList(FILE *out, List L);

#endif
