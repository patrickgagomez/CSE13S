#include "List.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

  /*
// create lists
List A = newList();
List B = newList();
List C = NULL;
int i;

// append 300 elements to the list
for (i = 1; i <= 300; i++) {
append(A, i);
prepend(B, i);
}

// print out the lists
printf("List A:\n");
printList(stdout, A);
printf("------------------\n");

printf("List B:\n");
printList(stdout, B);
printf("------------------\n");

// copy list A to list C
printf("Copying List: A -> C\n");
C = copyList(A);

// check that list A indeed matches list C and not list B
printf("A = B?\t%s\n", equals(A, B) ? "true" : "false");
printf("B = C?\t%s\n", equals(B, C) ? "true" : "false");
printf("A = C?\t%s\n", equals(C, A) ? "true" : "false");
printf("------------------\n");

// insert and delete new elements at different spots in the list
moveFront(A);
for (i = 0; i < 45; i++)
moveNext(A); // at index 45
insertBefore(A, -12);
printf("Inserting new element: -12 before index 45\n");
for (i = 0; i < 105; i++)
moveNext(A); // at index 105
insertAfter(A, -98);
printf("Inserting new element: -98 after index 105\n");
for (i = 0; i < 30; i++)
movePrev(A); // at index 30
printf("Deleting element: index 30\n");
delete (A);

// print out the new list with altered elements
printf("New List:\n");
printList(stdout, A);
printf("\n");

// print the length of the list as is, and then
// delete the list and check it's length. should
// be at zero (empty).
printf("List A current length:%d\n", length(A));
printf("Clearing List A...\n");
clear(A);
printf("List A current length:%d\n", length(A));

// free the lists to avoid memory leaks.
freeList(&A);
freeList(&B);
freeList(&C);

*/
  List A = newList();
  prepend(A, 5);
  prepend(A, 65);
  prepend(A, 43);
  moveBack(A);
  printf("index: %d\n", index(A));
  delete (A);
  if (index(A) != -1)
    return 1;
  prepend(A, 2);
  prepend(A, 8);
  prepend(A, 1);
  moveBack(A);
  if (index(A) != 4)
    return 2;
  delete (A);
  moveBack(A);
  if (index(A) != 3)
    return 3;
  moveFront(A);
  delete (A);
  moveFront(A);
  if (index(A) != 0)
    return 4;
  delete (A);
  if (index(A) != -1)
    return 5;
  freeList(&A);

  return (0);
}
