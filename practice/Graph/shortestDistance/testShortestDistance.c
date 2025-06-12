#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int shortestDistance(Graph g, int src, int dest);

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
    
    printf("\nEnter two vertices: ");
    int src = 0;
    int dest = 0;
    while (scanf("%d %d", &src, &dest) == 2) {
        int dist = shortestDistance(g, src, dest);
        if (dist < 0) {
            printf("There is no path between vertices %d and %d\n",\
                   src, dest);
        } else {
            printf("The shortest distance between vertices %d and %d "
                   "is: %d\n",
                   src, dest, dist);
        }
        
        printf("Enter two vertices: ");
        src = 0;
        dest = 0;
    }
    
    GraphFree(g);
}
