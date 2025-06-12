
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void closeFollowers(Graph g, int src, int distance, int followers[]) {
    // TODO
    int numV = g->nV;
    bool *arr = malloc(numV * sizeof(bool));
    for (int i = 0; i < numV; i++) arr[i] = false;
    arr[src] = true;

    for (int i = distance; i > 0; i--) {
        for (int j = 0; j < numV; j++) {
            for (int k = 0; k < numV && !arr[i]; k++) {
                if (g->edges[j][k] != 0) {
                    followers[j] = 1;
                    arr[j] = true;
                }
            }
        }
    }
    free(arr);
}

