#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int numWithin(Graph g, int src, int dist);

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

    int src;
    int dist;
    printf("\nEnter the source vertex and maximum distance: ");
    while (scanf("%d %d", &src, &dist) == 2) {
        int result = numWithin(g, src, dist);
        printf("numWithin(g, %d, %d) = %d\n", src, dist, result);
        printf("Enter the source vertex and maximum distance: ");
    }
    
    GraphFree(g);
}
