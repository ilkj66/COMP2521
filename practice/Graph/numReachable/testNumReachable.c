#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int numReachable(Graph g, int src);

int main(void) {
    int nV = 0;
    printf("Enter number of vertices: ");
    if (scanf("%d", &nV) != 1) {
        fprintf(stderr, "error: failed to read number of vertices\n");
        exit(EXIT_FAILURE);
    } else if (nV <= 0) {
        fprintf(stderr, "error: invalid number of vertices\n");
        exit(EXIT_FAILURE);
    }

    int nE = 0;
    printf("Enter number of edges: ");
    if (scanf("%d", &nE) != 1) {
        fprintf(stderr, "error: failed to read number of vertices\n");
        exit(EXIT_FAILURE);
    } else if (nE < 0) {
        fprintf(stderr, "error: invalid number of edges\n");
        exit(EXIT_FAILURE);
    }

    Graph g = GraphNew(nV);
    printf("Enter %d edges in the form `v w` (no quotes):\n", nE);
    for (int i = 0; i < nE; i++) {
        int v = 0;
        int w = 0;
        if (scanf("%d %d", &v, &w) != 2) {
            fprintf(stderr, "error: failed to read edge\n");
            exit(EXIT_FAILURE);
        }
        GraphInsertEdge(g, v, w);
    }

    GraphShow(g);
    
    printf("\nEnter the source vertex: ");
    int src;
    while (scanf("%d", &src) == 1) {
        int result = numReachable(g, src);
        printf("Number of vertices reachable from vertex %d: %d\n", src, result);
        printf("Enter the source vertex: ");
    }
    
    GraphFree(g);
}
