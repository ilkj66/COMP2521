#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
    if (src == dest) return 0;
    int n = GraphNumVertices(g);
    int* pred = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) pred[i] = -1;
    pred[src] = src;
    Queue q = QueueNew();
    QueueEnqueue(q, src);
    while (!QueueIsEmpty(q)) {
        int v = QueueDequeue(q);
        for (int w = 0; w < n; w++) {
            if (GraphIsAdjacent(g, v, w) && pred[w] == -1) {
                pred[w] = v;
                QueueEnqueue(q, w);
            }
        }
    }

    QueueFree(q);
    if (pred[dest] == -1) {
        free(pred);
        return -1;
    }
    int curr = dest;
    int dist = 0;
    while (curr != src) {
        curr = pred[curr];
        dist++;
    }

    free(pred);

    return dist;
}
