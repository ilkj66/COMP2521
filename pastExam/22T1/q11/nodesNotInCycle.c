
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
int dfs(Graph g, int *pred, int src, int prev);
// Worst case time complexity of this solution: O(...)
void nodesNotInCycle(Graph g, int notInCycle[]) {
    // TODO
    int numV = GraphNumVertices(g);
    int* pred = malloc(numV * sizeof(int));
    for (int i = 0; i < numV; i++) pred[i] = -1;
    int end = dfs(g, pred, 0, 0);
    //backtracking
    for (int i = 0; i < numV; i++) notInCycle[i] = 1;
    int ind = end;
    while (pred[ind] != -1) {
        notInCycle[ind] = 0;
        ind = pred[ind];
    }
}

int dfs(Graph g, int *pred, int src, int prev) {
    pred[src] = prev;
    for (int i = 0; i < GraphNumVertices(g); i++) {
        if (GraphIsAdjacent(g, src, i)) {
            if (pred[i] != -1 && i != prev) {
                return src;
            }
            dfs(g, pred, i, src);
        }
    }
}
