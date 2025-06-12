// Algorithms to design electrical grids

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "place.h"
#include "Pq.h"

////////////////////////////////////////////////////////////////////////
// Your task

double calculate(struct place p1, struct place p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int find(int parent[], int x) {
    if (parent[x] != x) {
        parent[x] = find(parent, parent[x]);
    }
    return parent[x];
}

void unify(int parent[], int x, int y) {
    int rootX = find(parent, x);
    int rootY = find(parent, y);
    if (rootX != rootY) {
        parent[rootY] = rootX;
    }
}

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * from a power plant to all the given cities. Power lines must be built
 * between cities or between a city and a power plant.  Cost is directly
 * proportional to the total length of power lines used.
 * Assumes  that  numCities  is at least 1 (numCities is the size of the
 * cities array).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */

int planGrid1(struct place cities[], int numCities,
              struct place powerPlant,
              struct powerLine powerLines[]) {

    int totalNodes = numCities + 1;
    int *parent = malloc(sizeof(int) * totalNodes);
    for (int i = 0; i < totalNodes; i++) {
        parent[i] = i;
    }

    Pq pq = PqNew();

    for (int i = 0; i < numCities; i++) {
        for (int j = i + 1; j < numCities; j++) {
            double weight = calculate(cities[i], cities[j]);
            struct edge newEdge = {.v = i, .w = j, .weight = weight};
            PqInsert(pq, newEdge);
        }

        double weightToPlant = calculate(cities[i], powerPlant);
        struct edge edgeToPlant = {.v = i, .w = numCities, .weight = weightToPlant};
        PqInsert(pq, edgeToPlant);
    }

    int edgeCount = 0;
    while (!PqIsEmpty(pq) && edgeCount < numCities) {
        struct edge e = PqExtract(pq);
        int u = e.v;
        int v = e.w;

        if (find(parent, u) != find(parent, v)) {
            unify(parent, u, v);

            struct place from = (u == numCities) ? powerPlant : cities[u];
            struct place to   = (v == numCities) ? powerPlant : cities[v];

            powerLines[edgeCount].p1 = from;
            powerLines[edgeCount].p2 = to;

            edgeCount++;
        }
    }

    PqFree(pq);
    free(parent);
    return edgeCount;
}

////////////////////////////////////////////////////////////////////////
// Optional task

/**
 * Designs  a minimal cost electrical grid that will deliver electricity
 * to all the given cities.  Power lines must be built between cities or
 * between a city and a power plant.  Cost is directly  proportional  to
 * the  total  length of power lines used.  Assume that each power plant
 * generates enough electricity to supply all cities, so not  all  power
 * plants need to be used.
 * Assumes  that  numCities and numPowerPlants are at least 1 (numCities
 * and numPowerPlants are the sizes of the cities and powerPlants arrays
 * respectively).
 * Stores the power lines that need to be built in the given  powerLines
 * array, and returns the number of power lines stored. Assumes that the
 * powerLines array is large enough to store all required power lines.
 */
int planGrid2(struct place cities[], int numCities,
              struct place powerPlants[], int numPowerPlants,
              struct powerLine powerLines[]) {
    // TODO: Complete this function
    return 0;
}
