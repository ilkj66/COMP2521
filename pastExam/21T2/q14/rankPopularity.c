// rankPopularity.c ... implementation of rankPopularity function

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
double getPopularity(Graph g, int target);
int **warshallAlgo(Graph g);
void rankPopularity(Graph g, int src, double *mnV) {
    int **matrix = warshallAlgo(g);
    
    for (int i = 0; i < g->nV; i++) {
        if (matrix[src][i] == 1) {
            mnV[i] = getPopularity(g, i);
        } else if (i == src) {
            mnV[i] = getPopularity(g, i);
        }
    }
    for (int i = 0; i < g->nV; i++) {
        free(matrix[i]);
    }
    free(matrix);

}

int **warshallAlgo(Graph g) {
    int num = g->nV;
    int **matrix = malloc(num * sizeof(int*));
    for (int i = 0; i < num; i++) {
        matrix[i] = malloc(sizeof(int) * num);
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (g->edges[i][j]) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            for (int k = 0; k < num; k++) {
                if(matrix[j][i] && matrix[i][k]) {
                    matrix[j][k] = 1;
                }
            }
        }
    }
    return matrix;
}

double getPopularity(Graph g, int target) {
    int numV = g->nV;
    int outDegree = 0;
    int inDegree = 0;
    for (int i = 0; i < numV; i++) {
        if (g->edges[target][i] == 1) {
            outDegree++;
        }
        if (g->edges[i][target] == 1) {
            inDegree++;
        }
    }
    if (outDegree == 0) {
        double result = inDegree / 0.5;
        return result;
    }
    return (double) inDegree / outDegree;
}

