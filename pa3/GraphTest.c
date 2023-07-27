/*********************************************************************************
* Patrick Gomez, pggomez
* 2022 Spring CSE101 PA#3
* GraphTest.c
*	A main function to test if Graph.c/h is working properly
*********************************************************************************/
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(void){
	Graph A = newGraph(100);
  List L = newList();

	addEdge(A, 64, 4);
  addEdge(A, 64, 3);
  addEdge(A, 42, 2);
    addEdge(A, 2, 64);
    addEdge(A, 4, 2);
    addEdge(A, 3, 42);
    for (int i = 1; i <= 100; i++) {
      prepend(L, i);
    }
		printList(stdout, L);
		printf("\n");
    DFS(A, L);
		printList(stdout, L);
		printf("\n");
		printf("\n");
    if (getDiscover(A, 100) != 1)
      return 2;
    if (getDiscover(A, 64) != 73)
      return 3;
    if (getDiscover(A, 4) != 75)
      return 4;
    DFS(A, L);
		printList(stdout, L);
		printf("\n");
		printf("\n");
		printf("discover test 5: %d\n", getDiscover(A, 4));
    if (getDiscover(A, 4) != 121)
      printf("failed test 5\n");
			return 5;
    if (getDiscover(A, 63) != 117)
			printf("failed test 6\n");
      return 6;
    DFS(A, L);
    if (getDiscover(A, 65) != 71)
			printf("failed test 7\n");
      return 7;
    if (getDiscover(A, 1) != 199)
			printf("failed test 8\n");
      return 8;
    return 0;


	freeGraph(&A);
  freeList(&L);

}
