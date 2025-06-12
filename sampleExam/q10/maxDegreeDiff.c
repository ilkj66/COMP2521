
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int maxDegreeDiff(Graph g) {
    // TODO
    int numVertex = GraphNumVertices(g);
    int *inDegree = calloc(numVertex, sizeof(int));
    int *outDegree = calloc(numVertex, sizeof(int));
    for (int i = 0; i < numVertex; i++) {
        inDegree[i] = 0;
        outDegree[i] = 0;
    }
    for (int i = 0; i < numVertex; i++) {
        struct adjNode *curr = g->edges[i];
        while (curr != NULL) {
            outDegree[i]++;
            inDegree[curr->v]++;
            curr = curr->next;
        }
    }
    int maximum = 0;
    for (int i = 0; i < numVertex; i++) {
        int newMaximum = abs(inDegree[i] - outDegree[i]);
        if (newMaximum > maximum) {
            maximum = newMaximum;
        }
    }
    free(inDegree);
    free(outDegree);
    return maximum;
}

