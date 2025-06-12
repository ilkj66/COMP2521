#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int vsetIsEmpty(int* vset, int cap) {
    for(int i = 0; i < cap; i++) {
        if (vset[i]) return 0;
    }
    return 1;
}

int findMinimal(int *dist, int cap, int* inVset) {
    int mini = -1;
    int index = -1;
    for (int i = 0; i < cap; i++) {
        if (inVset[i] && dist[i] != -1) {
            if (mini == -1 || dist[i] < mini) {
                mini = dist[i];
                index = i;
            }
        }
    }
    return index;
}

int numWithin(Graph g, int src, int dist) {
    int n = GraphNumVertices(g);
    int* distance = malloc(n * sizeof(int));
    int* inVset = malloc(n * sizeof(int)); // 0 means not in vset, 1 otherwise
    int* pred = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        distance[i] = -1;
        inVset[i] = 1;
        pred[i] = -1;
    }
    distance[src] = 0;
    while (vsetIsEmpty(inVset, n) != 1) {
        int v = findMinimal(distance, n, inVset);
        if (v == -1) break;
        inVset[v] = 0;
        for (int w = 0; w < n; w++) {
            if (g->edges[v][w]) {
                if (distance[w] > distance[v] + 1 || distance[w] == -1) {
                    distance[w] = distance[v] + 1;
                    pred[w] = v;
                }
            }
        }
    }
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (distance[i] <= dist) count++;
    }
    free(distance);
    free(inVset);
    free(pred);
    return count;
}
