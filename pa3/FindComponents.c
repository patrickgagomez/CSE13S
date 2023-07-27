/********************************************************************************* 
* Patrick Gomez, pggomez 
* 2022 Spring CSE101 PA#3 
* FindComponents.c 
* Main function to call DFS and get Strongly Connected Components.
*********************************************************************************/
#include "Graph.h"
#include "List.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	//check if we got infile and outfile...	
	if (argc != 3) {
    fprintf(stderr, "Program Error: No infile/outfile specified.\n");
    exit(EXIT_FAILURE);
  }

	//open infile
  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Could not open file: %s", argv[1]);
    return 0;
  }

	//open outfile
  FILE *outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    printf("Could not open file: %s", argv[2]);
    return 0;
  }

	//read in the first line, which is the number of verticies
  int verts;
  fscanf(infile, "%d\n", &verts);
	//create a new graph with that information
  Graph G = newGraph(verts);

	//create some variables to keep track of things
  int arrSize = -1;
  char c;

	//read through the entire infile and increment the size for the number
	//of lines in the infile
  for (c = getc(infile); c != EOF; c = getc(infile)) {
    if (c == '\n') {
      arrSize++;
    }
  }

	//rewind the infile
  rewind(infile);

  // move past the inital vertices line...
  fscanf(infile, "%d\n", &verts);
	
	//create an array to hold the pairs of numbers...
  int firstNum[arrSize];
  int secondNum[arrSize];


	//read in all the numbers, including the 0 0 dummy lines
  for (int i = 0; i < arrSize; i++) {
    fscanf(infile, "%d %d\n", &firstNum[i], &secondNum[i]);
  }

	//for loop that goes through the array up until the dummy
	//line (0 0) and adds all the edges to the graphs.

	//when it hits the dummy line, it sets the 'i' to the 'arrSize',
	//which then terminates the loop and lets us continue.
  for (int i = 0; i < arrSize; i++) {
    if (firstNum[i] != 0 && secondNum[i] != 0) {
      addArc(G, firstNum[i], secondNum[i]);
    }
  }

	//print out all of the adj lists
	fprintf(outfile, "Adjacency list representation of G:\n");
  printGraph(outfile, G);
	fprintf(outfile, "\n");

	//Create a new list and fill it with the same amount of
	//indexes that G Graph has
	List L = newList();
	for (int i = 1; i <= getOrder(G); i++){
		append(L, i);
	}

	//call DFS on the graph with the new list
	DFS(G, L);
	//this returns a new List
	
	//then get the tranpose of G...
	Graph gT = transpose(G);
	//and call DFS on it to get the Strongly Connected Components!
	DFS(gT, L);
	
	//loop through the indexes in graph and check how many SCCs there are
	int sccCount = 0;
	for (int i = 1; i <= getOrder(G); i++){
    if (getParent(gT, i) == NIL){
			sccCount++;
		}
  }

	//then print out the SCCs as you move through the "Stack" and "pop" them off!
	fprintf(outfile, "G contains %d strongly connected components:", sccCount);
	int numSCC = 0;
	for (int i = 1; i <= getOrder(G); i++){
		moveBack(L);
		while (getParent(gT, get(L)) != NIL){
			movePrev(L);	
		}
		int savedInd = index(L);
		numSCC++;
		fprintf(outfile, "\nComponent %d: %d ", numSCC, get(L));
		moveNext(L);
		while (index(L) >= 0){
			fprintf(outfile, "%d ", get(L));
			moveNext(L);
		}
		moveBack(L);
		while (index(L) != savedInd){
			deleteBack(L);
			moveBack(L);
			i++;
		}
		deleteBack(L);
    moveBack(L);
    //i++;
	}
	//newline for clarity!
	fprintf(outfile, "\n");

	return 0;	
}	
