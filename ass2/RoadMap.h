// Interface to the Road Map ADT
// Nodes (intersections) are identified by integers between 0 and N - 1,
// where N is the number of nodes.

// !!! DO NOT MODIFY THIS FILE !!!

#ifndef ROAD_MAP_H
#define ROAD_MAP_H

#include <stdbool.h>

#include "time.h"

#define MAX_ROADS_PER_NODE 4

typedef struct roadMap *RoadMap;

struct road {
    int fromNode;
    int toNode;
    int travelMinutes;

    // Only used in Task 4
    bool affectedByStorms;
    struct time closedFrom;
    struct time closedUntil;
};

////////////////////////////////////////////////////////////////////////
// Task 1

/**
 * Creates a new road map with the given number of nodes (intersections)
 * and no roads.
 * Assumes that `numNodes` is positive.
 */
RoadMap RoadMapNew(int numNodes);

/**
 * Frees all memory allocated to the map
 */
void RoadMapFree(RoadMap map);

/**
 * Returns the number of nodes in the map
 */
int RoadMapNumNodes(RoadMap map);

/**
 * Returns the number of roads in the map
 *
 * Note: Both one-way and two-way roads count as a single road.
 */
int RoadMapNumRoads(RoadMap map);

/**
 * Adds a road between nodes `node1` and `node2` that takes
 * `travelMinutes` minutes to drive down, if:
 * - There are not already MAX_ROADS_PER_NODE roads connected to `node1`
 *   (regardless of the direction of the roads), and
 * - There are not already MAX_ROADS_PER_NODE roads connected to `node2`
 *   (regardless of the direction of the roads), and
 * - There is not already a road (either one-way or two-way) between
 *   `node1` and `node2`.
 *
 * If `isTwoWay` is true, the new road is a two-way road, otherwise it
 * is a one-way road from `node1` to `node2`.
 * Returns true if the road was added, and false otherwise.
 *
 * Assumes that `node1` and `node2` are valid and not equal, and that
 * `travelMinutes` is positive and less than MINUTES_PER_DAY.
 *
 * Note: Both one-way and two-way roads count as a single road.
 */
bool RoadMapAddRoad(RoadMap map, int node1, int node2,
                    bool isTwoWay, int travelMinutes);

/**
 * Stores outbound roads from `node` in the given `roads` array, and
 * returns the number of roads stored. In each of the roads stored, the
 * `fromNode` field should be equal to `node`.
 *
 * Assumes that the `roads` array is large enough to store the roads.
 */
int RoadMapGetRoadsFrom(RoadMap map, int node, struct road roads[]);

/**
 * Stores inbound roads to `node` in the given `roads` array, and
 * returns the number of roads stored. In each of the roads stored, the
 * `toNode` field should be equal to `node`.
 *
 * Assumes that the `roads` array is large enough to store the roads.
 */
int RoadMapGetRoadsTo(RoadMap map, int node, struct road roads[]);

////////////////////////////////////////////////////////////////////////
// Task 2

/**
 * Internally processes and saves information about islands based on the
 * current roads in the map.
 * Assumes that no roads will be added to the map after this function is
 * called.
 */
void RoadMapProcessIslands(RoadMap map);

/**
 * Returns the number of islands.
 * Assumes that RoadMapProcessIslands has been called.
 */
int RoadMapNumIslands(RoadMap map);

/**
 * Returns true if the given nodes are on the same island, and false
 * otherwise.
 * Assumes that RoadMapProcessIslands has been called.
 */
bool RoadMapOnSameIsland(RoadMap map, int node1, int node2);

/**
 * Given a node, sets the name of the island that the node is on to the
 * given name. If the island was already given a name, then it should be
 * replaced with the given name.
 * Assumes that RoadMapProcessIslands has been called.
 */
void RoadMapSetIslandName(RoadMap map, int node, char *name);

/**
 * Given a node, returns the name of the island that the node is on, or
 * NULL if the island has not been named. The returned string must not
 * be modified or freed.
 * Assumes that RoadMapProcessIslands has been called.
 */
char *RoadMapGetIslandName(RoadMap map, int node);

////////////////////////////////////////////////////////////////////////
// Task 3

/**
 * Adds traffic lights to the given node. Does nothing if the node
 * already has traffic lights.
 */
void RoadMapAddTrafficLights(RoadMap map, int node);

/**
 * Returns true if the given node has traffic lights, and false
 * otherwise
 */
bool RoadMapHasTrafficLights(RoadMap map, int node);

////////////////////////////////////////////////////////////////////////
// Task 4

/**
 * Specifies that the road between `node1` and `node2` should be closed
 * from `closedFrom` until `closedUntil` each day (due to storms). Does
 * nothing if the road already has a closure time set.
 * Assumes that the road exists.
 */
void RoadMapAddRoadClosure(RoadMap map, int node1, int node2,
                           struct time closedFrom,
                           struct time closedUntil);

////////////////////////////////////////////////////////////////////////

#endif
