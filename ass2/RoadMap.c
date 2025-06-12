// Implementation of the Road Map ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RoadMap.h"
#include "time.h"

struct roadMap {
	int nN; // number of nodes
	int nR; // number of roads
	int *roadOfNode; // an array of each nodes' number
	int *capOfNode; // capacity of each nodes' road (include from and to)
	struct road **roads; // list of roads

	int nI; //number of islands
	int *compNo; // components number of each node
	char **islandNames; // name of islands

	bool *trafLights; // traffic lights of each node exist or not, false means no traffic lights
};

static void dfsComponents(RoadMap map, int node, int *compNo, int compNumber);

////////////////////////////////////////////////////////////////////////
// Task 1

RoadMap RoadMapNew(int numNodes) {
	RoadMap newMap = malloc(sizeof(struct roadMap));

	if (newMap == NULL) {
		fprintf(stderr, "eror: Malloc Failed.\n");
		exit(1);
	}

	newMap->nN = numNodes;
	newMap->nR = 0;
	newMap->nI = 0;

	newMap->capOfNode = calloc(numNodes, sizeof(int));
	newMap->compNo = calloc(numNodes, sizeof(int));
	newMap->roadOfNode = calloc(numNodes, sizeof(int));
	newMap->trafLights = calloc(numNodes, sizeof(bool));
	newMap->islandNames = calloc(numNodes, sizeof(char *));
	// calloc error checking
	if (newMap->roadOfNode == NULL || newMap->compNo == NULL || newMap->capOfNode == NULL 
		|| newMap->islandNames == NULL || newMap->trafLights == NULL) {
		fprintf(stderr, "error: Malloc Failed.\n");
		exit(1);
	}
	// initialing the data structure
	for (int i = 0; i < numNodes; i++) {
		newMap->roadOfNode[i] = 0;
		newMap->capOfNode[i] = 0;
		newMap->compNo[i] = -1;
		newMap->trafLights[i] = false;
	}
	// create roads which can contains double way roads
	newMap->roads = calloc(numNodes, sizeof(struct road *));
	if (newMap->roads == NULL) {
		fprintf(stderr, "error: Malloc Failed.\n");
		exit(1);
	}
	for (int i = 0; i < numNodes; i++) {
		newMap->roads[i] = calloc(MAX_ROADS_PER_NODE * 2, sizeof(struct road)); // able to store both side of roads
	}
	
	return newMap;
}

void RoadMapFree(RoadMap map) {
	for (int i = 0; i < map->nN; i++) free(map->roads[i]);
	if (map->islandNames != NULL) {
		for (int i = 0; i < map->nI; i++) {
			free(map->islandNames[i]);
		}
	} 
	free(map->islandNames);
	
	free(map->compNo);
	free(map->roads);
	free(map->capOfNode);
	free(map->roadOfNode);
	free(map->trafLights);
	free(map);
}

int RoadMapNumNodes(RoadMap map) {
	return map->nN;
}

int RoadMapNumRoads(RoadMap map) {
	return map->nR;
}

bool RoadMapAddRoad(RoadMap map, int node1, int node2,
                    bool isTwoWay, int travelMinutes) {
	// if there are already 4 roads with nodes
	if (map->roadOfNode[node1] >= MAX_ROADS_PER_NODE || map->roadOfNode[node2] >= MAX_ROADS_PER_NODE) return false;
	// check the road already exist
	for (int i = 0; i < map->capOfNode[node1]; i++) {
		struct road r = map->roads[node1][i];
		if (r.toNode == node2) {
			return false;
		}
	}

	for (int i = 0; i < map->capOfNode[node2]; i++) {
		struct road r = map->roads[node2][i];
		if (r.fromNode == node1) {
			return false;
		}
	}
	// add road (single way)
	struct road newRoad;
	newRoad.fromNode = node1;
	newRoad.toNode = node2;
	newRoad.travelMinutes = travelMinutes;
	newRoad.affectedByStorms = false; // default as false

	map->roads[node1][map->capOfNode[node1]++] = newRoad;
	map->roads[node2][map->capOfNode[node2]++] = newRoad;

	map->roadOfNode[node1]++;

	map->roadOfNode[node2]++;
	// check if the road is two ways
	if (isTwoWay) {
		
		for (int i = 0; i < map->capOfNode[node1]; i++) {
			struct road r = map->roads[node1][i];
			if (r.fromNode == node2) {
				return false;
			}
		}
		for (int i = 0; i < map->capOfNode[node2]; i++) {
			struct road r = map->roads[node2][i];
			if (r.toNode == node1) {
				return false;
			}
		}

		struct road newRoad2;
		newRoad2.fromNode = node2;
		newRoad2.toNode = node1;
		newRoad2.travelMinutes = travelMinutes;
		newRoad2.affectedByStorms = false;

		map->roads[node1][map->capOfNode[node1]++] = newRoad2;
		map->roads[node2][map->capOfNode[node2]++] = newRoad2;
	}
	map->nR++; // increase the roads number
	return true;
}

int RoadMapGetRoadsFrom(RoadMap map, int node, struct road roads[]) {
	int cap = map->capOfNode[node];
	int j = 0;
	for (int i = 0; i < cap; i++) {
		struct road thisRoad = map->roads[node][i];
		if (thisRoad.fromNode == node) {
			roads[j++] = thisRoad;
		}
	}
	return j;
}

int RoadMapGetRoadsTo(RoadMap map, int node, struct road roads[]) {
	int cap = map->capOfNode[node];
	int j = 0;
	for (int i = 0; i < cap; i++) {
		struct road thisRoad = map->roads[node][i];
		if (thisRoad.toNode == node) {
			roads[j++] = thisRoad;
		}
	}
	return j;
}

////////////////////////////////////////////////////////////////////////
// Task 2

void RoadMapProcessIslands(RoadMap map) {
	int compNumber = 0;
	// using dfs to check the components
	for (int i = 0; i < RoadMapNumNodes(map); i++) {
		if(map->compNo[i] == -1) {
			dfsComponents(map, i, map->compNo, compNumber);
			compNumber++; // update the component number
		}
	}
	map->nI = compNumber;
	free(map->islandNames);
	map->islandNames = malloc(sizeof(char *) * map->nI); // setting the island names
	for(int i = 0; i < map->nI; i++) {
		map->islandNames[i] = NULL;
	}
}

static void dfsComponents(RoadMap map, int node, int *compNo, int compNumber) {
	//check the component recursivly
	compNo[node] = compNumber;
	for (int i = 0; i < map->capOfNode[node]; i++) { // go through each nodes in the map
		struct road r = map->roads[node][i]; // finding each neighbor of the node
		if (r.fromNode == node && compNo[r.toNode] == -1) {
			dfsComponents(map, r.toNode, compNo, compNumber);
		}
	}
}

int RoadMapNumIslands(RoadMap map) {
	return map->nI;
}

bool RoadMapOnSameIsland(RoadMap map, int node1, int node2) {
	return map->compNo[node1] == map->compNo[node2];
}

void RoadMapSetIslandName(RoadMap map, int node, char *name) {
	int compNo = map->compNo[node];
	map->islandNames[compNo] = strdup(name); // set the same name
}

char *RoadMapGetIslandName(RoadMap map, int node) {
	int compNo = map->compNo[node];
	return map->islandNames[compNo];
}

////////////////////////////////////////////////////////////////////////
// Task 3

void RoadMapAddTrafficLights(RoadMap map, int node) {
	if (!map->trafLights[node]) map->trafLights[node] = true;
}

bool RoadMapHasTrafficLights(RoadMap map, int node) {
	return map->trafLights[node];
}

////////////////////////////////////////////////////////////////////////
// Task 4

void RoadMapAddRoadClosure(RoadMap map, int node1, int node2,
                           struct time from, struct time until) {
	// finding the road and set the close time (single way)
	for (int i = 0; i < map->capOfNode[node1]; i++) {
		struct road *r = &map->roads[node1][i];
		if ((r->fromNode == node1 && r->toNode == node2) || (r->fromNode == node2 && r->toNode == node1)) {
			r->affectedByStorms = true;
			r->closedFrom = from;
			r->closedUntil = until;
		}
	}
	// finding the road and set the close time (double way)
	for (int i = 0; i < map->capOfNode[node2]; i++) {
		struct road *r = &map->roads[node2][i];
		if ((r->fromNode == node2 && r->toNode == node1) || (r->fromNode == node1 && r->toNode == node2)) {
			r->affectedByStorms = true;
			r->closedFrom = from;
			r->closedUntil = until;
		}
	}
}
