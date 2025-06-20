// Implementation of the Undirected Weighted Graph ADT
// Uses an adjacency matrix

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Pq.h"

// DO NOT modify this struct
struct graph {
    int nV;         // #vertices
    int nE;         // #edges
    double **edges; // adjacency matrix storing positive weights
                    // 0 if nodes not adjacent
};

static bool validVertex(Graph g, Vertex v);
bool hasCycle(Graph g, int n);
bool dfsHasCycle(Graph g, int v, int parent, bool *visited, int n);

////////////////////////////////////////////////////////////////////////

Graph GraphNew(int nV) {
    assert(nV > 0);

    Graph g = malloc(sizeof(*g));
    if (g == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    g->nV = nV;
    g->nE = 0;

    g->edges = malloc(nV * sizeof(double *));
    if (g->edges == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nV; i++) {
        g->edges[i] = calloc(nV, sizeof(double));
        if (g->edges[i] == NULL) {
            fprintf(stderr, "error: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    return g;
}

void GraphFree(Graph g) {
    for (int i = 0; i < g->nV; i++) {
        free(g->edges[i]);
    }
    free(g->edges);
    free(g);
}

////////////////////////////////////////////////////////////////////////

int GraphNumVertices(Graph g) {
    return g->nV;
}

bool GraphInsertEdge(Graph g, struct edge e) {
    assert(validVertex(g, e.v));
    assert(validVertex(g, e.w));
    assert(e.v != e.w);
    assert(e.weight > 0.0);

    if (g->edges[e.v][e.w] == 0.0) {
        g->edges[e.v][e.w] = e.weight;
        g->edges[e.w][e.v] = e.weight;
        g->nE++;
        return true;
    } else {
        return false;
    }
}

bool GraphRemoveEdge(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));

    if (g->edges[v][w] != 0.0) {   // edge e in graph
        g->edges[v][w] = 0.0;
        g->edges[w][v] = 0.0;
        g->nE--;
        return true;
    } else {
        return false;
    }
}

double GraphIsAdjacent(Graph g, Vertex v, Vertex w) {
    assert(validVertex(g, v));
    assert(validVertex(g, w));
    
    return g->edges[v][w];
}

void GraphShow(Graph g) {
    printf("Number of vertices: %d\n", g->nV);
    printf("Number of edges: %d\n", g->nE);
    for (int v = 0; v < g->nV; v++) {
        for (int w = v + 1; w < g->nV; w++) {
            if (g->edges[v][w] != 0.0) {
                printf("Edge %d - %d: %lf\n", v, w, g->edges[v][w]);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////
// Your task

Graph GraphMst(Graph g) {
    int n = GraphNumVertices(g);
    Graph mst = GraphNew(n);
    Pq pq = PqNew();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double weight = GraphIsAdjacent(g, i, j);
            if (weight != 0.0) {
                struct edge e = {.v = i, .w = j, .weight = weight};
                PqInsert(pq, e);
            }
        }
    }

    int edgeCount = 0;
    while (!PqIsEmpty(pq) && edgeCount < n - 1) {
        struct edge e = PqExtract(pq);
        GraphInsertEdge(mst, e);
        if (hasCycle(mst, n)) {
            GraphRemoveEdge(mst, e.v, e.w);
        } else {
            edgeCount++;
        }
    }

    PqFree(pq);
    if (edgeCount == n - 1) return mst;
    GraphFree(mst);
    return NULL;
}

bool hasCycle(Graph g, int n) {
    bool *visited = calloc(n, sizeof(bool));
    bool result = false;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsHasCycle(g, i, -1, visited, n)) {
                result = true;
                break;
            }
        }
    }
    free(visited);
    return result;
}

bool dfsHasCycle(Graph g, int v, int parent, bool *visited, int n) {
    visited[v] = true;
    for (int w = 0; w < n; w++) {
        if (GraphIsAdjacent(g, v, w) != 0.0) {
            if (!visited[w]) {
                if (dfsHasCycle(g, w, v, visited, n)) return true;
            } else if (w != parent) {
                return true;
            }
        }
    }
    return false;
}


////////////////////////////////////////////////////////////////////////

static bool validVertex(Graph g, Vertex v) {
    return v >= 0 && v < g->nV;
}

