/*********************************************************************************
* Patrick Gomez, pggomez
* 2022 Spring CSE101 PA#3
* Graph.c
* The '.c' file for all of the Graph functions.
*********************************************************************************/
#include "Graph.h"
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int time;

int Visit(Graph G, int u, int time, List L);

//---------------------- structs
typedef struct GraphObj {
  int order;
  int size;
  int source;
  int *color;
  int *parent;
  int *distance;

//newstuff
	int *finish;
	int *discover;
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
// new stuff
	G->finish = calloc(n + 1, sizeof(int));
	G->discover = calloc(n + 1, sizeof(int));

  // fill them with values
  for (int i = 1; i < n + 1; i++) {
    G->listArray[i] = newList();
    G->color[i] = WHITE;
    G->parent[i] = NIL;
    G->distance[i] = INF;
		
		//new stuff
		G->finish[i] = UNDEF;
		G->discover[i] = UNDEF; 
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

	moveFront(G->listArray[u]);
  for(int i = 0; i < length(G->listArray[u]); i++){
    if( get(G->listArray[u]) == v ){
			return;
    }
		moveNext(G->listArray[u]);
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
	return;
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
		if (length(G->listArray[i]) > 0){
    	printList(out, G->listArray[i]);
		} else if (length(G->listArray[i]) == 0){
			fprintf(out, "\n");
		}
  }
  return;
}



///////////////////////////////////////////////////////////////////pa2 functions ^^^
///////////////////////////////////////////////////////////////////pa3 functions vvv


int getDiscover(Graph G, int u) { /* Pre: 1<=u<=n=getOrder(G) */
	//check preconditions...
	if (u < 1 || u > getOrder(G)) {
    fprintf(stderr, "getDiscover error: u is not within bounds\n");
    exit(EXIT_FAILURE);
  }

	//then just return discover time at 'u' index
	return G->discover[u];
}

int getFinish(Graph G, int u){  /* Pre: 1<=u<=n=getOrder(G) */
	//check preconditions...
	if (u < 1 || u > getOrder(G)) {
    fprintf(stderr, "getDiscover error: u is not within bounds\n");
    exit(EXIT_FAILURE);
  }
	
	//then just return finish time at 'u' index
	return G->finish[u];
}

Graph transpose(Graph G){
	//create a new graph and grab the end value...
	Graph newG = newGraph(getOrder(G));
	int end = 0;
	

	//then from 1 to n (getorder(g)), reverse each arc by adding it's inverse
	for (int i = 1; i <= getOrder(G); i++) {
		moveFront(G->listArray[i]);
    for (int j = 0; j < length(G->listArray[i]); j++){
			end = get(G->listArray[i]);
			addArc(newG, end, i);
			moveNext(G->listArray[i]);
		}
  }
	
	//return the new graph
	return newG;
}

Graph copyGraph(Graph G){
	//create a new graph and grab the end value...
  Graph newG = newGraph(getOrder(G));
  int end = 0;


  //then from 1 to n (getorder(g)), add all the same arcs to the new graph
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->listArray[i]);
    for (int j = 0; j < length(G->listArray[i]); j++){
      end = get(G->listArray[i]);
      addArc(newG, i, end);
      moveNext(G->listArray[i]);
    }
  }

  //return the new graph
  return newG;
}



void DFS(Graph G, List S){ /* Pre: length(S)==getOrder(G) */
	//set everything to default values...
	for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = WHITE;
    G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
  }
	
	//set initial time to zero
  time = 0;
	//for all indexes in stack S...
  for (moveFront(S); index(S) >= 0; moveNext(S)) {
		//if their color is WHITE, recursively call Visit().
		if (G->color[get(S)] == WHITE){
      time = Visit(G, get(S), time, S);
    }
  }
	
	//clear the original stack to make a new one after
	//the recursive calls to Visit()
	clear(S);	

	//add in all the values to the stack in their proper order...
  for (int i = 1; i <= G->order; i++){
		if (length(S) == 0){
			append(S, i);
			continue;
		} else {
			moveFront(S);
  		while (index(S) >= 0 && G->finish[get(S)] >= G->finish[i]) {
    		moveNext(S);
  		}
		}
		if (index(S) < 0){
			append(S, i);
			continue;
		} else {
			insertBefore(S, i);
			continue;
		}
	}
}

int Visit(Graph G, int u, int time, List L){
	//set the discover time and the color value to GREY (discovered)
	G->discover[u] = (++time);
	G->color[u] = GREY;	
	
	//move to the front of the adj list at 'u'...
	moveFront(G->listArray[u]);
	int getNum = 0;

	//for all the indexes in the adj list...
	for (int y = 0; y < length(G->listArray[u]); y++){
		//grab the number and if it is WHITE, set it's parent and time to a
		//recursive call to visit...
		getNum = get(G->listArray[u]);
		if (G->color[getNum] == WHITE){
			G->parent[getNum] = u;
			time = Visit(G, getNum, time, L);
		}
		moveNext(G->listArray[u]);
	}
	
	//as the recursive calls pop backwards, it will color the	
	//indexes black and fill in their finishing times!
	G->color[u] = BLACK;
	G->finish[u] = ++time;

	//return time
	return time;
}
