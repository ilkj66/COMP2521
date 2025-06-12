#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int bstNodes(struct node* t) {
	if (!t) return 0;
	return 1 + bstNodes(t->left) + bstNodes(t->right);
}

bool treeIsSizeBalanced(struct node *t) {
	// TODO
	if (!t) return true;
	if (abs(bstNodes(t->left) - bstNodes(t->right)) <= 1) {
		return treeIsSizeBalanced(t->left) && treeIsSizeBalanced(t->right);
	} else return false;
}
