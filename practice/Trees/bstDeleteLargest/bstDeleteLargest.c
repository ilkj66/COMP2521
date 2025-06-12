#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct node *bstDeleteLargest(struct node *t, int *max) {
	if (!t) return NULL;
	struct node* curr = t;
	struct node* prev = NULL;
	while (curr->right) {
		prev = curr;
		curr = curr->right;
	}
	(*max) = curr->value;
	if (prev == NULL) {
		t = curr->left;
		free(curr);
		return t;
	}
	prev->right = curr->left;
	free(curr);
	return t;
}
