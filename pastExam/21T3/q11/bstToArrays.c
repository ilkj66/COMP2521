
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

// Worst case time complexity of this solution: O(...)
void fillKeys(struct node *t, char keys[],int leftSiblings[], int parents[], int *index, struct node *prev, int prevInd);
void bstToArrays(struct node *t, char keys[], int parents[], int leftSiblings[]) {
	int index = 0;
	fillKeys(t, keys, leftSiblings, parents, &index, NULL, 0);
}

void fillKeys(struct node *t, char keys[], int leftSiblings[], int parents[], int *index, struct node *prev, int prevInd) {
	if (!t) return;
	keys[*index] = t->key;
	if (prev == NULL) {
		parents[*index] = *index;
	} else {
		parents[*index] = prevInd;
	}
	if (!prev || t == prev->left || !prev->left) leftSiblings[*index] = *index;
	else leftSiblings[*index] = prevInd + 1;
	int pIndex = (*index);
	(*index)++;
	fillKeys(t->left, keys, leftSiblings, parents, index, t, pIndex);
	fillKeys(t->right, keys, leftSiblings, parents, index, t, pIndex);
}

