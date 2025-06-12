// Implementation of navigation algorithms

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "navigator.h"
#include "RoadMap.h"
#include "time.h"

static void shortestPath (RoadMap map, int start, int end, int *pred, int *dist);
static bool vSetIsEmpty(bool *inVset, int size);
static void advancedShortestPath (RoadMap map, int start, int end, int *pred, int *dist, struct time startTime, struct time *departTime);
static bool needToWait (struct time current, int travelMinutes, struct time closedFrom, struct time closedUntil);

////////////////////////////////////////////////////////////////////////
// Task 3

struct route navigate(RoadMap map, int fromNode, int toNode,
                      struct time time) {
	struct route route = {
		.fromNode = fromNode,
		.toNode = toNode,
		.numLegs = 0,
		.legs = NULL,
	};
	int *pred = calloc(RoadMapNumNodes(map), sizeof(int)); // store previous node
	int *dist = calloc(RoadMapNumNodes(map), sizeof(int)); // store distance from start node
	if (pred == NULL || dist == NULL) {
		fprintf(stderr, "error: Memory Allocation Failed.\n");
		exit(1);
	}
	for (int i = 0; i < RoadMapNumNodes(map); i++) { // initialzing arrays
		pred[i] = -1;
		dist[i] = INT_MAX;
	}

	shortestPath(map, fromNode, toNode, pred, dist); // find the shortest path
	
	if (dist[toNode] == INT_MAX) { // path not found
		free(pred);
		free(dist);
		return route;
	}

	int numleg = 0;
	int predcessor = toNode;
	for (; predcessor != -1; predcessor = pred[predcessor]) { // get the number of legs
		numleg++;	
	}

	route.numLegs = numleg - 1;
	int *path = malloc(numleg * sizeof(int)); // store the path from start to end
	if (path == NULL) {
		fprintf(stderr, "error: Memory Allocation Failed.\n");
		exit(1);
	}
	predcessor = toNode;
	for (int i = numleg - 1; i >= 0; i--) { // recording the path to array
		path[i] = predcessor;
		predcessor = pred[predcessor];
	}

	route.legs = calloc(route.numLegs, sizeof(struct leg));

	struct time currentTime = time;
	// create legs
	for (int i = 0; i < route.numLegs; i++) {
		int fromN = path[i];
		int toN = path[i + 1];
		struct road roadFromN[MAX_ROADS_PER_NODE];
		int sizeOfRoadFromN = RoadMapGetRoadsFrom(map, fromN, roadFromN); // get road from node
		for (int j = 0; j < sizeOfRoadFromN; j++) {
			struct road r = roadFromN[j];
			if (r.toNode == toN) { // create single leg
				int timeCost = r.travelMinutes;
				route.legs[i].fromNode = fromN;
				route.legs[i].toNode = toN;
				route.legs[i].duration = timeCost;

				route.legs[i].start = currentTime;
				if (RoadMapHasTrafficLights(map, fromN) && i != 0) { // considering if the node has traffic lights
					currentTime = timeAdd(currentTime, TRAFFIC_LIGHT_WAIT);
					route.legs[i].start = currentTime;
					timeCost += TRAFFIC_LIGHT_WAIT;
				}
				currentTime = timeAdd(currentTime, r.travelMinutes); // updating current time
				route.legs[i].end = currentTime;
			}
		}
	}
	// setting legs to route
	route.start = route.legs[0].start;
	route.end = route.legs[route.numLegs - 1].end;
	route.totalDuration = timeDiff(route.legs[0].start, currentTime); //setting total duration

	free(pred);
	free(dist);
	free(path);
	
    return route;
}

// Dijkstra's Alogrithm
static void shortestPath (RoadMap map, int start, int end, int *pred, int *dist) {
	int nodeNum = RoadMapNumNodes(map);
	bool *visited = calloc(nodeNum, sizeof(bool)); // recording the node is visited or not
	bool *inVset = calloc(nodeNum, sizeof(bool)); // check the node is in vset or not
	if (visited == NULL || inVset == NULL) {
		fprintf(stderr, "error: Memory Allocation Failed.\n");
		exit(1);
	}
	for (int i = 0; i < nodeNum; i++) { // initialize
		visited[i] = false;
		inVset[i] = true;
	}
	dist[start] = 0;
	while (!vSetIsEmpty(inVset, nodeNum)) { // if vset is not empty
		int minimal = INT_MAX; // compare from the biggest
		int node;
		for (int i = 0; i < nodeNum; i++) {
			if (inVset[i] && dist[i] < minimal) {
				minimal = dist[i];
				node = i;
			}
		}

		inVset[node] = false;
		struct road roads[MAX_ROADS_PER_NODE];
		int roadNum = RoadMapGetRoadsFrom(map, node, roads);
		for (int i = 0; i < roadNum; i++) { // go through every neighbor node
			int toNode = roads[i].toNode;
			int time = roads[i].travelMinutes;

			if (RoadMapHasTrafficLights(map, node)) { // considering the traffic lights
				time += TRAFFIC_LIGHT_WAIT;
			}

			if (dist[node] + time < dist[toNode]) { // update if the diatance less than previous diatance
				dist[toNode] = dist[node] + time;
				pred[toNode] = node;
			}
		}
	}

	free(visited);
	free(inVset);
}

static bool vSetIsEmpty(bool *inVset, int size) {
	for (int i = 0; i < size; i++) {
		if (inVset[i]) return false;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////
// Task 4

/**
 * Describe your solution in detail here: use dijkstra algorithm and consider the close road,
 find the shortest path and backtracking create legs. 
 * 
 * TODO
 */
struct route advancedNavigate(RoadMap map, int fromNode, int toNode,
                              struct time time) {
	// TODO
	struct route route = {
		.fromNode = fromNode,
		.toNode = toNode,
		.numLegs = 0,
		.legs = NULL,
	};

	int nodeNum = RoadMapNumNodes(map);
	int *pred = calloc(nodeNum, sizeof(int));
	int *dist = calloc(nodeNum, sizeof(int));
	struct time *departTime = calloc(nodeNum, sizeof(struct time));
	if (!pred || !dist || !departTime) {
		fprintf(stderr, "error: Memory Allocation Failed.\n");
		exit(1);
	}
	for (int i = 0; i < nodeNum; i++) {
		pred[i] = -1;
		dist[i] = INT_MAX;
	}

	advancedShortestPath(map, fromNode, toNode, pred, dist, time, departTime);

	
	free(pred);
	free(dist);
	free(departTime);
    return route;
}

static void advancedShortestPath (RoadMap map, int start, int end, int *pred, int *dist, struct time startTime, struct time *departTime) {
	int nodeNum = RoadMapNumNodes(map);
	bool *visited = calloc(nodeNum, sizeof(bool));
	bool *inVset = calloc(nodeNum, sizeof(bool));
	if (visited == NULL || inVset == NULL) {
		fprintf(stderr, "error: Memory Allocation Failed.\n");
		exit(1);
	}
	for (int i = 0; i < nodeNum; i++) {
		visited[i] = false;
		inVset[i] = true;
	}

	dist[start] = 0;
	departTime[start] = startTime;
	while (!vSetIsEmpty(inVset, nodeNum)) {
		int minimal = INT_MAX;
		int node;
		// finding the minimal travel time node
		for (int i = 0; i < nodeNum; i++) {
			if (inVset[i] && dist[i] < minimal) {
				minimal = dist[i];
				node = i;
			}
		}
		inVset[node] = false;
		struct road roads[MAX_ROADS_PER_NODE];
		int roadNum = RoadMapGetRoadsFrom(map, node, roads);
		for (int i = 0; i < roadNum; i++) {
			struct road thisRoad = roads[i];
			struct time currentTime = timeAdd(startTime, dist[thisRoad.fromNode]);
			if (RoadMapHasTrafficLights(map, thisRoad.fromNode)) {
				currentTime = timeAdd(currentTime, 1);
			}
			if (thisRoad.affectedByStorms &&
				needToWait(currentTime, thisRoad.travelMinutes, thisRoad.closedFrom, thisRoad.closedUntil)) {
				currentTime = thisRoad.closedFrom;
			}
			int newDist = timeDiff(currentTime, startTime);
			if (visited[thisRoad.toNode]) {
				if (newDist < dist[thisRoad.toNode]) {
					dist[thisRoad.toNode] = newDist;
					pred[thisRoad.toNode] = thisRoad.fromNode;
				}
			} else {
				dist[thisRoad.toNode] = newDist;
				pred[thisRoad.toNode] = thisRoad.fromNode;
			}
			departTime[thisRoad.toNode] = timeAdd(startTime, dist[thisRoad.toNode]);
		}
	}
	free(visited);
	free(inVset);
}

static bool needToWait (struct time current, int travelMinutes, struct time closedFrom, struct time closedUntil) {
	
	int currToStart = timeDiff(current, closedFrom);
	int currToEnd = timeDiff(current, closedUntil);
	if (currToStart < travelMinutes && currToEnd > 0) return true;
	return false;

}

