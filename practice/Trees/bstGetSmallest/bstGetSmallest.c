#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

struct node *bstGetSmallest(struct node *t) {
	// TODO
	if (!t) return NULL;
	while (t->left) {
		t = t->left;
	}
	return t;
}
