#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfs(Graph g, int src, bool* visited);

int numReachable(Graph g, int src) {
    int n = GraphNumVertices(g);
    bool *visited = malloc(n * sizeof(bool));
    dfs(g, src, visited);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i]) count++;
    }
    free(visited);
    return count;
}

void dfs(Graph g, int src, bool* visited) {
    int n = GraphNumVertices(g);
    visited[src] = true;
    for (int i = 0; i < n; i++) {
        if (GraphIsAdjacent(g, src, i) && !visited[i]) {
            dfs(g, i, visited);
        }
    }
}