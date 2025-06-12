#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

static int bstNodes(struct node* t) {
	if (!t) return 0;
	return 1 + bstNodes(t->left) + bstNodes(t->right);
}

int bstGetKth(struct node *t, int k) {
	int count = bstNodes(t->left);
	if (k < count) return bstGetKth(t->left, k);
	else if (k == count) return t->value;
	else return bstGetKth(t->right, k - count - 1);
}
