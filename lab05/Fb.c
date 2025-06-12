// Implementation of the FriendBook ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fb.h" 
#include "List.h"
#include "Map.h"
#include "Queue.h"

#define DEFAULT_CAPACITY 1 // DO NOT change this line

struct adjNode {
    int v;
    struct adjNode *next;
};

// DO NOT modify this struct
struct fb {
    int numPeople;
    int capacity;

    char **names; // the id of a person is simply the index
                  // that contains their name in this array
    
    Map nameToId; // maps names to ids

    struct adjNode **adj; // adjacency lists, kept in increasing order
};

static void increaseCapacity(Fb fb);
static int nameToId(Fb fb, char *name);

static struct adjNode *newAdjNode(int v);
static bool inAdjList(struct adjNode *l, int v);
static void freeAdjList(struct adjNode *l);
static int cmp(const void *a, const void *b);

// Please ignore this line
static struct adjNode * __attribute__((unused)) newAdjNode(int v);

////////////////////////////////////////////////////////////////////////

// Creates a new instance of FriendBook
Fb FbNew(void) {
    Fb fb = malloc(sizeof(*fb));
    if (fb == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    fb->numPeople = 0;
    fb->capacity = DEFAULT_CAPACITY;
    
    fb->names = calloc(fb->capacity, sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    
    fb->nameToId = MapNew();

    fb->adj = calloc(fb->capacity, sizeof(struct adjNode *));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    return fb;
}

void FbFree(Fb fb) {
    for (int i = 0; i < fb->capacity; i++) {
        freeAdjList(fb->adj[i]);
    }
    free(fb->adj);

    MapFree(fb->nameToId);

    for (int i = 0; i < fb->numPeople; i++) {
        free(fb->names[i]);
    }
    free(fb->names);
    
    free(fb);
}

int FbNumPeople(Fb fb) {
    return fb->numPeople;
}

bool FbAddPerson(Fb fb, char *name) {
    if (fb->numPeople == fb->capacity) {
        increaseCapacity(fb);
    }

    if (!MapContains(fb->nameToId, name)) {
        int id = fb->numPeople++;
        fb->names[id] = strdup(name);
        MapSet(fb->nameToId, name, id);
        return true;
    } else {
        return false;
    }
}

static void increaseCapacity(Fb fb) {
    int newCapacity = fb->capacity * 2;
    
    fb->names = realloc(fb->names, newCapacity * sizeof(char *));
    if (fb->names == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->names[i] = NULL;
    }
    
    fb->adj = realloc(fb->adj, newCapacity * sizeof(struct adjNode));
    if (fb->adj == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }
    for (int i = fb->capacity; i < newCapacity; i++) {
        fb->adj[i] = NULL;
    }
    
    fb->capacity = newCapacity;
}

bool FbHasPerson(Fb fb, char *name) {
    return MapContains(fb->nameToId, name);
}

List FbGetPeople(Fb fb) {
    List l = ListNew();
    for (int id = 0; id < fb->numPeople; id++) {
        ListAppend(l, fb->names[id]);
    }
    return l;
}

bool FbIsFriend(Fb fb, char *name1, char *name2) {
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);
    return inAdjList(fb->adj[id1], id2);
}

////////////////////////////////////////////////////////////////////////
// Your tasks

bool FbFriend(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    if (FbIsFriend(fb, name1, name2)) {
        return false;
    }

    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);

    struct adjNode *name1Node = newAdjNode(id1);
    struct adjNode *name2Node = newAdjNode(id2);

    if (fb->adj[id1] == NULL) {
        fb->adj[id1] = name2Node;
    } else if (fb->adj[id1]->v > id2) {
        name2Node->next = fb->adj[id1];
        fb->adj[id1] = name2Node;
    } else {
        struct adjNode *curr = fb->adj[id1];
        while (curr->next != NULL && curr->next->v < id2) {
            curr = curr->next;
        }
        name2Node->next = curr->next;
        curr->next = name2Node;
    }

    if (fb->adj[id2] == NULL) {
        fb->adj[id2] = name1Node;
    } else if (fb->adj[id2]->v > id1) {
        name1Node->next = fb->adj[id2];
        fb->adj[id2] = name1Node;
    } else {
        struct adjNode *curr = fb->adj[id2];
        while (curr->next != NULL && curr->next->v < id1) {
            curr = curr->next;
        }
        name1Node->next = curr->next;
        curr->next = name1Node;
    }
    

    return true;
} 

int FbNumFriends(Fb fb, char *name) {
    // TODO: Complete this function
    int count = 0;
    int id = nameToId(fb, name);
    
    struct adjNode *curr = fb->adj[id];
    while(curr != NULL) {
        curr = curr->next;
        count++;
    }
    return count;
}

List FbMutualFriends(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    List l = ListNew();
    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);

    struct adjNode *curr1 = fb->adj[id1];
    struct adjNode *curr2 = fb->adj[id2];
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->v == curr2->v) {
            ListAppend(l, fb->names[curr1->v]);
            curr1 = curr1->next;
            curr2 = curr2->next;
        } else if (curr1->v > curr2->v) {
            curr2 = curr2->next;
        } else curr1 = curr1->next;
    }

    return l;
}

bool FbUnfriend(Fb fb, char *name1, char *name2) {
    // TODO: Complete this function
    if (!FbIsFriend(fb, name1, name2)) return false;

    int id1 = nameToId(fb, name1);
    int id2 = nameToId(fb, name2);

    struct adjNode *curr1 = fb->adj[id1];
    struct adjNode *curr2 = fb->adj[id2];

    if (curr1->v == id2) {
        struct adjNode *tmp = curr1;
        fb->adj[id1] = curr1->next;
        free(tmp);
    } else {
        while (curr1->next->v < id2) {
            curr1 = curr1->next;
        }
        struct adjNode *tmp = curr1->next->next;
        free(curr1->next);
        curr1->next = tmp;
    }

    if (curr2->v == id1) {
        struct adjNode *tmp = curr2;
        fb->adj[id2] = curr2->next;
        free(tmp);
    } else {
        while (curr2->next->v < id1) {
            curr2 = curr2->next;
        }
        struct adjNode *tmp = curr2->next->next;
        free(curr2->next);
        curr2->next = tmp;
    }
    
    return true;
}

int FbFriendRecs1(Fb fb, char *name, struct recommendation recs[]) {
    //TODO: Complete this function
    
    // get all the non-friend list
    int id = nameToId(fb, name);
    bool *friendList = malloc (fb->numPeople * sizeof(bool));
    // initialize the list
    for (int i = 0; i < fb->numPeople; i++) {
        friendList[i] = false;
        recs[i].numMutualFriends = 0;
        strcpy(recs[i].name, fb->names[i]);
    }
    // set friends' id to true
    struct adjNode *curr = fb->adj[id];
    while(curr != NULL) {
        friendList[curr->v] = true;
        curr = curr->next;
    }

    for (int i = 0; i < fb->numPeople; i++) {
        if (!friendList[i]) {
            curr = fb->adj[i];
            while (curr != NULL) {
                if (friendList[curr->v]) recs[i].numMutualFriends++;
                curr = curr->next;
            }
        }
    }
    int recCount = 0;
    for (int i = 0; i < fb->numPeople; i++) {
        if (recs[i].numMutualFriends > 0) recCount++;
    }

    
    qsort(recs, recCount-1, sizeof(struct recommendation), cmp);
    free (friendList);

    return recCount-1;
}

static int cmp(const void *a, const void *b) {
    return ((struct recommendation *)b)->numMutualFriends - 
           ((struct recommendation *)a)->numMutualFriends;
}

////////////////////////////////////////////////////////////////////////
// Optional task

List FbFriendRecs2(Fb fb, char *name) {
    // TODO: Complete this function
    List l = ListNew();
    return l;
}

////////////////////////////////////////////////////////////////////////
// Helper Functions

// Converts a name to an ID. Raises an error if the name doesn't exist.
static int nameToId(Fb fb, char *name) {
    if (!MapContains(fb->nameToId, name)) {
        fprintf(stderr, "error: person '%s' does not exist!\n", name);
        exit(EXIT_FAILURE);
    }
    return MapGet(fb->nameToId, name);
}

static struct adjNode *newAdjNode(int v) {
    struct adjNode *n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->v = v;
    n->next = NULL;
    return n;
}

static bool inAdjList(struct adjNode *l, int v) {
    for (struct adjNode *n = l; n != NULL && n->v <= v; n = n->next) {
        if (n->v == v) {
            return true;
        }
    }
    return false;
}

static void freeAdjList(struct adjNode *l) {
    struct adjNode *n = l;
    while (n != NULL) {
        struct adjNode *temp = n;
        n = n->next;
        free(temp);
    }
}

