#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int furthestReachable(Graph g, int src) {
    int n = GraphNumVertices(g);
    int* pred = malloc(n * sizeof(int));
    int* dist = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }
    Queue q = QueueNew();
    pred[src] = src;
    dist[src] = 0;
    QueueEnqueue(q, src);
    while (!QueueIsEmpty(q)) {
        int v = QueueDequeue(q);
        for (int i = 0; i < n; i++) {
            if (GraphIsAdjacent(g, v, i) && pred[i] == -1) {
                QueueEnqueue(q, i);
                pred[i] = v;
                dist[i] = dist[v] + 1;
            }
        }
    }
    QueueFree(q);
    int distance = -1;
    int node = -1;
    for (int i = 0; i < n; i++) {
        if (dist[i] >= distance) {
            distance = dist[i];
            node = i;
        }
    }
    free(dist);
    free(pred);
    return node;
}
