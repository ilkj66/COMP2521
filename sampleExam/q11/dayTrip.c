
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int dayTrip(Graph g, Vertex s, Vertex vs[]) {
    // TODO
    bool *visited = calloc(g->nV, sizeof(bool));
    int sumOfvs = 0;
    for (int i = 0; i < g->nV; i++) {
        if (g->fastEdges[s][i] && i != s) {
            visited[i] = true;
            vs[sumOfvs] = i;
            sumOfvs++;
        }
    }
    int newSumOfvs = sumOfvs;
    for (int i = 0; i < sumOfvs; i++) {
        int pred = vs[i];
        for (int j = 0; j < g->nV; j++) {
            if (g->fastEdges[pred][j] && !visited[j] && j != s) {
                visited[j] = true;
                vs[newSumOfvs] = j;
                newSumOfvs++;
            }
        }
    }
    for (int i = 0; i < g->nV; i++) {
        if (g->stdEdges[s][i] && !visited[i] && i != s) {
            visited[i] = true;
            vs[newSumOfvs] = i;
            newSumOfvs++;
        }
    }
    free(visited);
    return newSumOfvs;
}

