// Interface to the undirected graph ADT
// Vertices are identified by integers between 0 and N - 1, where N is
// the number of vertices in the graph
// Self-loops are not allowed

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct graph *Graph;

typedef int Vertex;

struct graph {
    int nV;       // #vertices
    int nE;       // #edges
    bool **edges; // adjacency matrix
};

/**
 * Creates a new graph
 */
Graph GraphNew(int nV);

/**
 * Frees all memory allocated to the given graph
 */
void GraphFree(Graph g);

/**
 * Returns the number of vertices in the graph
 */
int GraphNumVertices(Graph g);

/**
 * Inserts an edge between `v` to `w`. Does nothing if the edge already
 * exists.
 * Assumes `v` and `w` are valid vertices and `v` =/= `w`.
 */
void GraphInsertEdge(Graph g, Vertex v, Vertex w);

/**
 *  Checks if there is an edge between `u` and `v`, returning `true` if
 *  there is or false otherwise.
 *  Assumes `u` and `v` are valid vertices.
 */
bool GraphIsAdjacent(Graph g, Vertex u, Vertex v);

/**
 * Prints the graph to stdout
 */
void GraphShow(Graph g);

#endif
