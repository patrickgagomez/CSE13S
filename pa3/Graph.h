/*********************************************************************************
* Patrick Gomez, pggomez
* 2022 Spring CSE101 PA#3
* Graph.h
* The '.h' file for all of the Graph functions.
*********************************************************************************/
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include "List.h"
#include <stdbool.h>
#include <stdio.h>

#define UNDEF -1
#define NIL -2
#define INF -8
#define WHITE 0
#define GREY 1
#define BLACK 2

typedef struct GraphObj *Graph;

// constructor (n verts / no edges)
Graph newGraph(int n);

// destructor
void freeGraph(Graph *pG);

// return the corresponding field values
int getOrder(Graph G);
int getSize(Graph G);

// return the source (start) vertex or nil of BFS hasnt been called
int getSource(Graph G);

// precon: 1 <= u <= getOrder(g)
// return the parent vertex of 'u' if bfs has been called, nil otherwise
int getParent(Graph G, int u);

// precon: 1 <= u <= getOrder(g)
// return the distance from source (start) to 'u'
int getDist(Graph G, int u);

// appends to the list of verts the shortest path in G from u, or nil if no path
// precon: source is not nil
// precon: 1 <= u <= getOrder(g)
void getPath(List L, Graph G, int u);

// restore g to original state.
void makeNull(Graph G);

// insert new edge from 'u' to 'v'
void addEdge(Graph G, int u, int v);

// insert directed edge from 'u' to 'v'
void addArc(Graph G, int u, int v);

// run BFS on 'G' with source 's'
void BFS(Graph G, int s);

// print the graph
void printGraph(FILE *out, Graph G);


///////////////////////////////////////////// pa2 functions ^^^
///////////////////////////////////////////// pa3 functions vvv

// return discover variable/field
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

// return discover variable/field
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */

// perform depth first search on graph G
// S variable 1.defines the order in which verts are processed
//            2.stores the verts by decreasing finish times
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

// returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G);

#endif

