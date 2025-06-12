#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

struct node* newNode(int value) {
	struct node* new = malloc(sizeof(struct node));
	new->value = value;
	return new;
}

struct node *treeCopy(struct node *t, int depth) {
	if (depth < 0) return NULL;
	if (!t) return NULL;
	struct node* root = newNode(t->value);
	root->left = treeCopy(t->left, depth - 1);
	root->right = treeCopy(t->right, depth - 1);
	return root;
}
