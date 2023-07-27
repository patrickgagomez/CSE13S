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
  int saveIndex;


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
      addEdge(G, firstNum[i], secondNum[i]);
    } else if (firstNum[i] == 0 && secondNum[i] == 0) {
      saveIndex = i + 1;
      i = arrSize;
    }
  }

	//print out all of the adj lists
  printGraph(outfile, G);
	fprintf(outfile, "\n");

	//create a list to hold the paths generated
  List path = newList();


	//using the same principle as the for loop above, we iterate over the
	//elements from infile until we hit the next dummy line, which is the end
	//of the infile.
  for (int i = saveIndex; i < arrSize; i++) {
    if (firstNum[i] != 0 && secondNum[i] != 0) {
      //inside the loops, we call BFS and get the path specified...
			BFS(G, firstNum[i]);
      getPath(path, G, secondNum[i]);

			//then we print out all the information of that path, such as distance
			//and the path itself.
			moveFront(path);
			if (get(path) != -1){
				fprintf(outfile, "The distance from %d to %d is %d\n", firstNum[i], secondNum[i], getDist(G, firstNum[i]));
				fprintf(outfile, "A shortest %d-%d path is: ", firstNum[i], secondNum[i]);
      	printList(outfile, path);
				fprintf(outfile, "\n");
			} else {
				//if the List path has a NIL (-1) and that's it, then we know that there is no path and that
				//the distance is infinity, so we print that here if that is the case.
				fprintf(outfile, "The distance from %d to %d is infinity\n", firstNum[i], secondNum[i]);
				fprintf(outfile, "No %d-%d path exists\n", firstNum[i], secondNum[i]);
			}
			//clear the path for the next getPath() call.
      clear(path);
		//once we hit the dummy line (0 0), we terminate the loop
    } else if (firstNum[i] == 0 && secondNum[i] == 0) {
      i = arrSize;
    }
  }

  return 0;
}
