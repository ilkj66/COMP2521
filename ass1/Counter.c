// Implementation of the Counter ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Counter.h"

struct counter {
	char *character;
	int freq;
	struct counter *left;
	struct counter *right;
};

static void ItemsAdd (Counter c, struct item *numItems, int *latest_i);

Counter CounterNew(void) {
	struct counter *newCounter = malloc (sizeof(struct counter));
	if (newCounter == NULL) {
		fprintf (stderr, "Memory Allocation Failed.\n"); // error checking
		exit(1);
	}
	// initialize the new counter
	newCounter->character = NULL;
	newCounter->freq = 0;
	newCounter->left = NULL;
	newCounter->right = NULL;

	return newCounter;
}

void CounterFree(Counter c) {
	if (c == NULL) return;

	CounterFree(c->left);
	CounterFree(c->right);
	if (c->character != NULL) free(c->character);
	free(c);
}

void CounterAdd(Counter c, char *character) {
	// case Of the first node
	if (c->character == NULL) {
		c->character = strdup(character);
		c->freq = 1;
		return;
	}

	struct counter *curr = c;
	struct counter *prev = NULL;

	while (curr != NULL) {
		prev = curr;
		if (strcmp(character, curr->character) < 0) {
			curr = curr->left;
		} else if (strcmp(character, curr->character) > 0) {
			curr = curr->right;
		} else if (strcmp(character, curr->character) == 0) { // the character is already exist, increase the frequency
			curr->freq++;
			return;
		}
	}
	// character does not exist in tree, create new node of it
	struct counter *new = malloc (sizeof(struct counter));
	if (new == NULL) {
		fprintf(stderr, "Memory Allocation Failed.\n");
		return;
	}

	new->character = strdup(character);
	new->freq = 1;
	new->left = NULL;
	new->right = NULL;
	// inserting new node
	if (strcmp(character, prev->character) < 0) {
		prev->left = new;
	} else {
		prev->right = new;
	}

}

int CounterNumItems(Counter c) {
	if (c == NULL) { // base case
		return 0;
	}
	
	return 1 + CounterNumItems(c->left) + CounterNumItems(c->right);
}

int CounterGet(Counter c, char *character) {
	struct counter *curr = c;
	// Finding node
	while (curr != NULL) {
		int compare = strcmp(character, curr->character);

		if (compare < 0) 
			curr = curr->left;
		else if (compare > 0) 
			curr = curr->right;
		else return curr->freq;
	}
	return 0;

}

struct item *CounterItems(Counter c, int *numItems) {
	*numItems = CounterNumItems(c); // get size of array

	struct item *ItemsList = malloc((*numItems) * sizeof(struct item));
	if (ItemsList == NULL) {
		fprintf(stderr, "Memory Allocation Failed\n");
		exit(1);
	}

	int latest_i = 0;
	ItemsAdd(c, ItemsList, &latest_i);

	return ItemsList;
}

static void ItemsAdd (Counter c, struct item *numItems, int *latest_i) { // add the items in array
	if (c == NULL) return;
	// add items in order
	ItemsAdd(c->left, numItems, latest_i);

	strcpy(numItems[*latest_i].character, c->character);
	numItems[*latest_i].freq = c->freq;
	(*latest_i)++;

	ItemsAdd(c->right, numItems, latest_i);
}
