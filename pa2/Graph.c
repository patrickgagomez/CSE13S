#include "Graph.h"
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

//---------------------- structs
typedef struct GraphObj {
  int order;
  int size;
  int source;
  int *color;
  int *parent;
  int *distance;
  List *listArray;
} GraphObj;
//----------------------

//------------------------------------------------- constructors/destructors
Graph newGraph(int n) {
  //allocate mem for the graphs
	Graph G = malloc(sizeof(GraphObj));
  G->listArray = calloc(n + 1, sizeof(List));

  // allocate mem for arrays
  G->color = calloc(n + 1, sizeof(int));
  G->parent = calloc(n + 1, sizeof(int));
  G->distance = calloc(n + 1, sizeof(int));

  // fill them with values
  for (int i = 1; i < n + 1; i++) {
    G->listArray[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }

	//set the non-array variables
  G->order = n;
  G->size = 0;
  G->source = NIL;

  return G;
}

void freeGraph(Graph *pG) {
  int n = getSize(*pG);
  //free each list inside the list array
	for (int i = 0; i < n + 1; i++) {
    freeList(&((*pG)->listArray[i]));
  }
	
	//free the list array and all of the other
	//allocated arrays
	free((*pG)->listArray);
  free((*pG)->color);
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);

	//set the graph to null
  (*pG) = NULL;

  return;
}
// -----------------------------------------------------

// easy accessors --------------------------------------

//simply return the variables requested
int getOrder(Graph G) { return G->order; }
int getSize(Graph G) { return G->size; }
int getSource(Graph G) { return G->source; }


//------------------------------------------------------

//------------------------------------------------------ mutators/weirdaccessors
int getParent(Graph G, int u) {
  //if u is within the bounds, just return the parent
	if (u >= 1 && u <= getOrder(G)) {
    return G->parent[u];
  }
	//otherwise just exit w/ failure
  fprintf(stderr, "getParent Error: index is not within bounds\n");
  exit(EXIT_FAILURE);
}

int getDist(Graph G, int u) {
	//if u is within the bounds, just return the distance
  if (u >= 1 && u <= getOrder(G)) {
    return G->distance[u];
  }
	//otherwise just exit w/ failure
  fprintf(stderr, "getParent Error: index is not within bounds\n");
  exit(EXIT_FAILURE);
}

void getPath(List L, Graph G, int u) {
  //check if the source is nil...
	if (G->source != NIL) {
  //if not, check if u is the same as the current source  
	if (u == G->source) {
			//if it is, just append it
      append(L, G->source);
		//otherwise, if parent is nil
    } else if (G->parent[u] == NIL) {
      //clear the list and append nil, the return out
			clear(L);
      append(L, NIL);
      return;
		//our last statement recursively calls getPath until we reach the
		//parent, and then it shoots back, appending all of the path elements
		//into the list
    } else {
      getPath(L, G, G->parent[u]);
      append(L, u);
			G->distance[G->source]++;
    }
    return;
  }
  fprintf(stderr, "getPath Error: BFS has not been called yet\n");
  exit(EXIT_FAILURE);
}

void makeNull(Graph G) { return; }

void addEdge(Graph G, int u, int v) {
  //because an edge is 2 arcs going back and forth
	//on the same two elements, we just call add arc twice
	//and decrement the size so we only are adding 1 edge
	addArc(G, u, v);
  addArc(G, v, u);
  G->size--;
  return;
}

void addArc(Graph G, int u, int v) {

	//check all of the preconditions for u and v...
  if (u <= 0 || u > getOrder(G)) {
    fprintf(stderr, "add arc error: u is out of bounds\n");
    exit(EXIT_FAILURE);
  }

  if (v <= 0 || v > getOrder(G)) {
    fprintf(stderr, "add arc error: v is out of bounds\n");
    exit(EXIT_FAILURE);
  }

  if (u == v) {
    fprintf(stderr,
            "add arc error: u and v are equal to eachother. cannot add arc\n");
    exit(EXIT_FAILURE);
  }

	//move to the front of the listarray at index u
  moveFront(G->listArray[u]);
	//while the index hasn't reached the end...
  while (index(G->listArray[u]) >= 0) {
    //if the data at u is greater than v...
		if (get(G->listArray[u]) >= v) {
			//insert before to keep the adj list in order
      insertBefore(G->listArray[u], v);
      G->size++;
      return;
    }
		//otherwise we keep moving next
    moveNext(G->listArray[u]);
  }
	//until we eventually append and increment the size
  append(G->listArray[u], v);
  G->size++;
}
//------------------------------------------------------

//--------------------------------------------- BFS
void BFS(Graph G, int s) {

  G->source = s;
  // set all the inital values of color, distance and parent
  for (int i = 0; i <= getOrder(G); i++) {
    G->color[i] = WHITE;
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }

  // set the source values
  G->color[s] = GREY;
  G->distance[s] = 0;
  G->parent[s] = NIL;

  // create an empty list
  List L = newList();

  // append to that list and move front
  append(L, s);

  // while the list isnt empty...
  while (length(L) != 0) {
    // get the index in the list cursor and the delete it from the list
    moveFront(L);
    int x = get(L);
    deleteFront(L);

    for (moveFront(G->listArray[x]); index(G->listArray[x]) >= 0;
         moveNext(G->listArray[x])) {
      int y = get(G->listArray[x]);
      if (G->color[y] == WHITE) {
        G->color[y] = GREY;
        G->distance[y] = G->distance[x] + 1;
        G->parent[y] = x;
        append(L, y);
      }
      G->color[x] = BLACK;
    }
  }
  freeList(&L);
}
//----------------------------------------------

//===================================

void printGraph(FILE *out, Graph G) {
  //simple loop to loop through the graph and print
	//each adj list.
	for (int i = 1; i < getOrder(G) + 1; i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->listArray[i]);
  }
  return;
}
