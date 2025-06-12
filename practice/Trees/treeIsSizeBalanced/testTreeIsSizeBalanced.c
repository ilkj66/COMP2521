#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

bool treeIsSizeBalanced(struct node *t);

int main(void) {
	struct node *t = treeRead(0);
	printf("\n");

	printf("Tree:\n");
	treePrint(t);

	bool result = treeIsSizeBalanced(t);
	printf("treeIsSizeBalanced returned %s\n",
	       result ? "TRUE" : "FALSE");

	treeFree(t);
}
