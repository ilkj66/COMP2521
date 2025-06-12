#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

void bstPostfix(struct node *t) {
	// TODO
	if (!t) return;
	bstPostfix(t->left);
	bstPostfix(t->right);
	printf("%d ", t->value);
}
